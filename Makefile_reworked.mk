NAME	:= minishell

include minishell.mk

BUILD_DIR	:= .build/
OBJS 		:= $(patsubst $(SRCSDIR)%.c,$(BUILD_DIR)%.o,$(SRCS))
DEPS		:= $(OBJS:.o=.d)

# ********** FLAGS AND COMPILATION FLAGS ************************************* #

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -MMD -MP -I incs/ -I libft/incs/
RLFLAGS		:= -lreadline -lcurses # pourquoi lreadline et lcurses ? lcurses c'est pas pour la librarie graphique ncurse ?

RM			:= rm -f
RMDIR		+= -r
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(BUILD_DIR)

.DEFAULT_GOAL	:= all

# ********** DEBUG *********************************************************** #

# en bloc ici pour l'instant, on ferra peut etre des modes de compilations plus tard je sais pas comment faire pour l'instant

VALGRIND_SUPPRESS_FILE = .valgrind_suppress.txt

$(VALGRIND_SUPPRESS_FILE):
	@echo "{\n    leak readline\n    Memcheck:Leak\n    ...\n    fun:readline\n}" > $@
	@echo "{\n    leak add_history\n    Memcheck:Leak\n    ...\n    fun:add_history\n}" >> $@
	@echo "$(GREEN_BOLD)✓ $(VALGRIND_SUPPRESS_FILE) is ready$(RESETC)"

VALGRIND_FLAGS = valgrind \
	--suppressions=$(VALGRIND_SUPPRESS_FILE) \
	--leak-check=full \
	--trace-children=yes \
	--track-fds=yes \
	--show-leak-kinds=all \

# ********** RULES *********************************************************** #

-include $(DEPS)

.PHONY: all
all: $(NAME)

$(NAME): libft/libft.a Makefile $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(RLFLAGS) -o $(NAME) $(OBJS) -L libft -lft
	@echo "\n$(GREEN_BOLD)✓ $(NAME) is ready$(RESETC)"

# on peut rajouter tes petit emojis si tu veux 💫✨💫 🧹🧹🧹

libft/libft.a: FORCE
	@$(MAKE) -C libft

$(BUILD_DIR)%.o: $(SRCSDIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)[Compiling]$(RESETC) $<"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

.PHONY: valgrind
valgrind: $(VALGRIND_SUPPRESS_FILE) $(NAME)
	$(VALGRIND_FLAGS) ./$(NAME)

.PHONY: clean
clean:
	@$(MAKE) clean -C libft/
	@$(RM) $(OBJS) $(DEPS) $(VALGRIND_SUPPRESS_FILE)
	@echo "$(RED_BOLD)[Cleaning]$(RESETC)"

.PHONY: fclean
fclean: clean
	@$(MAKE) fclean -C libft/
	@$(RM) $(RMDIR) $(NAME) $(BUILD_DIR)
	@echo "$(RED_BOLD)✓ $(NAME) is fully cleaned!$(RESETC)"

.PHONY: re
re: fclean all

.PHONY: FORCE
FORCE:

.SILENT: clean fclean

# ********** COLORS AND BACKGROUND COLORS ************************************ #

RESETC				:=	\033[0m

GREEN_BOLD			:= \033[1;32m
RED_BOLD			:= \033[1;31m
CYAN				:= \033[0;36m
