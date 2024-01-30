#include "mini_lib.h"


#define MAX_COMMAND_LENGTH 200
#define ARG_MAX 20

#define COLOR_RESET "\033[0m"
#define COLOR_PROMPT "\033[1;32m" // Couleur verte brillante pour le prompt
#define COLOR_PROMPT_2 "\033[1;32m>>> " // Couleur verte brillante pour le prompt
#define COLOR_RED "\033[1;31m" // Couleur rouge brillante
#define COLOR_BLUE "\033[1;34m" // Couleur bleue brillante
#define COLOR_ORANGE "\033[38;5;208m"


int mini_strncpy(char* s, char* d, int n) {
    if (s == NULL || d == NULL || n < 0) {
        return -1; // Cas d'erreur
    }

    int cmpt = 0;
    while (*s != '\0' && cmpt < n) {
        *d = *s;
        cmpt++;
        s++;
        d++;
    }
    *d = '\0';

    return cmpt; // nb caractères copiés
}


void split_command(char *full_command, char *command, char *args[], int *argc) {
    *argc = 0;

    // Supprimer le caractère de nouvelle ligne '\n' à la fin de la chaîne
    size_t len = mini_strlen(full_command);
    if(len > 0 && full_command[len - 1] == '\n') {
        full_command[len - 1] = '\0';
    }

    char *start = full_command;
    // Ignorer les espaces au début
    while(*start == ' ') {
        start++;
    }

    // Trouver la fin de la commande
    char *end = start;
    while(*end != ' ' && *end != '\0') {
        end++;
    }

    // Copier la commande dans 'command'
    int length = end - start;
    mini_strncpy(start, command, length);
    command[length] = '\0';

    start = end;
    while(*start != '\0' && *argc < ARG_MAX - 1) {
        // Ignorer les espaces au début de chaque argument
        while(*start == ' ') {
            start++;
        }

        // Trouver la fin de l'argument
        end = start;
        while(*end != ' ' && *end != '\0') {
            end++;
        }

        // Copier l'argument dans 'args'
        length = end - start;
        args[*argc] = mini_calloc(1, length+1);//malloc(length + 1);
        mini_strncpy(start, args[*argc], length);
        args[*argc][length] = '\0';
        (*argc)++;

        // Déplacer le pointeur de début au prochain argument
        start = end;
    }

    // Dernier élément doit être NULL pour execvp
    args[*argc] = NULL;
}


void execute_command(char *command, char *args[], int argc) {
    int n;
    if(mini_strcmp(command, "mini_echo") == 0) {
        //mini_echo("Dans le echo"); mini_printf("\n");
        mini_printf(COLOR_PROMPT_2); mini_printf(COLOR_RESET);
        for(int i=0; i<argc; i++) {
            mini_echo(args[i]); mini_printf(" ");
        }
        mini_printf("\n");
    }
    else if(mini_strcmp(command, "mini_touch") == 0) {
        //mini_echo("Dans le touch"); mini_printf("\n");
        mini_printf(COLOR_PROMPT_2); mini_printf(COLOR_RESET); mini_touch(args[0]);
    }
    else if(mini_strcmp(command, "mini_cat") == 0) {
        //mini_echo("Dans le cat"); mini_printf("\n");
        mini_printf(COLOR_PROMPT_2); mini_printf(COLOR_RESET); mini_cat(args[0]);
    }
    else if(mini_strcmp(command, "mini_tail") == 0) {
        //mini_echo("Dans le tail"); mini_printf("\n");
        n = char_to_int(args[0]);
        mini_printf(COLOR_PROMPT_2); mini_printf(COLOR_RESET); mini_tail(n, args[1]); 
    }
    else if(mini_strcmp(command, "mini_head") == 0) {
        //mini_echo("Dans le head"); mini_printf("\n");
        n = char_to_int(args[0]);
        mini_printf(COLOR_PROMPT_2); mini_printf(COLOR_RESET); mini_head(n, args[1]); 
    }
    else if(mini_strcmp(command, "mini_clean") == 0) {
        //mini_echo("Dans le clean"); mini_printf("\n");
        mini_printf(COLOR_PROMPT_2); mini_printf(COLOR_RESET); mini_clean(args[0]);
    }
    else if(mini_strcmp(command, "mini_grep") == 0) {
        //mini_echo("Dans le grep"); mini_printf("\n");
        mini_printf(COLOR_PROMPT_2); mini_printf(COLOR_RESET); mini_grep(args[0], args[1]);
    }
    else if(mini_strcmp(command, "mini_wc") == 0) {
        //mini_echo("Dans le wc"); mini_printf("\n");
        mini_printf(COLOR_PROMPT_2); mini_printf(COLOR_RESET); mini_wc(args[0]);
    }
    else if(mini_strcmp(command, "mini_clear") == 0) {
        mini_printf(COLOR_PROMPT_2); mini_printf(COLOR_RESET); mini_clear(args[0]);
    }
    else if(mini_strcmp(command, "mini_help") == 0) {
        mini_printf(COLOR_PROMPT_2); mini_printf(COLOR_RESET); mini_help(args[0]);
    }
    else {
        mini_printf(COLOR_RED); mini_printf("Commande inconnue : '"); mini_printf(command); mini_printf("'"); mini_printf(COLOR_RESET); mini_printf("\n");
    }
    
}


