CC = gcc
CFLAGS = -Wall -O2
CFLAGSLIB = -fpic
LDFLAGS = libcsuper.so
SRC_SYS = 	Sources/System/argument_main.c \
		Sources/System/config.c \
		Sources/System/emplacement_fichier.c \
		Sources/System/fichier.c \
		Sources/System/fonction.c \
		Sources/System/structure.c
OBJ_SYS= $(SRC_SYS:.c=.o)
SRC_TER = 	Sources/Console/affichage.c \
		Sources/Console/interface.c \
		Sources/Console/main.c \
		Sources/Console/menu.c \
		Sources/Console/saisie_clavier.c
OBJ_TER= $(SRC_TER:.c=.o)

all: libcsuper.so csuper

libcsuper.so: $(OBJ_SYS)
	$(CC) -shared $^ -o $@
	rm $(OBJ_SYS)

csuper: $(OBJ_TER)
	$(CC) $^ $(LDFLAGS) -o $@
	rm $(OBJ_TER)

%.o: %.c %.h
	$(CC) $(CFLAGS) $(CFLAGSLIB) -c $< -o $@

install: install_libcsuper install_csuper

install_libcsuper: libcsuper.so
	cp -f libcsuper.so /usr/local/lib
	ldconfig

install_csuper: csuper
	cp -f csuper /usr/local/bin

uninstall: uninstall_libcsuper uninstall_csuper

uninstall_libcsuper:
	rm -f /usr/local/lib/libcsuper.so
	ldconfig

uninstall_csuper:
	rm -f /usr/local/bin/csuper
