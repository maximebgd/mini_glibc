#include "mini_lib.h"

int IOBUFFER_SIZE = 2048;
MYFILE *file_list = NULL;


MYFILE* mini_fopen(char* file, char mode) {
    if(file == NULL) return NULL;
    // Alloue la mémoire pour la structure MYFILE
    MYFILE *f = mini_calloc(sizeof(MYFILE), 1);
    if(f==NULL) mini_perror("mini_calloc() ");
    MYFILE *mycontent = mini_calloc(sizeof(MYFILE), 1);
    if(mycontent==NULL) mini_perror("mini_calloc() ");

    // Détermine le mode d'ouverture du fichier en fonction de la valeur de 'mode'
    switch(mode) {
        case 'r': // Ouverture en lecture
            f->fd = open(file, O_RDONLY);
            break;
        case 'w': // Ouverture en écriture
            f->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
            break;
        case 'b': // Ouverture en lecture/écriture
            f->fd = open(file, O_RDWR);
            break;
        case 'a': // Ouverture en ajout à la fin du fichier
            f->fd = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
            break;
        default :
            // Affiche un message d'erreur si le mode n'est pas valide et libère la mémoire allouée
            mini_printf("Le mode n'est pas valide !");
            mini_free(f);
            return NULL;
    }

    // Vérifie si l'ouverture du fichier a échoué
    if (f->fd == -1) {
        mini_perror("open() ");
        mini_free(f);
        return NULL;
    }

    // Initialise les autres champs de la structure MYFILE
    f->ind_read = -1;
    f->ind_write = -1;
    f->buffer_read = NULL;
    f->buffer_write = NULL;
    f->next_file = NULL;

    // Ajoute le fichier à la liste des fichiers ouverts
    if (file_list == NULL) { // Cas 1 : c'est le premier fichier ouvert
        file_list = f;
    }
    else { // Cas 2 : il y a déjà d'autres fichiers ouverts
        mycontent = file_list; // on copie ce qu'il y avait dans notre liste
        while (mycontent->next_file != NULL) { // parcours de la liste
            mycontent = mycontent->next_file;
        }
        mycontent->next_file = f; // on ajoute notre fichier à la fin de la liste 
    }

    // Renvoie le pointeur vers la structure MYFILE représentant le fichier ouvert
    return f;
}


int mini_fread(void* buffer, int size_element, int number_element, MYFILE* file) {
    int buffer_size = size_element * number_element;
    int i = 0;

    // Si l'index de lecture est -1, le buffer de lecture n'est pas encore alloué
    if (file->ind_read == -1) {
        file->buffer_read = mini_calloc(IOBUFFER_SIZE, 1); // Allocation du buffer de lecture
        if(file->buffer_read == NULL) mini_perror("mini_calloc() ");
        file->ind_read = 0; // Initialisation de l'index de lecture à 0
    }

    // Boucle principale pour lire les éléments dans le buffer de destination
    while (i < buffer_size) {
        // Si l'index de lecture atteint la fin du buffer de lecture, on le remet à 0
        if (file->ind_read == IOBUFFER_SIZE) {
            file->ind_read = 0;
        }

        // Si l'index de lecture est à 0, alors on va lire un nouveau bloc de données dans le buffer de lecture
        if (file->ind_read == 0) {
            // On utilise read pour lire IOBUFFER_SIZE éléments dans le buffer de lecture
            if (read(file->fd, file->buffer_read, IOBUFFER_SIZE) == -1) {
                // En cas d'erreur lors de la lecture, retourne -1
                return -1;
            }
        }

        // Copie de l'élément du buffer de lecture vers le buffer de destination
        ((char*)buffer)[i] = ((char*)file->buffer_read)[file->ind_read];
        // Incrémentation de l'index de lecture
        file->ind_read++;
        // Incrémentation de l'index dans le buffer de destination
        i++;
    }

    // Retourne le nombre total d'éléments lus
    return i;
}


int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE* file) {
    int buffer_size = size_element * number_element;
    int i = 0;
    
    // Si l'index d'écriture est -1, le buffer d'écriture n'est pas encore alloué
    if(file->ind_write == -1) {
        file->buffer_write = mini_calloc(IOBUFFER_SIZE, 1); // Allocation du buffer d'écriture
        if(file->buffer_write == NULL) mini_perror("mini_calloc() ");
        file->ind_write = 0; // Initialisation de l'index d'écriture à 0
    }

    // Boucle principale pour écrire les éléments dans le buffer d'écriture
    while(i < buffer_size) {
        // Si l'index d'écriture atteint la fin du buffer d'écriture, on le remet à 0
        if(file->ind_write == IOBUFFER_SIZE) {
            // Utilisation de write pour écrire IOBUFFER_SIZE éléments dans le fichier
            if(write(file->fd, file->buffer_write, IOBUFFER_SIZE) == -1) {
                return -1; // En cas d'erreur lors de l'écriture, retourne -1
            }
            file->ind_write = 0;
            //mini_printf("Ecrit par mini_fwrite ! \n");
        }

        // Copie de l'élément du buffer vers le buffer d'écriture
        ((char*)file->buffer_write)[file->ind_write] = ((char*)buffer)[i];
        file->ind_write++; // Incrémentation de l'index d'écriture
        i++; // Incrémentation de l'index dans le buffer de destination
    }
    return i; // Retourne le nombre total d'éléments écrits
}


