call bin\exe\premake5\premake5.exe vs2022

@echo test mode enabled. copying test database...

call xcopy /E /I "assets\\" "modules/hollow/assets\\" /Y


PAUSE