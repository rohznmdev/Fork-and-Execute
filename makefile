NAME = lab06
FLAGS = -Wall -pedantic-errors

cl: ${NAME}.c
	gcc -o ${NAME} ${FLAGS} -lm ${NAME}.c
run: cl
	./${NAME}
clean:
	rm -f ${NAME}
