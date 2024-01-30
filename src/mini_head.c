#include "mini_lib.h"

#define TAILLE_BUFFER 2048

void mini_head(int N, char* nfile) {
    char buffer[TAILLE_BUFFER];

    // Vérifie si le nom de fichier est valide
    if (nfile == NULL || mini_strlen(nfile) == 0) {
        mini_perror("Nom de fichier incorrect. \n");
        return;
    }

    // Ouvre le fichier en mode lecture
    MYFILE* file = mini_fopen(nfile, 'r');
    if (file == NULL) {
        // En cas d'erreur d'ouverture, affiche un message d'erreur et quitte la fonction
        mini_perror("mini_fopen() ");
        return;
    }

    // Lit les données du fichier pour les mettre dans le buffer
    int nb = mini_fread(buffer, 1, sizeof(buffer), file);
    if(nb == -1) {
        mini_perror("mini_fread() ");
    }

    // Si le nombre de ligne est <= 0, dans ce cas on affiche rien
    if (N <= 0) {
        mini_printf("\n");
    }
    // Si le nombre de lignes demandées est supérieur au nombre total de lignes dans le fichier,
    // affiche tout le contenu du fichier
    else if (N >= nb_ligne(nfile)) {
        mini_printf(buffer); mini_printf("\n");
    } 
    // Sinon, on affiche le nombre de ligne demandées
    else {
        int cmpt = 0; 
        char buffer_filtre[TAILLE_BUFFER];

        // Parcourt le buffer pour trouver l'index de la dernière ligne parmi les N premières
        for (int i = 0; i < nb; i++) {
            if (buffer[i] == '\n') {
                cmpt++;
                buffer_filtre[i] = '\n';
                if (cmpt == N) {
                    break;
                }
            }
            buffer_filtre[i] = buffer[i];
        }

        // Affiche les N premières lignes du fichier
        mini_printf(buffer_filtre); 
    }

    // Ferme le fichier
    if(mini_fclose(file) == -1) mini_perror("mini_fclose() ");
}