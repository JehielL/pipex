NAME        = pipex

# Compilador y flags
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g -fsanitize=address
LFT_DIR     = utils/libft
PRINTF_DIR  = utils/ft_printf_42
INC         = -I./src -I$(LFT_DIR)/includes -I$(PRINTF_DIR)/includes
LIB         = -L$(LFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf

# Colores
GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m
CHECK_MARK  = \033[1;32m✔\033[0m

# Archivos fuente y objetos
SRC         = src/pipex.c src/pipex_utils.c src/error.c src/paths.c src/commands.c
OBJ         = $(SRC:.c=.o)

# Regla principal
all:        $(NAME)

# Construir el ejecutable
$(NAME):    $(OBJ)
		@echo " [ .. ] | Compilando libft.."
		@make -C $(LFT_DIR) > /dev/null
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) libft compilado con éxito!$(RESET)"
		@echo " [ .. ] | Compilando ft_printf.."
		@make -C $(PRINTF_DIR) > /dev/null
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) ft_printf compilado con éxito!$(RESET)"
		@$(CC) $(CFLAGS) -o $@ $^ $(LIB)
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) Ejecutable $(NAME) construido con éxito!$(RESET)"

# Regla para compilar archivos fuente en objetos
src/%.o: src/%.c
		@$(CC) $(CFLAGS) $(INC) -c $< -o $@
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) Compilado: $<$(RESET)"

# Limpiar archivos objetos y ejecutable
clean:
		@make -C $(LFT_DIR) clean > /dev/null
		@make -C $(PRINTF_DIR) clean > /dev/null
		@rm -f $(OBJ)
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) Archivos objeto eliminados.$(RESET)"

fclean: clean
		@rm -f $(NAME)
		@echo " $(RED)[ OK ] $(CHECK_MARK) Ejecutable $(NAME) eliminado.$(RESET)"

# Recompilar todo
re: fclean all

# Ejecutar el programa con Valgrind
valgrind: all
		@echo " [ .. ] | Ejecutando el programa con Valgrind.."
		@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME)

.PHONY: all clean fclean re valgrind
