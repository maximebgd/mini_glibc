#include "mini_lib.h"

#define TAILLE_BUFFER 2048

void mini_clear(char* nfile) {
    write(STDOUT_FILENO, "\033[H\033[2J", 7);
}