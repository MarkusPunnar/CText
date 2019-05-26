# CText
Simple text editor C++ project.

The editor can:

 - Open and save text files.
 - Change text font and size.
 - Add styles to the text - for example color, bold and italic.
 - Open multiple files as tabs at the same time.
 - Notice when you are trying to close a tab with unsaved changes.
 - Undo and redo functionality.
 
To run the editor:

 - On Windows: 
1) open Qt console (probably named Qt 5.13.0 (MinGW 7.3.0 64-bit) if you have the newest version)
2) go to the program folder like you would with cmd
3) run command - qmake.exe CText.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug"
4) run command - mingw32-make.exe -j4
5) go to debug folder and run command (don't forget the dot at the end of the command) - windeployqt.exe --quick .
 6) run CText.exe file in the debug folder
 
 - On Linux, run the startup.sh script to compile the code and make an executable file. After that, run CText with ./CText
