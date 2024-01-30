/**
 * @file mini_lib.h
 * @author Maxime BEGOUD 
 * @brief 
 * @version 1.0
 * @date 2024-01-06
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef MINI_LIB_H
#define MINI_LIB_H

// !! Pour masquer l'erreur de sbrk !!
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>


// 1.1 Gestion de la mémoire
typedef struct malloc_element { 
    void* zone_alloue; 
    size_t size;
    int statut;
    struct malloc_element* next_malloc;
} malloc_element;

/**
 * Alloue de la mémoire et initialise ses éléments à zéro (avec sbrk)
 *
 * @param size_element La taille en octets d'un élément.
 * @param number_element Le nombre d'éléments à allouer.
 * @return Un pointeur vers la zone mémoire allouée, ou NULL en cas d'échec.
 */
void* mini_calloc(int size_element, int number_element);

/**
 * Marque le bloc comme non utilisé précédement alloué par mini_calloc.
 *
 * @param ptr Le pointeur vers la zone mémoire à libérer.
 */
void mini_free(void *ptr);

/**
 * Fonction pour terminer proprement le programme.
 * Vidage du buffer, flush des fichers et met fin au programme
 */
void mini_exit();


// Fonction en plus :
/**
 * Réservation d'un bloc de mémoire.
 *
 * @param myelm Le dernier élément de la liste de blocs de mémoire (peut être NULL si la liste est vide).
 * @param size La taille de la mémoire à allouer.
 * @return Un pointeur vers la structure malloc_element représentant le bloc alloué.
 */
malloc_element* reserver_block(malloc_element* myelm, size_t size);

/**
 * Recherche un bloc de mémoire disponible dans la liste de blocs alloués.
 *
 * @param myelm Pointeur vers le dernier élément examiné dans la liste.
 * @param size La taille de la mémoire requise.
 * @return Un pointeur vers la structure malloc_element du bloc trouvé ou NULL s'il n'y a pas de bloc disponible.
 */
malloc_element* recherche_block(malloc_element** myelm, size_t size);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 1.2 Gestion des chaînes de caracètres
/**
 * Fonction pour afficher des chaînes de caractères (avec gestion de tampon).
 * @param s Chaîne de caractères à afficher.
 */
void mini_printf(char* mess);

/**
 * Fonction pour afficher un seul caractère proprement
 * @param c Le caractères à afficher.
 */
void mini_printf_c(char c);

/**
 * Fonction pour la saisie de texte depuis l'entrée standard.
 * @param fbuffer Pointeur vers le tampon de destination.
 * @param size_buffer Taille du tampon de destination.
 * @return Le nombre de caractères lus, -1 en cas d'erreur
 */
int mini_scanf(char *fbuffer,int size_buffer);

/**
 * Calcule la longueur d'une chaîne de caractères.
 *
 * @param s La chaîne de caractères dont on veut connaître la longueur.
 * @return La longueur de la chaîne (avant caracètre de fin de chaine), -1 en cas d'erreur
 */
int mini_strlen(char *s);

/**
 * Copie la chaîne source dans la chaîne destination.
 *
 * @param s La chaîne source.
 * @param d La chaîne destination.
 * @return Le nombre de caracètre copié, -1 en cas d'erreur
 */
int mini_strcpy(char* s,char* d);

/**
 * Compare deux chaînes de caractères.
 *
 * @param s1 La première chaîne à comparer.
 * @param s2 La seconde chaîne à comparer.
 * @return Retourne un nombre <0 si "s1" est plus petite que "s2"
 *         Retourne 0 si "s1" = "s2"
 *         Retourne un nombre >0 si "s1" est plus grande que "s2"
 *         Retourne -1 en cas d'erreur
 */
int mini_strcmp(char* s1,char* s2);

/**
 * Fonction pour afficher un message d'erreur ainsi que le numéro erno 
 * de l'erreur correspondante
 * 
 * @param mess Message d'erreur à afficher
 */
void mini_perror(char *mess);


// Fonction en plus
/**
 * Permet d'afficher le contenu du tampon (buffer) et de le vider.
 */
void vidage_buffer();

/**
 * @brief 
 * 
 * @param s La chaine source
 * @param d La chaine destination
 * @param n Nombre de caracètre à copier
 * @return Nombre de caracètre copié, -1 en cas d'erreur
 */
