#pragma once

#include "gfxpch.h"
#include "gfxdefs.h"


namespace Graphics {

	class iSurface
	{
	public:
		iSurface(
			const std::wstring& _title, RECT _screen_rect,  HWND _parent=nullptr,  DWORD _style= WS_OVERLAPPEDWINDOW,  DWORD _style_ex= WS_EX_OVERLAPPEDWINDOW)
			: 
			className{ _title }, title{_title},
			width{_screen_rect.right}, height{_screen_rect.bottom},
			pos_x{_screen_rect.left}, pos_y{_screen_rect.top},
			style{ _style }, style_ex{ _style_ex }, hParent{ _parent }
		{


			// register a class to use, tie in the message thunk to seperate
			// the message callback
			WNDCLASSEX wc{ 0 };
			wc.cbSize = sizeof(wc);
			wc.lpszClassName = className.c_str();
			wc.cbClsExtra = 0;
			wc.hInstance = GetModuleHandle(NULL);
			wc.cbWndExtra = 0;
			wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = HandleMessageThunk;
			
			ATOM result = RegisterClassEx(&wc);
			if (result == 0) {
				_com_error err(GetLastError());
				std::wstringstream wss;
				std::wcout << L"Could Not Register Window Surface\n" << err.ErrorMessage() << "\n";
				throw std::runtime_error("WINDOW ERROR!");

			}

			hSurface = CreateWindowEx(style_ex, className.c_str(), title.c_str(), style, pos_x, pos_y, width, height, hParent, nullptr, GetModuleHandle(NULL), this);

			if (hSurface == nullptr) {
				throw std::runtime_error("Could Not Create a Surface");
			}


			ShowWindow(hSurface, SW_NORMAL);


		};
		virtual ~iSurface() = default;

		std::optional<UINT> ProcessMessages() {
			
			
			MSG msg{};
			while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			
				if (msg.message == WM_QUIT) {
					return 0;
				}

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			
			return {};
		}
		
		int GetWidth() {
			return width;
		}
		
		int GetHeight() {
			return height;
		}
		
		HWND GetSurfacePointer() {
			return hSurface;
		}

		const std::wstring& GetWindowTitle() {
			return title;
		}

		void SetWindowTitle(const std::wstring& _title) {
			title = _title;
			SetWindowText(hSurface, title.c_str());
		}

		static LRESULT CALLBACK HandleMessageThunk(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
			iSurface* pSurface = nullptr;

			// set or aquire the window pointer in the user data
			if (umsg == WM_NCCREATE) {
				CREATESTRUCT* pCreate = (CREATESTRUCT*)lparam;
				pSurface = (iSurface*)pCreate->lpCreateParams;
				SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pSurface);
				pSurface->hSurface = hwnd;
			}
			else {
				pSurface = (iSurface*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			}


			if (pSurface) {
				return pSurface->MessageHandler(umsg, wparam, lparam);
			}
			else {
				return DefWindowProc(hwnd, umsg, wparam, lparam);
			}
		}



		// Base Message Handler
		// Implements all Default Functionality for a window/surface
		virtual LRESULT CALLBACK MessageHandler(UINT msg, WPARAM w, LPARAM l) {
			switch (msg)
			{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			
			
			default:
				return DefWindowProc(hSurface, msg, w, l);
			}
		};

	private:
		const std::wstring className;

		HWND hSurface;
		HWND hParent;

		DWORD style;
		DWORD style_ex;

		RECT dimensions{ 0 };

		std::wstring title;
		int width;
		int height;
		int pos_x;
		int pos_y;

	};

}
