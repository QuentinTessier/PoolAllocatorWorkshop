NAME		= 	test

SRC			=	./main.c 				\
				./src/MemoryPool.c

OBJ			=	$(SRC:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ) $(NAME)