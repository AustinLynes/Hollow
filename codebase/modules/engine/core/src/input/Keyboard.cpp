#include "Keyboard.h"

bool Keyboard::IsKeyPressed(KeyCode kc)
{
	return (keys[kc] == true);
}


const char* kc_to_string(KeyCode kc) {
	switch (kc)
	{
	case LEFT_ARROW:
		return "Left Arrow";
	case UP_ARROW:
		return "Up Arrow";
	case RIGHT_ARROW:
		return "Right Arrow";
	case DOWN_ARROW:
		return "Down Arrow";
	case A:
		return "A";
	case B:
		return "B";
	case C:
		return "C";
	case D:
		return "D";
	case E:
		return "E";
	case F:
		return "F";
	case G:
		return "G";
	case H:
		return "H";
	case I:
		return "I";
	case J:
		return "J";
	case K:
		return "K";
	case L:
		return "L";
	case M:
		return "M";
	case N:
		return "N";
	case O:
		return "O";
	case P:
		return "P";
	case Q:
		return "Q";
	case R:
		return "R";
	case S:
		return "S";
	case T:
		return "T";
	case U:
		return "U";
	case V:
		return "V";
	case W:
		return "W";
	case X:
		return "X";
	case Y:
		return "Y";
	case Z:
		return "Z";
	}
}

void Keyboard::OnKeyDown(KeyCode kc)
{

	// Dispatch Event OnKeyPressed(keyCode)
	keys[kc] = true;
	// used to determine what virtual windows keycode matches to what FSE keycode
	
	//std::cout <<  kc_to_string(kc) << std::endl;

}

void Keyboard::OnKeyUp(KeyCode kc)
{
	// Dispatch Event OnKeyReleased(kc)
	keys[kc] = false;
}
