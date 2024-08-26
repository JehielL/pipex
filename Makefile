# Nombre del ejecutable
NAME        = pipex

# Compilador y flags
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g -fsanitize=address
LFT_DIR     = utils/libft
INC         = -I ./utils/libft 
LIB         = -L ./utils/libft

# Colores
GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m
CHECK_MARK  = \033[1;32m✔\033[0m

# Archivos fuente y objetos
SRC         = src/pipex.c
        
OBJ         = $(SRC:.c=.o)

# Regla principal
all:        $(NAME)

# Compilar el ejecutable
$(NAME):    $(OBJ)
		@echo " [ .. ] | Compilando libft.."
		@make -C $(LFT_DIR) > /dev/null
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) libft compilado con éxito!$(RESET)"

		@$(CC) $(CFLAGS) -o $@ $^ $(LIB)
		@echo " $(GREEN)[ OK ] $(CHECK_MARK) Ejecutable $(NAME) construido con éxito!$(RESET)"

# Regla para compilar cada archivo fuente en objeto
%.o: %.c
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
