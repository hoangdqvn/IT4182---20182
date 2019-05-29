CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: kiemtra

kiemtra: main.o parser.o scanner.o reader.o charcode.o token.o error.o codegen.o debug.o instructions.o semantics.o symtab.o
	${CC} main.o parser.o scanner.o reader.o charcode.o token.o error.o codegen.o debug.o instructions.o semantics.o symtab.o -o kiemtra

main.o: main.c
	${CC} ${CFLAGS} main.c

scanner.o: scanner.c
	${CC} ${CFLAGS} scanner.c

codegen.o: codegen.c
	${CC} ${CFLAGS} codegen.c

debug.o: debug.c
	${CC} ${CFLAGS} debug.c

instructions.o: instructions.c
	${CC} ${CFLAGS} instructions.c

semantics.o: semantics.c
	${CC} ${CFLAGS} semantics.c

symtab.o: symtab.c
	${CC} ${CFLAGS} symtab.c

parser.o: parser.c
	${CC} ${CFLAGS} parser.c

reader.o: reader.c
	${CC} ${CFLAGS} reader.c

charcode.o: charcode.c
	${CC} ${CFLAGS} charcode.c

token.o: token.c
	${CC} ${CFLAGS} token.c

error.o: error.c
	${CC} ${CFLAGS} error.c

clean:
	rm -f *.o *~

