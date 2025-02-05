override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

override TEMPDIR	:= temp/

SRC	+= $(addprefix $(TEMPDIR), $(addsuffix .c, $(TEMPSRC)))

override TEMPSRC	:= \
	minishell \
	struct \
	practice \
	#parsing \
