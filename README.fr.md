# mini_glibc

<p align="center">
  <a href="./README.md"><img src="https://img.shields.io/badge/🇬🇧_English-555555?style=for-the-badge" alt="English"></a>
  &nbsp;
  <a href="./README.fr.md"><img src="https://img.shields.io/badge/🇫🇷_Français-2ea44f?style=for-the-badge" alt="Français"></a>
</p>

Ré-implémentation pédagogique d'un sous-ensemble de la bibliothèque standard C, par-dessus les appels système bruts (`sbrk`, `read`, `write`, `open`, `close`, `fork`, `waitpid`). Le projet inclut également un mini-shell interactif qui orchestre une dizaine de commandes inspirées des outils Unix (`touch`, `cp`, `echo`, `cat`, `head`, `tail`, `grep`, `wc`, etc.).

Projet réalisé dans le cadre d'un TP lors de ma 3è année en école d'ingénieur — voir [`sujet.pdf`](./sujet.pdf) pour l'énoncé et [`rapport.pdf`](./rapport.pdf) pour le rapport détaillé.

> **Note finale : 19,63 / 20**

## Compilation et exécution

```bash
cd src
make           # produit ./mon_exe
./mon_exe      # lance le mini_shell
```

Pour nettoyer les artefacts de build :

```bash
make clean
```

## Fonctionnalités

Le projet est organisé en quatre couches logiques, chacune construite sur la précédente.

### 1. Gestion mémoire (`mini_memory.c`)
- `mini_calloc(size, n)` — allocation + initialisation à zéro via `sbrk`
- `mini_free(ptr)` — libération (marquage logique, réutilisation possible)
- Liste chaînée interne `malloc_element` pour suivre les blocs alloués

### 2. Chaînes & entrée/sortie standard (`mini_string.c`)
- `mini_printf`, `mini_printf_c` — affichage bufferisé (vidage sur `\n` ou buffer plein)
- `mini_scanf` — saisie depuis l'entrée standard
- `mini_strlen`, `mini_strcpy`, `mini_strncpy`, `mini_strcmp`
- `mini_perror` — message d'erreur avec `errno`

### 3. Fichiers (`mini_io.c`)
Structure `MYFILE` enveloppant un descripteur de fichier avec deux buffers (lecture / écriture).

- `mini_fopen(file, mode)` — modes `'r'`, `'w'`, `'b'` (R/W), `'a'` (append)
- `mini_fread`, `mini_fwrite` — I/O bufferisées
- `mini_fflush` — force l'écriture du buffer
- `mini_fclose` — flush + close + retrait de la liste interne
- `mini_fgetc`, `mini_fputc` — un caractère à la fois

### 4. Commandes système
Chaque commande est implémentée dans son propre fichier (`mini_touch.c`, `mini_cp.c`, etc.) en utilisant uniquement les couches ci-dessus.

| Commande     | Description                                                |
|--------------|------------------------------------------------------------|
| `mini_echo`  | Affiche les arguments                                      |
| `mini_touch` | Crée un fichier vide s'il n'existe pas                     |
| `mini_cat`   | Affiche le contenu d'un fichier                            |
| `mini_cp`    | Copie un fichier source vers une destination               |
| `mini_head`  | Affiche les N premières lignes d'un fichier                |
| `mini_tail`  | Affiche les N dernières lignes d'un fichier                |
| `mini_clean` | Vide / réinitialise un fichier                             |
| `mini_grep`  | Recherche une chaîne dans un fichier                       |
| `mini_wc`    | Compte les mots d'un fichier                               |
| `mini_clear` | Efface l'écran                                             |
| `mini_help`  | Affiche l'aide générale ou l'aide d'une commande           |

### 5. Mini-shell (`mini_shell.c`)
Boucle interactive qui lit une ligne, la découpe en commande + arguments, puis exécute la commande dans un processus fils (`fork` / `waitpid`). Tape `exit` pour quitter.

## Utilisation du mini_shell

À l'intérieur du shell, taper `mini_help` pour la liste des commandes, ou `mini_help <commande>` pour l'aide détaillée d'une commande précise.

Exemple :

```
mini_shell > mini_echo Bonjour le monde
mini_shell > mini_touch ./test_txt/nouveau.txt
mini_shell > mini_cat ./test_txt/test.txt
mini_shell > mini_grep BEGOUD ./test_txt/test.txt
mini_shell > exit
```

Les chemins sont résolus relativement au dossier d'exécution — lancer `./mon_exe` depuis `src/` pour utiliser les fichiers de test fournis dans `src/test_txt/`.

## Structure du dépôt

```
.
├── README.md                 # anglais (défaut)
├── README.fr.md              # français
├── sujet.pdf                 # énoncé du TP
├── rapport.pdf               # rapport détaillé
└── src/
    ├── Makefile
    ├── mini_lib.h            # déclarations et documentation de l'API
    ├── mini_memory.c         # couche 1 : allocation
    ├── mini_string.c         # couche 2 : chaînes & E/S standard
    ├── mini_io.c             # couche 3 : fichiers
    ├── mini_*.c              # couche 4 : commandes système
    ├── mini_shell.c          # couche 5 : shell interactif
    ├── fonctions_auxiliaires.c
    ├── main.c
    └── test_txt/             # fichiers de test
```

## Environnement

- Développé et testé sur macOS (Darwin) avec `gcc`
- Compatible Linux (les appels système utilisés sont POSIX standards)
- La directive `#pragma GCC diagnostic ignored "-Wdeprecated-declarations"` dans `mini_lib.h` masque l'avertissement `sbrk` sur macOS

## Auteur

Maxime BEGOUD — 2024
