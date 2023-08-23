NAME = minishell
CC = @gcc
RM = @rm -f
FLAGS = -lreadline
	# -Wall -Wextra -Werror

YELLOW = \033[33;49;1m
END = \033[0;0m

SRC = $(shell find src -name '*.c')
INCLUDES = -I includes

OBJ = ${SRC:.c=.o}
B_OBJ = ${B_SRC:.c=.o}

all: $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) $(OBJ) -o $(NAME)
			@echo "$(YELLOW)${NAME} ✔️"
			@echo "$(YELLOW)Mandatory files compiled successfully ✔️$(END)"

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

n:
	norminette src inc

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: clean all

.PHONY: all clean fclean re
