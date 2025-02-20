override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

override MAINDIR	:= main/
override INITDIR	:= init/
override UTILSDIR	:= utils/
override ENVDIR		:= env/
override ASTDIR		:= ast/
override PARSINGDIR	:= parsing/
override EXECDIR	:= exec/
override BUILTINDIR	:= built_in/

SRC	+= $(addprefix $(MAINDIR), $(addsuffix .c, $(MAINSRC)))

override MAINSRC	:= \
	minishell \

SRC +=  $(addprefix $(INITDIR), $(addsuffix .c, $(INITSRC)))

override INITSRC	:= \
	env_init \
	minishell_init \
	signal_init \

SRC += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRC)))

override UTILSSRC	:= \
	free_utils \
	list_utils \

SRC += $(addprefix $(ENVDIR), $(addsuffix .c, $(ENVSRC)))

override ENVSRC		:= \
	env_update \
	env_utils \

SRC += $(addprefix $(ASTDIR), $(addsuffix .c, $(ASTSRC)))

override ASTSRC		:= \
	ast_print \
	ast_utils \
	ast_built \

SRC	+= $(addprefix $(PARSINGDIR), $(addsuffix .c, $(PARSINGSRC)))

override PARSINGSRC	:= \
	errors \
	operator_check \
	operators \
	quotes \
	token_utils \
	tokenizer \
	word_utils \

SRC	+= $(addprefix $(EXECDIR), $(addsuffix .c, $(EXECSRC)))
override EXECSRC	:= \
	exec \
	cmds_path \

SRC	+= $(addprefix $(BUILTINDIR), $(addsuffix .c, $(BUILTINSRC)))
override BUILTINSRC	:= \
	built_in \
	pwd \
	cd \
	unset \
	# export \
