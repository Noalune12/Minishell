# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gueberso <gueberso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 17:11:29 by lbuisson          #+#    #+#              #
#    Updated: 2025/01/31 18:04:09 by gueberso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -MMD -MP
RLFLAGS = -lreadline -lcurses
RM = rm -f

SRCS = minishell.c parsing.c struct.c

OBJDIR = objs

OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

LIBFT_DIR = libft
LIBFT_A = libft/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) $(LIBFT_A) -lft

all: $(LIBFT_A) $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) -o $(NAME) $(RLFLAGS)
	@echo "💫✨💫 \033[92mMinishell compiled\033[0m 💫✨💫"


$(OBJDIR)/%.o: %.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_OBJDIR)/%.o: $(LIBFT_SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A): libft

libft:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
	$(RM) -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(LIBFT_A)
	@echo "🧹🧹🧹 \033[92mCleaning minishell complete\033[0m 🧹🧹🧹"

re : fclean all

.PHONY : all clean fclean re libft

-include $(DEPS)