void mini_help(char* nfonc) {
    if(mini_strcmp(nfonc, "") == 0 || mini_strcmp(nfonc, " ") == 0) {
        mini_printf(COLOR_BLUE);
        mini_printf("############################################# FORMULAIRE D'AIDE POUR LES APPELS DE FONCIONS DU MINI_SHELL #############################################\n");
        mini_printf("La fonction : 'mini_echo' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_echo chaine1 chaine2 ... chaineN \n"); 

        mini_printf("La fonction : 'mini_touch' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_touch name_file \n");

        mini_printf("La fonction : 'mini_cat' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_cat name_file \n");

        mini_printf("La fonction : 'mini_tail' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_tail N_dernière_ligne name_file \n");

        mini_printf("La fonction : 'mini_head' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_head N_première_ligne name_file \n");

        mini_printf("La fonction : 'mini_clean' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_clean name_file \n");

        mini_printf("La fonction : 'mini_grep' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_grep mot_cherché name_file \n");

        mini_printf("La fonction : 'mini_wc' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_wc name_file \n");

        mini_printf("La fonction : 'mini_clear' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_clear \n");

        mini_printf("\nPour QUITTER le mini_shell : exit \n");

        mini_printf("\n--> Si vous avez besoin d'aider pour une fonction <-- \n");
        mini_printf("----> mini_help name_fonction "); mini_printf("\n");

        mini_printf("#######################################################################################################################################################\n");
        mini_printf(COLOR_RESET); mini_printf("\n");
    }

    else if(mini_strcmp(nfonc, "mini_echo") == 0) {
        mini_printf(COLOR_BLUE);
        mini_printf("############################################# AIDE POUR LA FONCTION 'mini_echo' #############################################\n");
        mini_printf("La fonction : 'mini_echo' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_echo chaine1 chaine2 ... chaineN "); mini_printf(COLOR_RESET); mini_printf("\n");
    }
    else if(mini_strcmp(nfonc, "mini_touch") == 0) {
        mini_printf(COLOR_BLUE);
        mini_printf("############################################# AIDE POUR LA FONCTION 'mini_touch' #############################################\n");
        mini_printf("La fonction : 'mini_touch' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_touch name_file "); mini_printf(COLOR_RESET); mini_printf("\n");
    }
    else if(mini_strcmp(nfonc, "mini_cat") == 0) {
        mini_printf(COLOR_BLUE);
        mini_printf("############################################# AIDE POUR LA FONCTION 'mini_cat' #############################################\n");
        mini_printf("La fonction : 'mini_cat' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_cat name_file "); mini_printf(COLOR_RESET); mini_printf("\n");
    }
    else if(mini_strcmp(nfonc, "mini_tail") == 0) {
        mini_printf(COLOR_BLUE);
        mini_printf("############################################# AIDE POUR LA FONCTION 'mini_tail' #############################################\n");
        mini_printf("La fonction : 'mini_tail' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_tail N_dernière_ligne name_file "); mini_printf(COLOR_RESET); mini_printf("\n");
    }
    else if(mini_strcmp(nfonc, "mini_head") == 0) {
        mini_printf(COLOR_BLUE);
        mini_printf("############################################# AIDE POUR LA FONCTION 'mini_head' #############################################\n");
        mini_printf("La fonction : 'mini_head' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_head N_première_ligne name_file "); mini_printf(COLOR_RESET); mini_printf("\n");
    }
    else if(mini_strcmp(nfonc, "mini_clean") == 0) {
        mini_printf(COLOR_BLUE);
        mini_printf("############################################# AIDE POUR LA FONCTION 'mini_clean' #############################################\n");
        mini_printf("La fonction : 'mini_clean' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_clean name_file "); mini_printf(COLOR_RESET); mini_printf("\n");
    }
    else if(mini_strcmp(nfonc, "mini_grep") == 0) {
        mini_printf(COLOR_BLUE);
        mini_printf("############################################# AIDE POUR LA FONCTION 'mini_grep' #############################################\n");
        mini_printf("La fonction : 'mini_grep' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_grep mot_cherché name_file"); mini_printf(COLOR_RESET); mini_printf("\n");
    }
    else if(mini_strcmp(nfonc, "mini_wc") == 0) {
        mini_printf(COLOR_BLUE);
        mini_printf("############################################# AIDE POUR LA FONCTION 'mini_wc' #############################################\n");
        mini_printf("La fonction : 'mini_wc' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_wc name_file "); mini_printf(COLOR_RESET); mini_printf("\n");
    }
    else if(mini_strcmp(nfonc, "mini_clear") == 0) {
        mini_printf(COLOR_BLUE);
        mini_printf("############################################# AIDE POUR LA FONCTION 'mini_clear' #############################################\n");
        mini_printf("La fonction : 'mini_clear' s'appelle de la manière suivante : \n");
        mini_printf("----> mini_clear "); mini_printf(COLOR_RESET); mini_printf("\n");
    }
}


