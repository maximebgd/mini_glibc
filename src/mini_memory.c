#include "mini_lib.h"

// Déclaration des variables global :
malloc_element* malloc_list = NULL;

// Fonction au plus :
malloc_element* reserver_block(malloc_element* myelm, size_t size) {
    malloc_element* r_block;

    // Obtient la position actuelle du pointeur de fin du segment de données.
    r_block = sbrk(0); 
    if(r_block == (void*)-1) return NULL; // Échec de l'allocation

    // Alloue de la mémoire en ajustant le pointeur de fin du segment de données.
    void *request = sbrk(size + sizeof(malloc_element)); 
    
    ///assert((r_block == (malloc_element*)request)); 
    if(r_block != (malloc_element*)request) {
        return NULL; // En cas d'erreur
    }

    // Met à jour le lien vers le prochain bloc dans la liste (si elle n'est pas vide).
    if(myelm) {
        myelm->next_malloc = r_block;
    }

    // Initialise la mémoire allouée avec des zéros.
    for(size_t i = 0; i<size; i++) {
        ((char *)r_block)[i] = '\0';
    }

    // Configuration de la structure malloc_element pour représenter le bloc alloué.
    r_block->zone_alloue = r_block+1; // Pointe vers la zone de mémoire allouée.
    r_block->size = size;
    r_block->next_malloc = NULL; // Pas de prochain element pour le moment
    r_block->statut = 1; // Marque le bloc comme utilisé.

    return r_block;
}

// Fonction au plus :
malloc_element* recherche_block(malloc_element** myelm, size_t size) {
    malloc_element* mycontent = malloc_list; // On "sauvegarde" les élements acutels

    // Exercice 11 :
    // Parcours de la liste jusqu'à trouver un bloc de mémoire disponible et de la taille suffisante
    while(mycontent && !(mycontent->statut == 0 && mycontent->size >= size)) {
        *myelm = mycontent; // Mise à jour de l'adresse du dernier élément examiné dans la liste
        mycontent = mycontent->next_malloc; // Passage à l'élément suivant dans la liste
    }

    return mycontent; // Retourne le bloc trouvé (ou NULL si aucun bloc disponible)
}


void* mini_calloc(int size_element, int number_element) {
    // Calcul de la taille total que l'on veut
    size_t total_size = size_element*number_element;
    malloc_element* memory_block;

    // Gestion de l'erreur : taille totale négative ou nulle
    if(total_size <= 0) return NULL;

    if(!malloc_list) { // Cas n°1 : Premier element de notre liste
        memory_block = reserver_block(NULL, total_size);
        if(!memory_block) return NULL;
        malloc_list = memory_block;
    }
    else { // Cas 2 : On avait déjà des élements dans notre liste
        malloc_element* mycontent = malloc_list; // On "sauvegarde" les élements acutels
        memory_block = recherche_block(&mycontent, total_size);
        if(!memory_block) {
            memory_block = reserver_block(mycontent, total_size);
            if(!memory_block) return NULL;
        }
        else {
            memory_block->statut = 1; // Marque le bloc comme utilisé
        }
    }

    return (memory_block+1); // Retourne le pointeur vers la zone mémoire allouée (après la structure malloc_element)
}


void mini_free(void *ptr) {
    if(ptr == NULL) return; // On ne fait rien dans ce cas

    malloc_element* mycontent = malloc_list; // On "sauvegarde" les élements acutels
    
    // Parcours de la liste jusqu'à trouver le bloc correspondant au pointeur à libérer
    while(mycontent != NULL) {
        if(mycontent->zone_alloue == ptr) {
            mycontent->statut = 0; // Marque le bloc comme non utilisé
            break; // On a trouvé le bloc à libérer, sortie de la boucle
        }
        mycontent = mycontent->next_malloc;
    }

    // Réinitialise le contenu du bloc libéré à zéro (pas demandé)
    /*if(mycontent != NULL && mycontent->statut == 0) { 
        for(int i=0; i < mycontent->size; i++) {
            ((char *)mycontent + 1)[i] = '\0';
        }
    }*/
}


void mini_exit(){
    // Attention, il faut commenter/décommenter cette fonction en fonction de la version du mini_printf !!
    vidage_buffer(); // Afin d'afficher ce qu'il reste dans le buffer et le nettoyer
    
    flush_all_files();

	_exit(0); // On met fin au programme
}