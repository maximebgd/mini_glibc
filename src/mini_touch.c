#include "mini_lib.h"

#define TAILLE_BUFFER 2048

// Version 1 
/*void mini_touch(char* nfile) { // Créer un fichier si inexistant sinon fait rien AVEC ERROR ERRNO
    // Vérification si le nom de fichier est correct
    if (nfile == NULL || mini_strlen(nfile) == 0) {
        mini_perror("Nom de fichier incorrect. \n");
        return;
    }

    // Tenter d'ouvrir le fichier en mode lecture
    MYFILE *file_read = mini_fopen(nfile, 'r');
    if(file_read != NULL) {
        // Le fichier existe déjà
        if(mini_fclose(file_read) == -1) {
            mini_perror("mini_fclose(file_read) ");
        }
    }
    else {
        // Le fichier n'existe pas, ouverture en mode écriture ('w')
        MYFILE *file_write = mini_fopen(nfile, 'w');
        mini_printf("--(on obtient un code errno = 2, ce qui est normal) --\n");
        if (file_write == NULL) {
            mini_perror("Erreur lors de la création du fichier. \n");
            return;
        }
        // Fermeture du fichier
        if (mini_fclose(file_write) == -1) {
            mini_perror("mini_fclose(file_write) ");
        }
    }
}*/

// Version 2 
void mini_touch(char* nfile) { // Créer un fichier si inexistant sinon fait rien SANS ERROR ERRNO
    MYFILE *file = mini_fopen(nfile, 'a');
    if(file == NULL) {
        mini_perror("Erreur lors de la création du fichier. \n");
    }
    else {
        // Fermeture du fichier
        if(mini_fclose(file) == -1) {
            mini_perror("mini_fclose() ");
        }
    }
}