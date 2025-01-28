# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 08:31:01 by lbuisson          #+#    #+#              #
#    Updated: 2025/01/17 14:59:11 by lbuisson         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra -MMD -MP

NAME = libft.a

RM = rm -f

SRCDIR = srcs
OBJDIR = objs

LIBFT = $(SRCDIR)/libft
PRINTF = $(SRCDIR)/ft_printf
GNL = $(SRCDIR)/gnl

FUNCTIONS = $(LIBFT)/ft_atoi.c $(LIBFT)/ft_bzero.c $(LIBFT)/ft_calloc.c $(LIBFT)/ft_isalnum.c $(LIBFT)/ft_isalpha.c $(LIBFT)/ft_isascii.c \
	$(LIBFT)/ft_isdigit.c $(LIBFT)/ft_isprint.c $(LIBFT)/ft_itoa.c $(LIBFT)/ft_memchr.c $(LIBFT)/ft_memcmp.c \
	$(LIBFT)/ft_memcpy.c $(LIBFT)/ft_memmove.c $(LIBFT)/ft_memset.c $(LIBFT)/ft_putchar_fd.c $(LIBFT)/ft_putendl_fd.c \
	$(LIBFT)/ft_putnbr_fd.c $(LIBFT)/ft_putstr_fd.c $(LIBFT)/ft_split.c $(LIBFT)/ft_strchr.c $(LIBFT)/ft_strdup.c \
	$(LIBFT)/ft_strjoin.c $(LIBFT)/ft_strlcat.c $(LIBFT)/ft_strlcpy.c $(LIBFT)/ft_strlen.c $(LIBFT)/ft_strmapi.c \
	$(LIBFT)/ft_striteri.c $(LIBFT)/ft_strncmp.c $(LIBFT)/ft_strnstr.c $(LIBFT)/ft_strrchr.c $(LIBFT)/ft_substr.c \
	$(LIBFT)/ft_strtrim.c $(LIBFT)/ft_tolower.c $(LIBFT)/ft_toupper.c \
	$(LIBFT)/ft_lstnew.c $(LIBFT)/ft_lstadd_front.c $(LIBFT)/ft_lstsize.c $(LIBFT)/ft_lstlast.c $(LIBFT)/ft_lstadd_back.c \
	$(LIBFT)/ft_lstdelone.c $(LIBFT)/ft_lstclear.c $(LIBFT)/ft_lstiter.c $(LIBFT)/ft_lstmap.c \
	$(PRINTF)/ft_numbers.c $(PRINTF)/ft_words_pointer.c $(PRINTF)/ft_printf.c \
	$(GNL)/get_next_line.c $(GNL)/get_next_line_utils.c

OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(FUNCTIONS))
DEPS = $(OBJS:.o=.d)

all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)
	@echo "💫✨💫 \033[92mLibft compiled\033[0m 💫✨💫"

$(OBJDIR)/%.o : $(SRCDIR)/%.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) -rf $(OBJDIR)

fclean : clean
	$(RM) $(NAME)
	@echo "🧹🧹🧹 \033[92mCleaning libft complete\033[0m 🧹🧹🧹"

re : fclean all

.PHONY : all clean fclean re bonus

-include $(DEPS)
