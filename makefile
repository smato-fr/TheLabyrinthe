Labyrinthe: Main.o Constants.o Interface.o FileManager.o
    gcc -o Labyrinthe Constants.o Interface.o FileManager.o

Main.o: ./src/Main.c
    gcc -c -Wall ./src/Main.c

Constants.o: ./src/Constants.c
    gcc -c -Wall ./src/Constants.c

Interface.o: ./src/Interface.c
    gcc -c -Wall ./src/Interface.c

FileManager.o: ./src/FileManager.c
    gcc -c -Wall ./src/FileManager.c

clean:
    rm -f Labyrinthe *.o
