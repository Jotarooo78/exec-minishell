NAME = pipex

CC = cc

SRC = src/errors.c src/get_path.c src/main.c src/pipex.c src/manage_files.c src/manage_here_doc.c
INCLUDES = includes/pipex.h libft/libft.h

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wall -g3 -I $(LIBFT_DIR)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: clean fclean all re