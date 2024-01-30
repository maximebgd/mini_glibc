# Makefile
CC = gcc
CFLAGS = -g -Wall 
LDFLAGS =
OBJ = mini_memory.o mini_string.o mini_io.o fonctions_auxiliaires.o mini_touch.o mini_cp.o mini_echo.o mini_cat.o mini_head.o mini_tail.o mini_clean.o mini_grep.o mini_wc.o mini_clear.o mini_shell.o main.o 

mon_exe: $(OBJ)
		$(CC) $(OBJ) $(LDFLAGS) -o mon_exe

mini_memory.o: mini_memory.c mini_lib.h
mini_string.o: mini_string.c mini_lib.h
mini_io.o: mini_io.c mini_lib.h
fonctions_auxiliaires.o: fonctions_auxiliaires.c mini_lib.h

## Pour les commandes du mini_shell :
mini_touch.o : mini_touch.c mini_lib.h
mini_cp.o : mini_cp.c mini_lib.h
mini_echo.o : mini_echo.c mini_lib.h
mini_cat.o : mini_cat.c mini_lib.h
mini_head.o : mini_head.c mini_lib.h
mini_tail.o : mini_tail.c mini_lib.h
mini_clean.o : mini_clean.c mini_lib.h
mini_grep.o : mini_grep.c mini_lib.h
mini_wc.o : mini_wc.c mini_lib.h
mini_clear.o : mini_clear.c mini_lib.h


mini_shell.o : mini_shell.c mini_lib.h
main.o: main.c mini_lib.h


clean:
		rm -f *.o mon_exe

clear:
		rm -f *.o mon_exe