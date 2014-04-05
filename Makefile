CC = gcc
CFLAGS = -Wall -O2
CFLAGSLIB = -fpic
LDFLAGS = libcsuper.so
SRC_SYS = 	Sources/libcsuper/main_argument.c \
		Sources/libcsuper/game_config.c \
		Sources/libcsuper/file_system_path.c \
		Sources/libcsuper/csu_files.c \
		Sources/libcsuper/share.c \
		Sources/libcsuper/csu_struct.c
OBJ_SYS= $(SRC_SYS:.c=.o)
SRC_TER = 	Sources/csuper/display.c \
		Sources/csuper/interface.c \
		Sources/csuper/main.c \
		Sources/csuper/menu.c \
		Sources/csuper/keyboarding.c
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