int mini_strncpy(char* s, char* d, int n);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 1.3 Gestion des entrées/sorties
typedef struct MYFILE{
    int fd; // le descripteur de fichier obtenu via open
    void *buffer_read; // le buffer contenant les données lues
    void *buffer_write; // le buffer contenant les données à écrire
    int ind_read; // l'indexe actuel dans le buffer_read, -1 ==> buffer pas alloué
    int ind_write; // l'indexe actuel dans le buffer_write, -1 ==> buffer pas alloué
	struct MYFILE *next_file;
} MYFILE;

/**
 * Ouvre un fichier avec le mode spécifié et renvoie une structure MYFILE correspondante.
 *
 * @param file Le nom du fichier à ouvrir.
 * @param mode Le mode d'ouverture du fichier ('r' pour lecture, 'w' pour écriture, 'b' pour lecture/écriture, 'a' pour ajout à la fin).
 * @return Un pointeur vers la structure MYFILE représentant le fichier ouvert, ou NULL en cas d'erreur.
 */
MYFILE* mini_fopen(char* file, char mode);

/**
 * Lit des éléments depuis un fichier spécifié par MYFILE en utilisant une lecture bufferisée.
 *
 * @param buffer Le pointeur vers le buffer de destination où les données lues seront stockées.
 * @param size_element La taille d'un élément à lire.
 * @param number_element Le nombre d'éléments à lire.
 * @param file Le pointeur vers la structure MYFILE représentant le fichier.
 * @return Le nombre total d'éléments lus ou -1 en cas d'erreur.
 */
int mini_fread(void* buffer,int size_element, int number_element, MYFILE* file);

/**
 * Écrit des éléments dans un fichier spécifié par MYFILE en utilisant une écriture bufferisée.
 *
 * @param buffer Le pointeur vers le buffer contenant les données à écrire.
 * @param size_element La taille d'un élément à écrire.
 * @param number_element Le nombre d'éléments à écrire.
 * @param file Le pointeur vers la structure MYFILE représentant le fichier.
 * @return Le nombre total d'éléments écrits ou -1 en cas d'erreur.
 */
int mini_fwrite(void* buffer,int size_element, int number_element, MYFILE* file);

/**
 * Force l'écriture des données non écrites présentes dans le buffer d'écriture de MYFILE.
 *
 * @param file Le pointeur vers la structure MYFILE représentant le fichier.
 * @return Le nombre de caractères écrits ou -1 en cas d'erreur.
 */
int mini_fflush(MYFILE *file);

/**
 * Ferme le fichier spécifié, effectue un flush du buffer d'écriture,
 * le supprime de la liste des fichiers ouverts, et utilise l'appel système close pour le fermer.
 *
 * @param file Un pointeur vers la structure MYFILE représentant le fichier à fermer.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int mini_fclose(MYFILE *file);

/**
 * Lit un caractère depuis le fichier spécifié par MYFILE.
 *
 * @param file Un pointeur vers la structure MYFILE représentant le fichier.
 * @return Le caractère lu (converti en entier), ou -1 en cas d'erreur.
 */
int mini_fgetc(MYFILE *file);

/**
 * Écrit un caractère dans le fichier spécifié par MYFILE.
 *
 * @param file Le pointeur vers la structure MYFILE représentant le fichier.
 * @param c Le caractère à écrire dans le fichier.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int mini_fputc(MYFILE* file, char c);


// Fonction en plus :
/**
 * Fonction pour flusher tous les fichiers ouverts.
 * Parcours la liste des fichiers ouverts et force l'écriture des données en attente.
 * Fonction utilisé avec mini_exit()
 */
void flush_all_files();

/**
 * Supprime un élément spécifié de la liste chaînée file_list.
 * Fonction utilisé avec mini_fclose()
 *
 * @param target Un pointeur double vers l'élément à supprimer.
 *               La fonction met à jour la liste et le pointeur est défini à NULL après la suppression.
 */
void delete_file(MYFILE** target);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 2.0 Commandes Système
/**
 * Créer un fichier vide (si il était inexistant)
 * 
 * @param nfile Le nom du fichier en question
 */
void mini_touch(char* nfile);

/**
 * Réalise la copie du fichier src dans dest 
 * 
 * @param src Le nom du fichier source
 * @param dest Le nom du fichier dest
 */
void mini_cp(char* src, char* dest);

/**
 * Fonction qui renvoie la taille réel d'un fichier
 * 
 * @param file 
 * @return taille du fichier en octets ou -1 en cas d'erreur
 */
int sizeoffile(char *file);

