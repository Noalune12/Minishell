override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

override TEMPDIR	:= temp/
override INITDIR	:= init/
override UTILSDIR	:= utils/
override ENVDIR		:= env/

SRC	+= $(addprefix $(TEMPDIR), $(addsuffix .c, $(TEMPSRC)))

override TEMPSRC	:= \
	minishell \
	#practice \

SRC +=  $(addprefix $(INITDIR), $(addsuffix .c, $(INITSRC)))

override INITSRC	:= \
	minishell_init \
	env_init \

SRC += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRC)))

override UTILSSRC	:= \
	list_utils \

SRC += $(addprefix $(ENVDIR), $(addsuffix .c, $(ENVSRC)))

override ENVSRC		:= \
	env_shlvl \
	env_pwd \

