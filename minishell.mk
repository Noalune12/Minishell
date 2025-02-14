override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

override TEMPDIR	:= temp/
override INITDIR	:= init/
override UTILSDIR	:= utils/
override ENVDIR		:= env/
override ASTDIR		:= ast/
override PARSINGDIR	:= parsing/

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

SRC += $(addprefix $(ASTDIR), $(addsuffix .c, $(ASTSRC)))

override ASTSRC		:= \
	ast_print \
	ast_utils \

SRC	+= $(addprefix $(PARSINGDIR), $(addsuffix .c, $(PARSINGSRC)))

override PARSINGSRC	:= \
	error_handling \
	operator_identifying \
	parsing_utils \
	quotes \
	token_first_to_rename \
	token_utils \
