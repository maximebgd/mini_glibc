#include "mini_lib.h"

#define TAILLE_BUFFER 2048

void mini_cp(char* src, char* dest) {
    char buffer[TAILLE_BUFFER];
    size_t info_lu;

    // Ouvrir le fichier source en mode lecture
    MYFILE *fsrc = mini_fopen(src, 'r');
    if(fsrc == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier source. \n");
        return;
    }
    int size_src = sizeoffile(src);

    // Ouvrir le fichier destination en mode écriture
    MYFILE *fdest = mini_fopen(dest, 'w');
    if(fdest == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier destination. \n");
        mini_fclose(fsrc);
        return;
    }

    // Lire du fichier source dans le buffer
    if((info_lu = mini_fread(buffer, 1, size_src+1, fsrc)) == -1) {
        mini_perror("Erreur lors de la lecture du fichier source. \n");
    }

    // Écrire le contenu du buffer dans le fichier destination
    if(mini_fwrite(buffer, 1, info_lu, fdest) == -1) {
        mini_perror("Erreur lors de l'écriture dans le fichier destination. \n");
    }

    // Fermer les fichiers
    if(mini_fclose(fsrc) == -1) mini_perror("Erreur lors de la fermeture du fichier source. \n");
    if(mini_fclose(fdest) == -1) mini_perror("Erreur lors de la fermeture du fichier destination. \n");
}