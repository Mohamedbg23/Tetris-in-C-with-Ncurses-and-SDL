//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "../../model/src/listeAttente.h"
#include "../../model/src/grille.h"
#include "../../model/src/piece.h"
#include "../../view/src/viewer.h"
#include "../../view/src/viewsdl.h"
#include "../../view/src/viewtxt.h"
#include "controler.h"

int main(int argc, char **argv){
    srand(time(NULL));
    if (argc != 2) {
        fprintf(stderr, "Error when parsing the parameters.\n");
        fprintf(stderr, "[USAGE] %s viewer\n", argv[0]);
        fprintf(stderr, "\t viewer can be text or sdl\n");
        return EXIT_FAILURE;
    }
    if(!strcmp("sdl",argv[1])){
        jeuSDL();
    }
    else if(!strcmp("txt",argv[1])){
        jeuTXT();
    }
    return EXIT_SUCCESS;
}