all: main.o bossFunctions.o debugPrint.o fightFunctions.o
	gcc -g main.o bossFunctions.o debugPrint.o fightFunctions.o -o HW3

main.o: main.c game.h
	gcc -g -c main.c 
	
fightFunctions.o: fightFunctions.c game.h
	gcc -g -c fightFunctions.c
	
bossFunctions.o: bossFunctions.c game.h
	gcc -g -c bossFunctions.c

debugPrint.o: debugPrint.c game.h
	gcc -g -c debugPrint.c 

clean: 
	rm *.o HW3

