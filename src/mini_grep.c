#include "mini_lib.h"

#define TAILLE_BUFFER 2048

void mini_grep(char* mot, char* nfile) {
    char buffer[TAILLE_BUFFER];
    char buffer_filtre[TAILLE_BUFFER];  // Nouveau buffer pour filtrer les lignes

    // Vérifie si le nom de fichier est valide
    if (nfile == NULL || mini_strlen(nfile) == 0) {
        mini_perror("Nom de fichier incorrect. \n");
        return;
    }

    // Ouvre le fichier en mode lecture
    MYFILE* file = mini_fopen(nfile, 'r');
    if (file == NULL) {
        mini_perror("mini_fopen() ");
        return;
    }

    // Initialisation du buffer_filtre
    for (int i = 0; i < TAILLE_BUFFER; i++) {
        buffer_filtre[i] = '\0';
    }

    // Lit les données du fichier pour les mettre dans le buffer
    int nb = mini_fread(buffer, 1, sizeof(buffer), file);
    if(nb == -1) {
        mini_perror("mini_fread() ");
    }

    int j = 0;     // Index de la chaîne de caractères à rechercher
    int ind = -1;  // Indice du dernier saut de ligne rencontré

    // Parcours du buffer pour la recherche de la chaîne
    for (int i = 0; i < nb; i++) {
        if (buffer[i] == '\n') {
            ind = i;
        }

        // Comparaison caractère par caractère avec la chaîne à rechercher
        if (buffer[i] == mot[j]) {
            j++;
        } else {
            j = 0;
        }

        // Si la chaîne complète est trouvée
        if (j == mini_strlen(mot)) {
            // Copie la ligne contenant le mot dans le buffer_filtre
            for (int k = ind + 1, l = 0; buffer[k] != '\n' && buffer[k] != '\0'; k++, l++) {
                buffer_filtre[l] = buffer[k];
            }

            // Affiche la ligne du buffer_filtre
            mini_printf(buffer_filtre);
            mini_printf("\n");

            // Nettoie le buffer_filtre
            for (int k = 0; k < TAILLE_BUFFER; k++) {
                buffer_filtre[k] = '\0';
            }

            // Réinitialise l'index de la chaîne à rechercher
            j = 0;
        }
    }
    // Ferme le fichier
    if(mini_fclose(file) == -1) mini_perror("mini_close() ");
}