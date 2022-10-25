Labyrinthe: Main.o Interface.o FileManager.o Tools.o
	gcc -o Labyrinthe Main.o Interface.o FileManager.o Tools.o

Main.o:
	gcc -c -Wall ./src/Main.c

Interface.o:
	gcc -c -Wall ./src/Interface.c

FileManager.o:
	gcc -c -Wall ./src/FileManager.c

Tools.o:
	gcc -c -Wall ./src/Tools.c

clean:
	rm -f Labyrinthe *.o
