CC=clang
OBJS=timer.o
H_FILES=timer.h
FLAGS=-O3 -Wall -Wextra -ansi -pedantic
MATH_FLAG=-lm
RM=rm

prime_sieve: prime_sieve.c ${OBJS} ${H_FILES}
	${CC} ${FLAGS} ${MATH_FLAG} -o $@ prime_sieve.c ${OBJS}
timer.o: timer.c
	${CC} ${FLAGS} -o $@ -c timer.c
clean:
	${RM} *.o prime_sieve
