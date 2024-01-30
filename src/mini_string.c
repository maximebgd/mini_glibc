#include "mini_lib.h"

#define BUF_SIZE 2048

char *buffer;
int ind = -1;
int j=0;


// Version 1 (il faut vider le buffer pour le \n dans le mini_exit())
void mini_printf(char *s) {
    if(ind == -1) { // Cas 1 : Première appel
        // On alloue de la mémoire au buffer
		buffer = mini_calloc(1, BUF_SIZE+1); // 1024 caracètre + 1 pour le '\0' 
		if(buffer==NULL) {
            mini_perror("mini_calloc() "); // erreur
		}
		ind=0; // La première case vide du tampon est donc la case n°0
	}

    for(int i = 0; s[i] != '\0'; i++) { // Parcours de toute la chaîne de caractères "s"
        if(s[i] == '\n' || ind == BUF_SIZE) { // Si on rencontre '\n' ou que le buffer est rempli
            if(write(STDOUT_FILENO, buffer, ind+1) == -1) { // On affiche le tampon avec write
                mini_perror("write() ");
            }
            //printf("--- JE SUIS DANS LE PRINTF \n");
            // On vide le tampon correctement :
            ind = -1;
            for(int i = 0; i < BUF_SIZE + 1; i++) {
                buffer[i] = '\0';
            }
        }
        ind++; // On met à jour la première case vide du tampon au fur et à mesure qu'on le remplit
        buffer[ind] = s[i]; // On remplit le tampon
    }
}

// Version 2 Pour afficher que un caracètre proprement
void mini_printf_c(char c) {
    char tmp[2];
    tmp[1] = '\0';
    tmp[0] = c;
    mini_printf(&tmp[0]);
}


int mini_scanf(char *fbuffer, int size_buffer) { 
    if (fbuffer == NULL || size_buffer <= 0) {
        return -1;  // paramètres invalides
    }
    
    int cmpt = 0; char c;
    while (cmpt < size_buffer) {
        if(read(STDIN_FILENO, &c, 1) < 0) {
            mini_perror("read() ");
            break;
        }

        fbuffer[cmpt++] = c;

        if(c == '\n') {
            break; // Fin de la saisie lorsqu'un retour à la ligne est rencontré
        }
    }
    
    fbuffer[cmpt] = '\0'; // Ajout du caractère de fin de chaîne
    return cmpt; // Retourne le nombre de caractères lus
}

int mini_strlen(char *s) {
    if (s == NULL) { // Cas où s serait NULL
        return -1;
    }

    int len = 0;
    // Parcours de la chaîne jusqu'au caractère nul ('\0')
    while (*s != '\0') {
        len++;
        s++;
    }

    return len;
}

int mini_strcpy(char* s, char* d) {
    /// assert(s != NULL && d != NULL); 
    if(s == NULL || d == NULL) { // Vérification des pointeurs non NULL
        return -1; // Cas d'erreur
    }
    
    int cmpt = 0;
    while (*s != '\0') { 
        *d = *s;
        cmpt++;
        s++;
        d++;
    }
    *d = '\0'; // On ajoute le caractère nul à la fin de la chaîne de destination

    return cmpt; // nb caracètre copiés
}

int mini_strcmp(char* s1, char* s2) {
    if(s1 == NULL || s2 == NULL) {
        return -1; // Cas d'erreur
    }

    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }

    return (*s1 > *s2) - (*s1 < *s2); // pour retourner 1, -1 ou 0 
}

void mini_perror(char *mess) {
    mini_printf(mess); // on affiche le message d'erreur
    
    char errno_buffer[50];  // taille suffisante pour stocker un code errno 
    int_to_char(errno, errno_buffer, 10); // on met le code errno dans le buffer 
    mini_printf("---> Code d'erreur (errno) : "); mini_printf(errno_buffer); // on affiche le code d'erreur
    mini_printf("\n");
}


// Fonction au plus :
void vidage_buffer() {
    if(buffer != NULL) {
        // 1 : On affiche ce qu'il y a dans le buffer 
        write(STDOUT_FILENO, buffer, BUF_SIZE+1);
        //printf("--- JE SUIS DANS LE VIDAGE \n");

        // 2 : On met \0 partout pour que le buffer soit propre
        for(int i=0; i<BUF_SIZE+1; i++) {
            buffer[i] = '\0';
        }
    }
}
