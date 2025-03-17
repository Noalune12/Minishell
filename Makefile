NAME	:= minishell

include man.mk
include minishell.mk

BUILD_DIR	:= .build/
OBJS 		:= $(patsubst $(SRCSDIR)%.c,$(BUILD_DIR)%.o,$(SRCS))
DEPS		:= $(OBJS:.o=.d)

# ********** FLAGS AND COMPILATION FLAGS ************************************* #

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g3 # ENLEVER G3
CPPFLAGS	:= -MMD -MP -I incs/ -I libft/incs/
RLFLAGS		:= -lreadline

RM			:= rm -f
RMDIR		+= -r
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(BUILD_DIR)

.DEFAULT_GOAL	:= all

# ********** DEBUG *********************************************************** #

# en bloc ici pour l'instant, on ferra peut etre des modes de compilations plus tard je sais pas comment faire pour l'instant

VALGRIND_SUPPRESS_FILE := $(abspath .valgrind_suppress.txt)

$(VALGRIND_SUPPRESS_FILE):
	@echo "{\n    leak readline\n    Memcheck:Leak\n    ...\n    fun:readline\n}" > $@
	@echo "{\n    leak add_history\n    Memcheck:Leak\n    ...\n    fun:add_history\n}" >> $@

VALGRIND_FLAGS := valgrind \
	--suppressions=$(VALGRIND_SUPPRESS_FILE) \
	--leak-check=full \
	--track-origins=yes \
	--trace-children=yes \
	--track-fds=yes \
	--show-leak-kinds=all \

# ********** RULES *********************************************************** #

-include $(DEPS)

.PHONY: init
init:
	@mkdir -p $(BUILD_DIR)
	@echo "$(words $(SRCS))" > $(BUILD_DIR)total_files
	@echo "0" > $(BUILD_DIR)current_file
	@date +%s > $(BUILD_DIR)start_time

.PHONY: all
all: init $(NAME)

$(NAME): libft/libft.a Makefile $(OBJS) $(MAN_PAGE)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJS) -L libft -lft $(RLFLAGS)
	@echo "\n$(GREEN_BOLD)✓ $(NAME) is ready$(RESETC)\n"

# on peut rajouter tes petit emojis si tu veux 💫✨💫 🧹🧹🧹

libft/libft.a: FORCE
	@$(MAKE) -C libft

$(BUILD_DIR)%.o: $(SRCSDIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	@CURRENT=`cat $(BUILD_DIR)current_file`; \
	CURRENT=$$((CURRENT+1)); \
	echo "$$CURRENT" > $(BUILD_DIR)current_file; \
	TOTAL=`cat $(BUILD_DIR)total_files`; \
	START=`cat $(BUILD_DIR)start_time`; \
	NOW=`date +%s`; \
	ELAPSED=$$((NOW-START)); \
	POSITION=$$((CURRENT % 6)); \
	printf "$(ERASE)$(CYAN)["; \
	if [ "$$POSITION" -eq 0 ]; then \
		printf "⠋"; \
	elif [ "$$POSITION" -eq 1 ]; then \
		printf "⠙"; \
	elif [ "$$POSITION" -eq 2 ]; then \
		printf "⠹"; \
	elif [ "$$POSITION" -eq 3 ]; then \
		printf "⠸"; \
	elif [ "$$POSITION" -eq 4 ]; then \
		printf "⠼"; \
	else \
		printf "⠴"; \
	fi; \
	printf "] [%d/%d] $(RESETC)%s" "$$CURRENT" "$$TOTAL" "$<"

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
	@$(RM) $(RMDIR) $(MAN_BASE_DIR)
	@echo "$(RED_BOLD)✓ $(NAME) is fully cleaned!$(RESETC)"

.PHONY: re
re: fclean all

.PHONY: FORCE
FORCE:

.SILENT: clean fclean

# ********** COLORS AND BACKGROUND COLORS ************************************ #

RESETC				:=	\033[0m
ERASE				:=	\033[2K\r

GREEN_BOLD			:= \033[1;32m
RED_BOLD			:= \033[1;31m
CYAN				:= \033[0;36m
