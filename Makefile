NAME = minishell
CC = @gcc
RM = @rm -f
FLAGS = -Werror -Wall -Wextra #-fsanitize=address

YELLOW = \033[33;49;1m
END = \033[0;0m

SRC = $(shell find src -name '*.c')
#INCLUDES = -I includes

READLINE_INC_PATH = -I/usr/local/opt/readline/include -I./includes/
READLINE_LIB_PATH = -L/usr/local/opt/readline/lib -lreadline

OBJ = ${SRC:.c=.o}
B_OBJ = ${B_SRC:.c=.o}

all: $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) $(OBJ) $(READLINE_LIB_PATH) -o $(NAME)
			@echo "$(YELLOW)${NAME} ✔️"
			@echo "$(YELLOW)Mandatory files compiled successfully ✔️$(END)"

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) $(READLINE_INC_PATH) -c $< -o $@

n:
	norminette src inc

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: clean all

.PHONY: all clean fclean re
