#include "mini_lib.h"

#define TAILLE_BUFFER 2048

void mini_clean(char* nfile) {
    // Vérifie si le nom de fichier est valide
    if (nfile == NULL || mini_strlen(nfile) == 0) {
        mini_perror("Nom de fichier incorrect. \n");
        return;
    }

    // Tente d'ouvrir ou de créer le fichier en mode 'w' (écriture)
    MYFILE *file = mini_fopen(nfile, 'w');
    if (file == NULL) {
        mini_perror("mini_fopen() \n");
    } else {
        // Le fichier a été créé ou réinitialisé avec succès et on le referme
        mini_printf("Fichier '"); mini_printf(nfile); mini_printf("' a été créé/remis à zéro avec succès. \n");
        if(mini_fclose(file) == -1) mini_perror("mini_close() ");
    }
}