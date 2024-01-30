#include "mini_lib.h"

#define TAILLE_BUFFER 2048

void mini_wc(char* nfile) {
    char buffer[TAILLE_BUFFER];

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

    // Lit les données du fichier pour les mettre dans le buffer
    int nb = mini_fread(buffer, 1, sizeoffile(nfile), file);
    if(nb == -1) {
        mini_perror("mini_fread() ");
    }

    int wc = 0; int in = 0; int i = 0;
    // V1 (fonctionne à moitié)
    /*for (int i = 0; i < nb; i++) {
        // On "filtre" nos cas pour compter un mot que dans certaines conditions !
        if((buffer[i] == ' ' && buffer[i+1] != ' ' && buffer[i+1] != '\n' && buffer[i+1] != '\0')
            || (buffer[i] == '\n' && buffer[i+1] != ' ' && buffer[i+1] != '\n' && buffer[i+1] != '\0')) {
            word_cmpt++;
        }
    }*/
    while(buffer[i] != '\0') {
        if(buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n' || buffer[i] == '\r') {
            in = 0;
        }
        else {
            if(!in) {
                wc++; in = 1;
            }
        }
        i++;
    }

    // Affiche le nombre de mots
    char tab[10]; int_to_char(wc, tab, 10); // création de variable & utilisation de fonction pour mettre au bon format
    mini_printf("Nombre de mots dans le fichier '"); mini_printf(nfile); mini_printf("' est : "); mini_printf(tab); mini_printf("\n");

    // Ferme le fichier
    if(mini_fclose(file) == -1) mini_perror("mini_close() ");
}