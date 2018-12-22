VPATH = ./ft_ssl_f/src
NAME = ft_ssl
LIB = libft.a
LIB_PATH = ./libft
PRINTF = printf.a
PRINTF_PATH = ./printf
SRC = main.c global.c main_controller.c print.c check.c file.c stdin.c \
string.c context.c hash_md5.c hash_sha256.c padding.c fghi.c bitwise.c \
hash.c output_h.c kill_leaks.c
OBJ = $(subst .c,.o,$(SRC))

.PHONY: all clean fclean re cleano

all: $(NAME)

$(NAME): $(LIB) $(PRINTF) $(OBJ)
	gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) $(PRINTF) $(LIB)

$(OBJ): $(SRC)
	gcc -Wall -Wextra -Werror -c $^

$(LIB) :
	@make -C $(LIB_PATH)
	@make clean -C $(LIB_PATH)
	mv $(LIB_PATH)/$(LIB) ./

$(PRINTF) :
	@make -C $(PRINTF_PATH)
	@make clean -C $(PRINTF_PATH)
	mv $(PRINTF_PATH)/$(PRINTF) ./

cleano:
	/bin/rm -f $(OBJ)

clean: cleano
	/bin/rm -f $(LIB)
	/bin/rm -f $(PRINTF)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