void mini_shell() {
    // Affiche l'aide du shell 
    mini_help("");
    mini_printf("\n"); mini_printf("\n");
    while (1) {
        //mini_printf("\n"); 
        char command[MAX_COMMAND_LENGTH];
        char full_command[MAX_COMMAND_LENGTH];
        char *args[ARG_MAX];
        int nb_arg;

        // Affiche le prompt
        mini_printf("\n"); mini_printf("\n");
        const char *prompt = "mini_shell > ";
        if(write(STDOUT_FILENO, COLOR_PROMPT, 7) == -1) mini_perror("write()");
        if(write(STDOUT_FILENO, prompt, mini_strlen((char *)prompt)) == -1) mini_perror("write()");
        if(write(STDOUT_FILENO, COLOR_RESET, 4) == -1) mini_perror("write()");// mini_printf("mini_shell >\n");

        // Lit la commande depuis l'entrée standard
        if (mini_scanf(full_command, sizeof(full_command)) == -1) {
            mini_perror("mini_scanf() ");
            return;
        }

        split_command(full_command, command, args, &nb_arg);
        // Vérifie si la commande est "exit"
        if (mini_strcmp(command, "exit") == 0) {
            mini_printf(COLOR_RED);
            mini_printf("########################################################################################################\n");
            mini_printf("############################################# -- AU REVOIR -- ##########################################\n");
            mini_printf("########################################################################################################\n");
            mini_printf(COLOR_RESET); mini_printf("\n");
            return;
        }

        // Supprime le caractère de nouvelle ligne
        size_t full_command_length = mini_strlen(command);
        if (full_command_length > 0 && command[full_command_length - 1] == '\n') {
            command[full_command_length - 1] = '\0';
        }

        // Crée un processus fils
        pid_t child_pid = fork();

        if (child_pid == -1) {
            // Erreur lors de la création du processus fils
            perror("Erreur lors de la création du processus fils");
            return;
        } 
        else if (child_pid == 0) {
            // Code exécuté par le processus fils
            execute_command(command, args, nb_arg);

            exit(EXIT_FAILURE);
        } 
        else {
            // Code exécuté par le processus père

            // Attend que le processus fils se termine
            int status;
            if (waitpid(child_pid, &status, 0) == -1) {
                perror("Erreur lors de l'attente du processus fils");
                return;
            }

            // Vérifie si le processus fils s'est terminé normalement
            if (WIFEXITED(status)) {
                char tab_wifeexited[10]; int_to_char(WEXITSTATUS(status), tab_wifeexited, 10);
                //mini_printf("Le processus fils s'est terminé avec le code de sortie : "); mini_printf(tab_wifeexited); mini_printf("\n");
                mini_printf(COLOR_ORANGE);
                mini_printf("\n"); mini_printf("############################################## Fin du processus fils  --> "); mini_printf("Processus père en attente de commande ..... ##############################################");
                mini_printf(COLOR_RESET); mini_printf("\n");
            } 
            else if (WIFSIGNALED(status)) {
                char tab_wifesignaled[10]; int_to_char(WTERMSIG(status), tab_wifesignaled, 10);
                //mini_printf("Le processus fils s'est terminé à cause du signal : "); mini_printf(tab_wifesignaled); mini_printf("\n");
                mini_printf(COLOR_ORANGE);
                mini_printf("\n"); mini_printf("############################################## Fin du processus fils     "); mini_printf("Processus père en attente de commande ..... ##############################################");
                mini_printf(COLOR_RESET); mini_printf("\n");
            }
        }
    }
}


