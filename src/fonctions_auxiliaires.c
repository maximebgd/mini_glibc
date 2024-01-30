#include "mini_lib.h"

#define TAILLE_BUFFER 2048


void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}


char* reverse(char *buffer, int start, int end) {
    while (start < end) {
        swap(&buffer[start++], &buffer[end--]);
    }

    return buffer;
}


char* int_to_char(int value, char* buffer, int base) {
    if (base < 2 || base > 32) {
        return buffer;
    }

    int i = 0;

    // Traitement des nombres négatifs
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
        value = -value;
    }

    do {
        int remainder = value % base;

        if (remainder >= 10) {
            buffer[i++] = 'A' + (remainder - 10);
        } else {
            buffer[i++] = '0' + remainder;
        }

        value /= base;
    } while (value > 0);

    buffer[i] = '\0';

    // Inversion des caractères dans la chaîne (sauf le signe négatif)
    if (buffer[0] == '-') {
        int start = 1;
        int end = i - 1;

        while (start < end) {
            char temp = buffer[start];
            buffer[start] = buffer[end];
            buffer[end] = temp;

            start++;
            end--;
        }
    } else {
        int start = 0;
        int end = i - 1;

        while (start < end) {
            char temp = buffer[start];
            buffer[start] = buffer[end];
            buffer[end] = temp;

            start++;
            end--;
        }
    }

    return buffer;
}


int char_to_int(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Gérer les caractères d'espacement au début
    while (str[i] == ' ') {
        i++;
    }

    // Gérer le signe '+' ou '-'
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    // Convertir les chiffres en entier
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return sign * result;
}


// Fonction en plus pour toutes les commandes shell :
int nb_ligne(char* nfile) {
    char buffer[TAILLE_BUFFER];

    // Vérifie si le nom de fichier est valide
    if (nfile == NULL || mini_strlen(nfile) == 0) {
        mini_perror("Nom de fichier incorrect. \n");
        return -1;
    }

    // Ouvre le fichier en mode lecture
    MYFILE* file = mini_fopen(nfile, 'r');
    if (file == NULL) {
        // En cas d'erreur d'ouverture, affiche un message d'erreur et quitte la fonction
        mini_perror("mini_fopen() ");
        return -1;
    }

    // Lit les données du fichier pour les mettre dans le buffer
    int nb = mini_fread(buffer, 1, sizeof(buffer), file);
    if(nb == -1) mini_perror("mini_fread() ");
    int nb_ligne = 1;
    // Parcourt le buffer pour compter le nombre de lignes
    for (int i = 0; i < nb; i++) {
        if (buffer[i] == '\n') {
            nb_ligne++;
        }
    }

    // Ferme le fichier
    mini_fclose(file);

    return nb_ligne;
}


int sizeoffile(char *file) {
    struct stat s;
    
    if(stat(file, &s) == 0) {
        return s.st_size;
    }
    else return -1;
}