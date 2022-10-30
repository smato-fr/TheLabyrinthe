linux: clean1 LabyrintheLinux clean2

linux_win: clean1 LabyrintheWindows clean2

windows: clean1 LabyrintheWindows clean2

LabyrintheWindowsFromLinux: MainW.o InterfaceW.o FileManagerW.o ToolsW.o
	x86_64-w64-mingw32-gcc -o Labyrinthe.exe MainW.o InterfaceW.o FileManagerW.o ToolsW.o

LabyrintheLinux: Main.o Interface.o FileManager.o Tools.o
	gcc -o Labyrinthe Main.o Interface.o FileManager.o Tools.o

LabyrintheWindows: Main.o Interface.o FileManager.o Tools.o
	gcc -o Labyrinthe.exe Main.o Interface.o FileManager.o Tools.o

Main.o:
	gcc -c -Wall ./src/Main.c

Interface.o:
	gcc -c -Wall ./src/Interface.c

FileManager.o:
	gcc -c -Wall ./src/FileManager.c

Tools.o:
	gcc -c -Wall ./src/Tools.c


MainW.o:
	x86_64-w64-mingw32-gcc -o MainW.o -c -Wall ./src/Main.c

InterfaceW.o:
	x86_64-w64-mingw32-gcc -o InterfaceW.o -c -Wall ./src/Interface.c

FileManagerW.o:
	x86_64-w64-mingw32-gcc -o FileManagerW.o -c -Wall ./src/FileManager.c

ToolsW.o:
	x86_64-w64-mingw32-gcc -o ToolsW.o -c -Wall ./src/Tools.c

clean1:
	rm -f *.o

clean2:
	rm -f *.o
