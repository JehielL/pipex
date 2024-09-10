# Nombre del ejecutable
NAME        = pipex

# Compilador y flags
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g -fsanitize=address
LFT_DIR     = utils/libft
FT_PRINTF   = utils/ft_printf_42
INC         = -I./src -I$(LFT_DIR)/includes -I$(FT_PRINTF)
LIB         = -L$(LFT_DIR) -lft

# Colores
GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m
CHECK_MARK  = \033[1;32m✔\033[0m

# Archivos fuente y objetos (incluye ft_printf)
SRC         = src/pipex.c src/pipex_utils.c src/error.c src/paths.c src/commands.c \
              $(FT_PRINTF)/ft_printf.c $(FT_PRINTF)/ft_aux_pf.c $(FT_PRINTF)/ft_putchar_pf.c \
              $(FT_PRINTF)/ft_puthex_pf.c $(FT_PRINTF)/ft_putnbr_pf.c $(FT_PRINTF)/ft_putptr_pf.c \
              $(FT_PRINTF)/ft_putstr_pf.c $(FT_PRINTF)/ft_putuint_pf.c
OBJ         = $(SRC:.c=.o)

# Regla principal
all:        $(NAME)

# Construir el ejecutable
$(NAME):    $(OBJ)
		@echo " [ .. ] | Compilando libft.."
		@make -C $(LFT_DIR) > /dev/null
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) libft compilado con éxito!$(RESET)"
		@$(CC) $(CFLAGS) -o $@ $^ $(LIB)
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) Ejecutable $(NAME) construido con éxito!$(RESET)"

# Regla para compilar archivos fuente en objetos
src/%.o: src/%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ > /dev/null
	@echo " $(GREEN)[ OK ] $(CHECK_MARK) Compilado: $<$(RESET)"

$(FT_PRINTF)/%.o: $(FT_PRINTF)/%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ > /dev/null
	@echo " $(GREEN)[ OK ] $(CHECK_MARK) Compilado: $<$(RESET)"

# Limpiar archivos objetos y ejecutable
clean:
		@make -C $(LFT_DIR) clean > /dev/null
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
