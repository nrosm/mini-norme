# **************************************************************************** #
#                              MAKEFILE PARA MINISHELL                         #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3

LIBS        = -lreadline

SRCDIR      = src
OBJDIR      = obj
INCDIR      = include
LIBDIR      = libft
PRINTDIR    = ft_printf

SRC         = $(shell find $(SRCDIR) -name '*.c')
OBJ         = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

LIBFT       = $(LIBDIR)/libft.a
FT_PRINTF   = $(PRINTDIR)/libftprintf.a

INC_FLAGS   = -I$(INCDIR) -I$(LIBDIR) -I$(PRINTDIR)

GREEN       = \033[0;32m
NC          = \033[0m

# ****************************************************** #

all: $(LIBFT) $(FT_PRINTF) $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Compilando $(NAME)...$(NC)"
	$(CC) $(CFLAGS) $(INC_FLAGS) $^ -o $@ $(LIBFT) $(FT_PRINTF) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(LIBFT):
	@echo "$(GREEN)Compilando libft...$(NC)"
	@$(MAKE) -C $(LIBDIR)

$(FT_PRINTF):
	@echo "$(GREEN)Compilando ft_printf...$(NC)"
	@$(MAKE) -C $(PRINTDIR)

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C $(LIBDIR)
	@$(MAKE) clean -C $(PRINTDIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBDIR)
	@$(MAKE) fclean -C $(PRINTDIR)

re: fclean all

.PHONY: all clean fclean re