/**
 * Affiche le contenu d'une chaîne de caractères.
 *
 * @param mess Un pointeur vers la chaîne de caractères à afficher.
 */
void mini_echo(char* mess);

/**
 * Affiche le contenu d'un fichier.
 *
 * @param nfile Le nom du fichier à afficher.
 */
void mini_cat(char* nfile);

/**
 * Affiche les N premières lignes d'un fichier spécifié par le nom du fichier.
 *
 * @param nfile Le nom du fichier à traiter.
 * @param N Le nombre de premières lignes à afficher.
 */
void mini_head(int N, char* nfile);

/**
 * Affiche les N dernières lignes d'un fichier spécifié par le nom du fichier.
 *
 * @param nfile Le nom du fichier à traiter.
 * @param N Le nombre de dernière lignes à afficher.
 */
void mini_tail(int N, char* nfile);

/**
 * Crée un fichier vide ou réinitialise un fichier existant.
 *
 * @param nfile Le nom du fichier à créer ou réinitialiser.
 */
void mini_clean(char* nfile);

/**
 * Recherche une chaîne de caractères dans un fichier et affiche les lignes
 * contenant cette chaîne.
 *
 * @param mot La chaîne de caractères à rechercher.
 * @param nfile Le nom du fichier à analyser.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
void mini_grep(char* mot, char* nfile);

/**
 * Affiche le nombre de mots dans un fichier spécifié par le nom du fichier.
 *
 * @param nfile Le nom du fichier à traiter.
 */
void mini_wc(char* nfile);


// Fonction en plus :
/**
 * Compte le nombre de lignes dans un fichier spécifié par le nom du fichier.
 * Fonction utilisé dans le mini_head() et mini_tail()
 *
 * @param nfile Le nom du fichier à traiter.
 * @return Le nombre de lignes dans le fichier, ou -1 en cas d'erreur.
 */
int nb_ligne(char* nfile);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 3.0 SHELL
/** 
 * Fonction qui lance notre mini_shell qui nous permet d'exécuter les fonctions 
 * tel que mini_echo, mini_cat...
 */
void mini_shell();


// Fonction en plus :
/**
 * Fonction pour diviser la grande ligne de commande en une partie
 * commande et une autre partie pour les arguments
 * 
 * @param full_command Chaine contenant la commande "brute"
 * @param command Chaine contenant uniquement la commande que l'on veut exécuter
 * @param args Tableau de chaine de caracètère qui contient tous nos arguments
 * @param argc Nombre d'argument au total
 */
void split_command(char *full_command, char *command, char *args[], int *argc);

/**
 * Permet d'exécuter la commande en fonction des arguments
 * 
 * @param command La commande sous forme d'une chaine de caractère
 * @param args Tableau de chaine de caractère contenant nos arguments pour la commande
 * @param argc Nombre d'argument
 */
void execute_command(char *command, char *args[], int argc);

/**
 * Fonction qui permet d'afficher de l'aider pour le mini_shell.
 * Peut soit afficher l'aide général, soit de l'aide pour une fonction précisément. 
 * 
 * @param nfonc Nom de la fonction où l'on veut avoir de l'aide ou "" si on veut de l'aide général
 */
void mini_help(char* nfonc);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Partie "fonctions_auxiliaires.c" :
/** 
 * Permute les valeurs de deux variables de type char.
 *
 * @param x Pointeur vers la première variable.
 * @param y Pointeur vers la deuxième variable.
 */
void swap(char *x, char *y);

/** 
 * Inverse l'ordre des caractères dans une portion d'un tableau de caractères.
 *
 * @param buffer Tableau de caractères à modifier.
 * @param start Indice du début de la portion à inverser.
 * @param end Indice de fin de la portion à inverser.
 * @return Pointeur vers le tableau de caractères modifié.
 */
char* reverse(char *buffer, int i, int j);

/**
 * Convertit un entier en chaîne de caractères avec la base spécifiée
 *
 * @param value La valeur entière à convertir.
 * @param buffer Le tampon où stocker la chaîne résultante.
 * @param base La base de conversion, comprise entre 2 et 32 inclus.
 * @return Pointeur vers la chaîne de caractères résultante.
 */
char* int_to_char(int value, char* buffer, int base);

/**
 * @brief Convertit une chaîne de caractères en entier.
 *
 * @param str La chaîne de caractères à convertir.
 * @return La valeur entière résultante.
 */
int char_to_int(const char *str);



void mini_clear(char* nfile);


#endif