int mini_fflush(MYFILE* file) {
    // Utilisation de write pour écrire les données non écrites dans le fichier
    lseek(file->fd, -1, SEEK_CUR); // sans le lseek, on a un caractère qui gène dans le .txt
    if(write(file->fd, file->buffer_write, file->ind_write) == -1) {
        return -1; // En cas d'erreur lors de l'écriture, retourne -1
    }

    // Puis on vide le buffer_write, car les données on été écrite 
    for(int i=0; i < IOBUFFER_SIZE; i++) {
        ((char*)file->buffer_write)[i] = '\0';
    }

    // Réinitialise l'index d'écriture à 0
    int nb_flush = file->ind_write;
    file->ind_write = 0;

    return nb_flush; // Retourne le nombre de caractères écrits
}


int mini_fclose(MYFILE *file) {
    // Vérifie si le pointeur de fichier est NULL
    if (file == NULL) {
        return -1; // On ne fait rien dans ce cas
    }

    MYFILE* mycontent = file_list; // On "sauvegarde" les éléments actuels de la liste
    
    // Parcours de la liste jusqu'à trouver le bloc correspondant au pointeur à libérer
    while (mycontent != NULL) {
        if (mycontent == file) {
            mini_fflush(mycontent); // Effectue un flush du buffer d'écriture
            delete_file(&file); // Supprime le fichier de la liste
            close(mycontent->fd); // Utilise l'appel système close pour fermer le fichier

            return 0; // Succès
        }
        mycontent = mycontent->next_file;
    }

    return -1; // Le fichier n'a pas été trouvé dans la liste
}

// Fonction en plus :
void delete_file(MYFILE** target) {
    // Vérifie si le pointeur cible est NULL
    if (target == NULL) {
        return; // La liste est vide ou l'élément à supprimer est nul
    }

    MYFILE* mycontent = file_list;
    MYFILE* prev_file = NULL;

    // Si l'élément à supprimer est en tête de liste
    if (mycontent == *target) {
        file_list = mycontent->next_file;
        mycontent->next_file = NULL;
        *target = NULL; // Mise à jour du pointeur cible
        return;
    }

    // Recherche de l'élément précédent dans la liste
    while (mycontent != NULL) {
        if (mycontent == *target) {
            prev_file->next_file = mycontent->next_file;
            mycontent->next_file = NULL;
            *target = NULL; // Mise à jour du pointeur cible
            break;
        }

        prev_file = mycontent;
        mycontent = mycontent->next_file;
    }
}


int mini_fgetc(MYFILE *file) {
    // Vérifie si le pointeur de fichier est NULL
    if (file == NULL) {
        return -1; // On ne fait rien dans ce cas
    }

    char *c = mini_calloc(sizeof(char), 1);
    if(c == NULL) mini_perror("mini_calloc() ");
    int test = mini_fread(c, sizeof(char), 1, file);
    if(test == 0 || test == -1) {
        return -1;
    }
    // On utilise mini_fread pour lire le caracètre dans le fichier 
    /*if (mini_fread(c, sizeof(char), 1, file) == -1) {
        return -1; // En cas d'erreur lors de la lecture
    }*/

    // En cas de succès
    return (int)(*c); 
}


int mini_fputc(MYFILE* file, char c) {
    // Vérifie si le pointeur de fichier est NULL
    if (file == NULL) {
        return -1; // On ne fait rien dans ce cas
    }
    
    // On utilise mini_fwrite pour écrire le caractère dans le fichier
    if (mini_fwrite(&c, sizeof(char), 1, file) == -1) {
        return -1; // En cas d'erreur lors de l'écriture
    }

    return 0; // En cas de succès
}


// Fonction en plus :
// Exercice 34 : (utilisé dans le mini_exit())
void flush_all_files() {
    // Démarre à partir du premier fichier dans la liste des fichiers ouverts
    MYFILE* current = file_list;

    // Parcours de tous les fichiers ouverts dans la liste
    while (current != NULL) {
        // Vérifie si le fichier a un buffer d'écriture non vide et des données en attente d'écriture
        if (current->buffer_write != NULL && current->ind_write > 0) {
            // Appelle mini_fflush pour forcer l'écriture des données dans le fichier
            mini_fflush(current);
        }

        // Passe au fichier suivant dans la liste
        current = current->next_file;
    }
}
