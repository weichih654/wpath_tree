CC=gcc
TARGET=wpath
OBJS=main.o path.o node.o
CFLAGS=-I./ -g
LIBS=
%.o:%.c
	${CC} -c $< ${CFLAGS}

all: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} ${CFLAGS}

clean:
	rm ${OBJS}
	rm ${TARGET}
