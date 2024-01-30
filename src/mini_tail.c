#include "mini_lib.h"

#define TAILLE_BUFFER 2048

void mini_tail(int N, char* nfile) {
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
    else if (N >= nb_ligne(nfile)) {
        mini_printf(buffer); mini_printf("\n"); // affiche tout le contenu du fichier
    } 
    // Sinon, on affiche les N dernières lignes
    else {
        int cmpt = 0; 
        int last_newline_index = -1; 

        // Parcourt le buffer à l'envers pour trouver l'index de la dernière ligne parmi les N dernières
        for (int i = nb - 1; i >= 0; i--) {
            if (buffer[i] == '\n') {
                cmpt++;
                if (cmpt == N) {
                    last_newline_index = i;
                    break;
                }
            }
        }

        // Affiche les N dernières lignes du fichier
        if (last_newline_index != -1) {
            mini_printf(&buffer[last_newline_index + 1]);  // +1 pour ne pas inclure le caractère '\n'
        } else {
            // Si le dernier '\n' n'est pas trouvé, cela signifie que le fichier contient moins de N lignes
            // Dans ce cas, affiche tout le contenu du fichier
            mini_printf(buffer); 
        }
        mini_printf("\n");
    }

    // Ferme le fichier
    if(mini_fclose(file) == -1) mini_perror("mini_close() ");
}