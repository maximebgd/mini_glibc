# mini_glibc

<p align="center">
  <a href="./README.md"><img src="https://img.shields.io/badge/🇬🇧_English-2ea44f?style=for-the-badge" alt="English"></a>
  &nbsp;
  <a href="./README.fr.md"><img src="https://img.shields.io/badge/🇫🇷_Français-555555?style=for-the-badge" alt="Français"></a>
</p>

Educational re-implementation of a subset of the C standard library on top of raw system calls (`sbrk`, `read`, `write`, `open`, `close`, `fork`, `waitpid`). The project also includes an interactive mini-shell that orchestrates around a dozen commands inspired by classic Unix tools (`touch`, `cp`, `echo`, `cat`, `head`, `tail`, `grep`, `wc`, etc.).

Project completed as part of a university assignment during my 3rd year of engineering school — see [`sujet.pdf`](./sujet.pdf) for the assignment brief and [`rapport.pdf`](./rapport.pdf) for the detailed report (both in French).

> **Final grade: 19.63 / 20**

## Build & run

```bash
cd src
make           # produces ./mon_exe
./mon_exe      # launches the mini_shell
```

To clean build artifacts:

```bash
make clean
```

## Features

The project is organized into four logical layers, each built on top of the previous one.

### 1. Memory management (`mini_memory.c`)
- `mini_calloc(size, n)` — allocation + zero-initialization via `sbrk`
- `mini_free(ptr)` — release (logical marking, block can be reused)
- Internal linked list `malloc_element` tracking allocated blocks

### 2. Strings & standard I/O (`mini_string.c`)
- `mini_printf`, `mini_printf_c` — buffered output (flushed on `\n` or when buffer is full)
- `mini_scanf` — input from standard input
- `mini_strlen`, `mini_strcpy`, `mini_strncpy`, `mini_strcmp`
- `mini_perror` — error message with `errno`

### 3. File I/O (`mini_io.c`)
`MYFILE` struct wrapping a file descriptor with separate read/write buffers.

- `mini_fopen(file, mode)` — modes `'r'`, `'w'`, `'b'` (R/W), `'a'` (append)
- `mini_fread`, `mini_fwrite` — buffered I/O
- `mini_fflush` — forces buffer write
- `mini_fclose` — flush + close + removal from internal list
- `mini_fgetc`, `mini_fputc` — one character at a time

### 4. System commands
Each command lives in its own file (`mini_touch.c`, `mini_cp.c`, etc.) and uses only the layers above.

| Command      | Description                                                |
|--------------|------------------------------------------------------------|
| `mini_echo`  | Prints its arguments                                       |
| `mini_touch` | Creates an empty file if it doesn't already exist          |
| `mini_cat`   | Prints the contents of a file                              |
| `mini_cp`    | Copies a source file to a destination                      |
| `mini_head`  | Prints the first N lines of a file                         |
| `mini_tail`  | Prints the last N lines of a file                          |
| `mini_clean` | Empties / resets a file                                    |
| `mini_grep`  | Searches for a string in a file                            |
| `mini_wc`    | Counts the words in a file                                 |
| `mini_clear` | Clears the screen                                          |
| `mini_help`  | Displays general help, or help for a specific command      |

### 5. Mini-shell (`mini_shell.c`)
Interactive loop that reads a line, splits it into command + arguments, then runs the command in a child process (`fork` / `waitpid`). Type `exit` to quit.

## Using the mini_shell

Inside the shell, type `mini_help` for the list of commands, or `mini_help <command>` for detailed help on a specific command.

Example:

```
mini_shell > mini_echo Hello world
mini_shell > mini_touch ./test_txt/new.txt
mini_shell > mini_cat ./test_txt/test.txt
mini_shell > mini_grep BEGOUD ./test_txt/test.txt
mini_shell > exit
```

Paths are resolved relative to the current working directory — launch `./mon_exe` from `src/` to use the sample test files provided in `src/test_txt/`.

## Repository structure

```
.
├── README.md                 # English (default)
├── README.fr.md              # French
├── sujet.pdf                 # assignment brief (FR)
├── rapport.pdf               # detailed report (FR)
└── src/
    ├── Makefile
    ├── mini_lib.h            # API declarations and documentation
    ├── mini_memory.c         # layer 1: allocation
    ├── mini_string.c         # layer 2: strings & standard I/O
    ├── mini_io.c             # layer 3: files
    ├── mini_*.c              # layer 4: system commands
    ├── mini_shell.c          # layer 5: interactive shell
    ├── fonctions_auxiliaires.c
    ├── main.c
    └── test_txt/             # test files
```

## Environment

- Developed and tested on macOS (Darwin) with `gcc`
- Linux-compatible (the system calls used are standard POSIX)
- The `#pragma GCC diagnostic ignored "-Wdeprecated-declarations"` directive in `mini_lib.h` silences the `sbrk` warning on macOS

## Author

Maxime BEGOUD — 2024
