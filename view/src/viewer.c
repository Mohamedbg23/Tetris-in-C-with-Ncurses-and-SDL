//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
#include <stdlib.h>
#include <string.h>
#include "viewtxt.h"
#include "viewsdl.h"

viewer * makeViewer(char *v){
    viewer *ret = NULL;
  if (!strcmp(v, "text")) {
    ret = initTextViewer();
  } else if (!strcmp(v, "sdl")) {
    ret = initSdlViewer();
  }
  return ret;
}