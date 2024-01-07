tetris: build/controler.o build/viewer.o build/viewsdl.o build/piece.o build/grille.o build/listeAttente.o build/viewtxt.o build/main.o
	gcc -g build/main.o build/controler.o build/viewer.o build/viewsdl.o build/viewtxt.o build/piece.o build/grille.o build/listeAttente.o -o tetris -lSDL2 -lSDL2_ttf -lncurses

build/main.o: view/src/viewer.h model/src/grille.h model/src/piece.h model/src/listeAttente.h controler/src/main.c controler/src/controler.h
	gcc -g -c controler/src/main.c -o  build/main.o

build/controler.o: view/src/viewer.h model/src/grille.h model/src/piece.h model/src/listeAttente.h controler/src/controler.c controler/src/controler.h
	gcc -g -c controler/src/controler.c -o  build/controler.o

build/viewer.o: view/src/viewer.c view/src/viewer.h model/src/grille.h model/src/piece.h view/src/viewsdl.h model/src/listeAttente.h view/src/viewtxt.h
	gcc -g -c view/src/viewer.c -o build/viewer.o

build/viewsdl.o: model/src/grille.h model/src/piece.h view/src/viewsdl.h view/src/viewsdl.c model/src/listeAttente.h
	gcc -g -c view/src/viewsdl.c -o build/viewsdl.o

build/viewtxt.o: model/src/grille.h model/src/piece.h view/src/viewtxt.h view/src/viewtxt.c model/src/listeAttente.h
	gcc -g -c view/src/viewtxt.c -o build/viewtxt.o

build/grille.o: model/src/grille.c model/src/grille.h model/src/piece.h
	gcc -g -c model/src/grille.c -o build/grille.o

build/piece.o: model/src/piece.c model/src/piece.h
	gcc -g -c model/src/piece.c -o build/piece.o

build/listeAttente.o: model/src/listeAttente.c model/src/listeAttente.h
	gcc -g -c model/src/listeAttente.c -o build/listeAttente.o

doc: doc/Doxyfile controler/src/controler.h controler/src/controler.c model/src/grille.c model/src/grille.h model/src/piece.c model/src/piece.h model/src/listeAttente.c model/src/listeAttente.h view/src/viewtxt.h view/src/viewtxt.c view/src/viewsdl.h view/src/viewsdl.c view/src/viewer.c view/src/viewer.h controler/src/main.c
	doxygen doc/Doxyfile

clean:
	rm build/*.o