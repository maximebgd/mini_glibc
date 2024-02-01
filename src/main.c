/**
 * @file main.c
 * @author Maxime BEGOUD 
 * @brief 
 * @version 1.0
 * @date 2024-01-06
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "mini_lib.h"


int main(int argc, char **argv) {
    
    // Exercice 12 : Test de mini_calloc & mini_free
    // Test n°1 :
    // Je procède à l'allocation de trois emplacements mémoire. Ensuite, je libère l'emplacement du milieu et teste si 
    // je peux réallouer cet espace mémoire avec une taille égale ou inférieure.
    /*char *p1 = mini_calloc(1, 101);
    if(p1 == NULL) return 0;
    printf("p1 : %p \n", p1);

    char *p2 = mini_calloc(1, 102);
    if(p2 == NULL) return 0;
    printf("p2 : %p \n", p2);

    char *p3 = mini_calloc(1, 103);
    if(p3 == NULL) return 0;
    printf("p3 : %p \n", p3);

    mini_free(p2); printf("--> p2 est free ! \n");

    char *p4 = mini_calloc(1, 102);
    printf("p4 : %p (doit être p2) \n", p4);

    mini_free(p4); printf("--> p4 est free ! \n");

    char *p5 = mini_calloc(1, 10);
    printf("p5 : %p (doit être p2 & p4) \n", p5);

    mini_free(p1); mini_free(p3); mini_free(p5); */

    // Test n°2 :
    // Je réserve trois emplacements mémoire (p1, p2, p3) puis les libère. Ensuite, je réalloue des espaces mémoire (p11, p22, p33) 
    // pour vérifier s'ils reprennent les emplacements libérés précédemment. Enfin, je libère ces nouveaux emplacements.
    /*char *p1 = mini_calloc(1, 101);
    if(p1 == NULL) return 0;
    printf("p1 : %p \n", p1);
    char *p2 = mini_calloc(1, 102);
    if(p2 == NULL) return 0;
    printf("p2 : %p \n", p2);
    char *p3 = mini_calloc(1, 103);
    if(p3 == NULL) return 0;
    printf("p3 : %p \n", p3);

    mini_free(p1); mini_free(p2); mini_free(p3);
    printf("p1, p2 et p3 sont free ! \n");

    char *p11 = mini_calloc(1, 101);
    if(p11 == NULL) return 0;
    printf("p11 : %p (= p1) \n", p11);
    char *p22 = mini_calloc(1, 99);
    if(p22 == NULL) return 0;
    printf("p22 : %p (= p2) \n", p22);
    char *p33 = mini_calloc(1, 98);
    if(p33 == NULL) return 0;
    printf("p33 : %p (= p3) \n", p33);

    mini_free(p11); mini_free(p22); mini_free(p33); */


    // Exercice 17 : Test du mini_printf
    /*char *str_1 = "Bonjour, ça va ? \n";
    mini_printf("1) Avec '\\n' : \n");
    mini_printf(str_1);
    
    char *str_2 = "Bonjour, ça va ?";
    mini_printf("2) SANS '\\n' : \n");
    mini_printf(str_2);*/
	

    // Exercice 20 : Test du mini_scanf
    /*int BUFFER_SIZE=6; char str[BUFFER_SIZE];

    mini_printf("Saisir : \n");
    int result = mini_scanf(str, BUFFER_SIZE);

    char str_int[10]; int_to_char(result, str_int, 10);
    if (result != -1) {
        mini_printf("Saisie : ");
        mini_printf(str); mini_printf("\n");
        mini_printf("Nb caracètre lu : "); mini_printf(str_int);
    } else {
        mini_printf("Erreur lors de la saisie.\n");
    }*/

    // Exercice 21 : Test de mini_strlen, mini_strcpy, mini_strcmp
    // Test de mini_strlen
    /*mini_printf("---- Test de mini_strlen ----\n");
    char test_str1[] = "Bonjour"; char len_str1[10];
    char test_str2[] = ""; char len_str2[10];
    char *null_str = NULL; char len_null[10];

    int len1 = mini_strlen(test_str1); int_to_char(len1, len_str1, 10);
    int len2 = mini_strlen(test_str2); int_to_char(len2, len_str2, 10);
    int lenn = mini_strlen(null_str); int_to_char(lenn, len_null, 10);
    mini_printf("Longueur de : '"); mini_printf(test_str1); mini_printf("' est : "); mini_printf(len_str1); mini_printf("\n");
    mini_printf("Longueur de : '"); mini_printf(test_str2); mini_printf("' est : "); mini_printf(len_str2); mini_printf("\n");
    mini_printf("Longueur de : '"); mini_printf("NULL"); mini_printf("' est : "); mini_printf(len_null); mini_printf("\n");

    // Test de mini_strcpy
    mini_printf("---- Test de mini_strcpy ---- \n");
    char *dest_str = mini_calloc(sizeof(char), 7); char len_dest[10];
    int lend = mini_strlen(dest_str); int_to_char(lend, len_dest, 10);
    mini_printf("Longueur de : '"); mini_printf("dest_str"); mini_printf("' est : "); mini_printf(len_dest); mini_printf(" (=0 car elle est vide) \n");
    int cb_char_copy = mini_strcpy(test_str1, dest_str); char tab_cb_char_cpoy[10]; int_to_char(cb_char_copy, tab_cb_char_cpoy, 10);
    mini_printf("Copie de '"); mini_printf(test_str1); mini_printf("' dans '"); mini_printf(dest_str); mini_printf("' (si les deux chaines sont identiques alors strcpy marche) \n");
    mini_printf("Nombre de caracètre copiés : "); mini_printf(tab_cb_char_cpoy);
    mini_printf("\n");

    // Test de mini_strcmp
    mini_printf("---- Test de mini_strcmp ----\n");
    int cmp_result1 = mini_strcmp("abc", "abc"); char cmp1[10];
    int cmp_result2 = mini_strcmp("abc", "abd"); char cmp2[10];
    int cmp_result3 = mini_strcmp("z", "a"); char cmp3[10];
    int_to_char(cmp_result1, cmp1, 10); int_to_char(cmp_result2, cmp2, 10); int_to_char(cmp_result3, cmp3, 10);

    mini_printf("Comparaison de 'abc' et 'abc' : "); mini_printf(cmp1); mini_printf(" (=0 car identique)\n");
    mini_printf("Comparaison de 'abc' et 'abd' : "); mini_printf(cmp2); mini_printf(" (-1 car 's1<s2') \n"); 
    mini_printf("Comparaison de 'z' et 'a' : "); mini_printf(cmp3); mini_printf(" (1 car 's1>s2') \n"); */
    

    // Exercice 23 : Test du mini_perror 
    // Simulons une erreur, par exemple, l'ouverture d'un fichier qui n'existe pas
    /*int fileDescriptor = open("fichier_inexistant.txt", O_RDONLY);
    if (fileDescriptor == -1) {
        // Appel de mini_perror avec un message explicatif
        mini_perror("ERROR open() ");
    }
    mini_printf("(le code errno doit être =2 dans ce test là) \n"); */


    // Exercice 30 : Test du mini_fopen et mini_fread
    /*MYFILE* file = mini_fopen("./test_txt/mini_fread_test.txt", 'r');
    if (file == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier.\n");
        return -1;
    }

    // Test de mini_fread
    int buffer_size = 2048;
    char buffer[buffer_size];
    char elm[10];

    int elements_lus = mini_fread(buffer, sizeof(char), buffer_size, file);
    int_to_char(elements_lus, elm, 10);

    if (elements_lus == -1) {
        mini_perror("Erreur lors de la lecture du fichier.\n");
        return 1;
    }
    mini_printf("Nb caracètre lu : "); mini_printf(elm); mini_printf("\n");
    mini_printf("Contenu lu : "); 
    mini_printf(buffer); */
    

    // Exercice 32 : Test du mini_fopen et mini_fread et mini_fwrite
    /*MYFILE* file_read = mini_fopen("./test_txt/mini_fread_test.txt", 'r');
    if (file_read == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier.\n");
        return -1;
    }

    // Test de mini_fread
    int buffer_size = 2048; char buffer_read[buffer_size];
    char elm[10];

    int elements_lus = mini_fread(buffer_read, sizeof(char), buffer_size, file_read);
    int_to_char(elements_lus, elm, 10);

    if (elements_lus == -1) {
        mini_perror("Erreur lors de la lecture du fichier.\n");
        return 1;
    }

    mini_printf("Contenu lu : "); mini_printf(buffer_read); mini_printf("\n");

    mini_printf("\n"); 

    // Ouvrir un fichier en écriture
    MYFILE* file_write = mini_fopen("./test_txt/mini_fwrite_test.txt", 'w');
    if (file_write == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier en écriture.\n");
        return -1;
    }

    // Test de mini_fwrite
    char to_write[] = "Bonjour! Je suis le texte qui test mini_fwrite() !";
    int elements_ecrits = mini_fwrite(to_write, sizeof(char), sizeof(to_write), file_write);
    if (elements_ecrits == -1) {
        mini_perror("Erreur lors de l'écriture dans le fichier.\n");
        return 1;
    }

    mini_printf("Contenu dans buffer_write : "); mini_printf(file_write->buffer_write); mini_printf("\n");
    char ind_w[10]; int_to_char(file_write->ind_write, ind_w, 10);
    mini_printf("Position de l'indice d'écriture : "); mini_printf(ind_w); mini_printf("\n"); */
    

    // Exercice 33 : Test du mini_fwrite mini_fflush 
    /*MYFILE* file_write = mini_fopen("./test_txt/mini_fwrite_test.txt", 'w');
    if (file_write == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier en écriture.\n");
        return -1;
    }

    // Test de mini_fwrite 
    char to_write[] = "Bonjour! Je suis le texte qui test mini_fwrite() !";
    int elements_ecrits = mini_fwrite(to_write, sizeof(char), sizeof(to_write), file_write);
    if (elements_ecrits == -1) {
        mini_printf("Erreur lors de l'écriture dans le fichier.\n");
        return 1;
    }

    mini_printf("Contenu dans buffer_write : "); mini_printf(file_write->buffer_write); mini_printf("\n");
    char ind_w[10]; int_to_char(file_write->ind_write, ind_w, 10);
    mini_printf("Position de l'indice d'écriture : "); mini_printf(ind_w); mini_printf("\n");

    // Test de mini_fflush
    int flushed_chars = mini_fflush(file_write);

    if (flushed_chars == -1) {
        mini_printf("Erreur lors du flush du buffer d'écriture.\n");
        return 1;
    }

    char flush_tab[10]; int_to_char(flushed_chars, flush_tab, 10);
    mini_printf("Nombre de caractères écrits par le flush : "); mini_printf(flush_tab); mini_printf("\n");
    mini_printf("Contenu dans buffer_write : (vide car tout est écrit)"); mini_printf(file_write->buffer_write); mini_printf("\n"); */

    // Exercice 38 : Test de toutes les fonctions
    // mini_fopen, mini_fwrite, mini_fflush, mini_fgetc, mini_fputc et mini_fclose
    /*MYFILE* file_read = mini_fopen("./test_txt/mini_fread_test.txt", 'r');
    if (file_read == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier.\n");
        return -1;
    }
    
    MYFILE* file_write = mini_fopen("./test_txt/mini_fwrite_test.txt", 'w');
    if (file_write == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier en écriture.\n");
        return -1;
    }

    // Test de mini_fwrite 
    char to_write[] = "Bonjour! Je suis le texte qui test mini_fwrite() !";
    int elements_ecrits = mini_fwrite(to_write, sizeof(char), sizeof(to_write), file_write);
    if (elements_ecrits == -1) {
        mini_printf("Erreur lors de l'écriture dans le fichier.\n");
        return 1;
    }
    mini_printf("Contenu dans buffer_write : "); mini_printf(file_write->buffer_write); mini_printf("\n");
    char ind_w[10]; int_to_char(file_write->ind_write, ind_w, 10);
    mini_printf("Position de l'indice d'écriture : "); mini_printf(ind_w); mini_printf("\n");

    // Test de mini_fflush
    int flushed_chars = mini_fflush(file_write);
    if (flushed_chars == -1) {
        mini_printf("Erreur lors du flush du buffer d'écriture.\n");
        return 1;
    }
    char flush_tab[10]; int_to_char(flushed_chars, flush_tab, 10);
    mini_printf("Nombre de caractères écrits par le flush : "); mini_printf(flush_tab); mini_printf("\n");
    mini_printf("Contenu dans buffer_write : (vide car tout est écrit)"); mini_printf(file_write->buffer_write); mini_printf("\n");

    // Test de mini_fgetc et mini_fputc
    mini_printf("\n");
    mini_printf("Lecture d'un caracètre par mini_fgetc :\n");
    char ind_r[10]; int_to_char(file_read->ind_read, ind_r, 10);
    mini_printf("Position de l'indice de lecture : "); mini_printf(ind_r); mini_printf("\n");
    
    int read_fgetc = mini_fgetc(file_read);
    char read_char = (char)read_fgetc;
    mini_printf("Caractère lu avec mini_fgetc dans le test write : "); mini_printf(&read_char); mini_printf("\n");
    int_to_char(file_read->ind_write, ind_r, 10);
    mini_printf("Position de l'indice de lecture : "); mini_printf(ind_r); mini_printf("\n");
    
    read_fgetc = mini_fgetc(file_write);
    read_char = (char)read_fgetc;
    mini_printf("Caractère lu avec mini_fgetc dans le test read : "); mini_printf(&read_char); mini_printf("\n");

    mini_printf("\n");
    mini_printf("Ecriture d'un caracètre par mini_fputc ('X') :\n");
    if(mini_fputc(file_write, 'X') == -1) {
        mini_printf("Erreur lors de l'écriture d'un caractère avec mini_fputc.\n");
        return 1;
    }

    // On regarde si 'X' est ajouté au buffer_write de file_write
    mini_printf("Contenu dans buffer_write ('X' ?) : "); mini_printf(file_write->buffer_write); mini_printf("\n");
    int_to_char(file_write->ind_write, ind_w, 10); 
    mini_printf("Position de l'indice d'écriture : "); mini_printf(ind_w); mini_printf("\n");
    
    // Flush du buffer d'écriture
    flushed_chars = mini_fflush(file_write);
    if (flushed_chars == -1) {
        mini_printf("Erreur lors du flush du buffer d'écriture.\n");
        return 1;
    }

    char flush_tab_2[10];int_to_char(flushed_chars, flush_tab_2, 10);
    mini_printf("Nombre de caractères écrits par le flush : "); mini_printf(flush_tab_2); mini_printf("\n");
    mini_printf("Contenu dans buffer_write : (vide car tout est écrit)"); mini_printf(file_write->buffer_write); mini_printf("\n"); 


    mini_printf("\n"); mini_printf("\n");
    MYFILE* fichier = mini_fopen("./test_txt/mini_fwrite_test.txt", 'r');
    char buffer_test[1000];
    int nb_lus;

    if(fichier != NULL) {
        if((nb_lus = mini_fread(buffer_test, 1, 1000, fichier)) > 0) {
            // Utilise mini_fwrite pour afficher les données lues
            //mini_fwrite(stdout, buffer_test, 1, nb_lus);
            mini_printf("Au final, le fichier 'mini_fwrite_test.txt' contient : ");
            mini_printf(buffer_test);
        }
        // Ferme le fichier
        mini_fclose(fichier);
    }

    // Fermeture des fichiers
    if (mini_fclose(file_read) == -1) {
        mini_printf("Erreur lors de la fermeture du fichier en lecture.\n");
        return 1;
    }

    if (mini_fclose(file_write) == -1) {
        mini_printf("Erreur lors de la fermeture du fichier en écriture.\n");
        return 1;
    }*/

    // Autre test simple du mini_fgetc / mini_fputc :
    /*MYFILE* file_write = mini_fopen("./test_txt/mini_fwrite_test.txt", 'w');
    if (file_write == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier en écriture.\n");
        return -1;
    }
    char to_write[] = "Bonjour! Je suis le texte qui test mini_fwrite() !";
    int elements_ecrits = mini_fwrite(to_write, sizeof(char), sizeof(to_write), file_write);
    if (elements_ecrits == -1) {
        mini_printf("Erreur lors de l'écriture dans le fichier.\n");
        return 1;
    }
    mini_printf("Contenu dans buffer_write : "); mini_printf(file_write->buffer_write); mini_printf("\n");
    char ind_w[10]; int_to_char(file_write->ind_write, ind_w, 10);
    mini_printf("Position de l'indice d'écriture : "); mini_printf(ind_w); mini_printf("\n");

    mini_printf("\n");
    mini_printf("--> Lecture d'un caracètre par mini_fgetc :\n");
    mini_printf("#### INFORMATION SUR LE FICHIER #### \n");
    char ind_r[10]; int_to_char(file_write->ind_read, ind_r, 10);
    mini_printf("Position de l'indice de lecture : "); mini_printf(ind_r); mini_printf("\n");
    int_to_char(file_write->ind_write, ind_w, 10);
    mini_printf("Position de l'indice d'écriture : "); mini_printf(ind_w); mini_printf("\n");

    int i_fgetc = mini_fgetc(file_write);
    char c_fgetc = (char)i_fgetc;
    mini_printf("Caractère lu avec mini_fgetc dans le test write : "); mini_printf_c(c_fgetc); mini_printf("\n");
    char ind_r[10]; int_to_char(file_write->ind_write, ind_r, 10);
    mini_printf("Position de l'indice de lecture : "); mini_printf(ind_r); mini_printf("\n");
    
    mini_printf("#### INFORMATION SUR LE FICHIER #### \n");
    int_to_char(file_write->ind_read, ind_r, 10);
    mini_printf("Position de l'indice de lecture : "); mini_printf(ind_r); mini_printf("\n");
    int_to_char(file_write->ind_write, ind_w, 10);
    mini_printf("Position de l'indice d'écriture : "); mini_printf(ind_w); mini_printf("\n");

    mini_printf("\n");
    mini_printf("--> Ecriture d'un caracètre par mini_fputc ('X') :\n");
    if(mini_fputc(file_write, 'X') == -1) {
        mini_printf("Erreur lors de l'écriture d'un caractère avec mini_fputc.\n");
        return 1;
    }

    // On regarde si 'X' est ajouté au buffer_write de file_write
    mini_printf("Contenu dans buffer_write ('X' ?) : "); mini_printf(file_write->buffer_write); mini_printf("\n");
    int_to_char(file_write->ind_write, ind_w, 10); 
    mini_printf("Position de l'indice d'écriture : "); mini_printf(ind_w); mini_printf("\n");*/

    // Autre test simple du mini_fgetc / mini_fputc : 
    /*MYFILE *fichier = mini_fopen("./test_txt/mini_fgetc.txt", 'r');
    MYFILE *fichier2 = mini_fopen("./test_txt/mini_fputc.txt", 'w');
    // Vérifier si le fichier a été ouvert avec succès
    if (fichier != NULL) {
        char caractere;

        // Lire chaque caractère du fichier et l'afficher
        while ((caractere = mini_fgetc(fichier))) {
            //printf("%c \n", caractere);
            mini_printf_c(caractere); 
            mini_fputc(fichier2, caractere);
        }

        // Fermer le fichier après lecture
        mini_fclose(fichier);
    } else {
        // Afficher un message d'erreur si l'ouverture du fichier a échoué
        mini_printf("Erreur d'ouverture du fichier.\n");
    }
    mini_printf("\n");
    MYFILE *fichier3 = mini_fopen("./test_txt/mini_fread_test.txt", 'r');
    mini_printf_c(mini_fgetc(fichier3));*/

    // Autre test simple du mini_fgetc / mini_fputc : 
    /*MYFILE *fichier = mini_fopen("./test_txt/mini_fputc2.txt", 'w');
    if(fichier == NULL) {
        mini_perror("mini_fopen() ");
    }
    mini_fputc(fichier, 'c');
    mini_fputc(fichier, 'k');
    mini_fputc(fichier, 'x');
    mini_fputc(fichier, 's');
    mini_fputc(fichier, 'x');
    mini_fputc(fichier, 'x');
    mini_fputc(fichier, 'd');*/

    // Test pour savoir si le mini_fclose va effecuter le mini_fflush :
    /*MYFILE* file_write2 = mini_fopen("./test_txt/mini_fwrite_test2.txt", 'w');
    if (file_write2 == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier en écriture.\n");
        return -1;
    }
    char to_write2[] = "Est-ce que je suis flush quand mini_close seulement est appelé ?";
    int elements_ecrits2 = mini_fwrite(to_write2, sizeof(char), sizeof(to_write2), file_write2);
    if (elements_ecrits2 == -1) {
        mini_printf("Erreur lors de l'écriture dans le fichier.\n");
        return 1;
    }
    mini_printf("Contenu dans buffer_write2 : "); mini_printf(file_write2->buffer_write); mini_printf("\n");
    char ind_w2[10]; int_to_char(file_write2->ind_write, ind_w2, 10);
    mini_printf("Position de l'indice d'écriture2 : "); mini_printf(ind_w2); mini_printf("\n");

    // On close, donc normalement le mini_flush se fait automatiquement :
    if (mini_fclose(file_write2) == -1) {
        mini_printf("Erreur lors de la fermeture du fichier en écriture.\n");
        return 1;
    }
    mini_printf("Contenu dans buffer_write2 (vide donc OK): "); mini_printf(file_write2->buffer_write); mini_printf("\n");
    int_to_char(file_write2->ind_write, ind_w2, 10);
    mini_printf("Position de l'indice d'écriture2 (0 donc OK): "); mini_printf(ind_w2); mini_printf("\n"); */
    
    // Exercice 39 : Test du mini_touch
    // Test avec un fichier qui n'existe pas
    /*char* filename1 = "./test_txt/mini_touch_test_new.txt";
    mini_touch(filename1);

    // Test avec un fichier qui existe déjà
    char* filename2 = "./test_txt/mini_touch_test_exist.txt";
    mini_touch(filename2);*/

    // Exercice 40 :
    // Test de mini_cp :
    /*char source[] = "./test_txt/mini_cp_source.txt";
    char destination[] = "./test_txt/mini_cp_dest.txt";
    mini_cp(source, destination);*/

    // Test mini_echo :
    /*char message[] = "Hello, world ! \n";
    mini_echo(message);*/

    // Test de mini_cat :
    /*char* nom_fichier = "./test_txt/mini_cp_dest.txt";
    mini_cat(nom_fichier);*/
    
    // Test de mini_head :
    /*char* nom_fichier = "./test_txt/test.txt";
    mini_head(0, nom_fichier); // affiche rien
    mini_head(1, nom_fichier); // affiche la 1er ligne
    mini_head(2, nom_fichier); // affiche la 2e ligne */

    // Test de mini_tail :
    /*char* nom_fichier = "./test_txt/test.txt";
    mini_tail(0, nom_fichier); // affiche rien
    mini_tail(1, nom_fichier); // affiche la 1er dernière ligne
    mini_tail(2, nom_fichier); // affiche la 2e ligne */

    // Test de mini_clean :
    /*char* nom_fichier_new = "./test_txt/mini_clean_test_new.txt";
    char* nom_fichier_exist = "./test_txt/mini_clean_test_exist.txt"; // un .txt avec des données dedans 
    mini_clean(nom_fichier_new); // va créer un fichier vide "test_mini_clean_new.txt"
    mini_clean(nom_fichier_exist); // va remettre à 0 le fichier "test_mini_clean_exist.txt" */

    // Test de mini_grep :
    /*char* mot = "BEGOUUD";  // Mot à rechercher
    char* nom_fichier = "./test_txt/test.txt";  // Nom du fichier à traiter
    mini_grep(mot, nom_fichier); */

    // Test de mini_wc :
    /*char* nom_fichier = "./test_txt/mini_wc_test.txt"; 
    mini_wc(nom_fichier);*/

    // Test du mini_shell 
    mini_shell();

    printf("...");
    printf("zkcnzc");

    mini_exit();
    return 0;
}


