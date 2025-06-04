#MAKEFILE FILES
CC = gcc
CFLAGS = -Wall -g
PACK = ar
PFLAGS = -rcs
DIR_EXE = ejecutable
DIR_LIB = libreria
DIR_OBJ = objetos
DIR_ERR = errores
LIB_PROPIAS = ./librerias_propias
OBJS = $(SCRS:*.c=$*.o)

.PHONY: all

all: limpia_pantalla crear_dir_err crear_dir_obj crear_dir_exe crea_objetos crea_ejecutable

library: limpia_pantalla crear_dir_err crear_dir_obj crear_dir_lib crea_objetos crear_empaquetado copia_cabecera

clean: limpia_temporales limpia_objetos limpia_errores

crea_objetos: $(SCRS)
	export LIB_PROPIAS	
	$(CC) $(CFLAGS) -I$(LIB_PROPIAS) -c $(SCRS)
	mv *.o ./$(DIR_OBJ)/

crea_ejecutable: $(OBJS)
	$(CC) -L$(LIB_PROPIAS) -o $(NAME) $(OBJS) $(INCLUDES) -lm
	mv $(NAME) ./$(DIR_EXE)

crear_empaquetado:
	$(PACK) $(PFLAGS) lib$(NAME).a ./$(DIR_OBJ)/*.o
	mv lib$(NAME).a ./$(DIR_LIB)

copia_cabecera:
	cp *.h $(DIR_LIB)

crear_dir_obj:
	mkdir -p $(DIR_OBJ)
	chmod +744 $(DIR_OBJ)

crear_dir_exe:
	mkdir -p $(DIR_EXE)
	chmod +744 $(DIR_EXE)

crear_dir_lib:
	mkdir -p $(DIR_LIB)
	chmod +744 $(DIR_LIB)

crear_dir_err:
	mkdir -p $(DIR_ERR)
	chmod +744 $(DIR_ERR)

limpia_pantalla:
	clear
	
limpia_temporales:
	rm -f *.*~
	rm -f Makefile~
	rm -f .*.swp
	rm -f .*.*.un~
	rm -f .Makefile.un~

limpia_objetos: 
	rm -R $(DIR_OBJ)

limpia_errores:
	rm -R $(DIR_ERR)

run:
	clear 
	./$(DIR_EXE)/$(NAME)

debug:
	clear
	gdb $(DIR_EXE)/$(NAME);

check:
	clear
	valgrind --log-file=./$(DIR_ERR)/informe --tool=memcheck --leak-check=full ./$(DIR_EXE)/$(NAME)
	cat ./$(DIR_ERR)/informe

#MAKEFILE VARIABLE

NAME = maze
SCRS = maze.c
INCLUDES = #-lX11 (en caso de usar x_video)

