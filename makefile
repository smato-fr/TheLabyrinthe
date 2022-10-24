prog: main.o constants.o interface.o filemanager.o
	gcc -o prog -c main.o constants.o interface.o filemanager.o

main.o: Main.c
	gcc -c -Wall Main.c

constants.o: Constants.c
	gcc -o constants.o -c Constants.c

interface.o: Interface.c
	gcc -o interface.o -c Interface.c

filemanager.o: FileManager.c
	gcc -o filemanager.o -c FileManager.c

clean:
	rm -f prog *.o
