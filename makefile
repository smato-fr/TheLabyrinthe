Labyrinthe: Main.o Interface.o FileManager.o
	gcc -o Labyrinthe Main.o Interface.o FileManager.o

Main.o:
	gcc -c -Wall ./src/Main.c

Interface.o:
	gcc -c -Wall ./src/Interface.c

FileManager.o:
	gcc -c -Wall ./src/FileManager.c

Tool.o:
	gcc -c -Wall ./src/Tool.c

clean:
	rm -f Labyrinthe *.o
