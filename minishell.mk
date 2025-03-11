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
override HEREDOCDIR	:= heredoc/
override EXPANDDIR	:= expand/
override WILDCARDIR	:= wildcard/
override OPTIONSDIR	:= options/


SRC	+= $(addprefix $(EXPANDDIR), $(addsuffix .c, $(EXPANDSRC)))

override EXPANDSRC	:= \
	expand \
	expand_utils \
	expand_quote_removal \
	expand_quote_handling \
	expand_len_utils \

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
	t_token_utils

SRC += $(addprefix $(ENVDIR), $(addsuffix .c, $(ENVSRC)))

override ENVSRC		:= \
	env_update \
	env_utils \

SRC += $(addprefix $(ASTDIR), $(addsuffix .c, $(ASTSRC)))

override ASTSRC		:= \
	ast_built \
	ast_print_utils \
	ast_print \
	ast_utils \

SRC	+= $(addprefix $(PARSINGDIR), $(addsuffix .c, $(PARSINGSRC)))

override PARSINGSRC	:= \
	errors \
	operator_check \
	operator_utils \
	operators \
	parenthesis_check \
	quotes \
	syntax_check \
	token_utils \
	tokenizer \
	word_utils \

SRC	+= $(addprefix $(EXECDIR), $(addsuffix .c, $(EXECSRC)))
override EXECSRC	:= \
	exec \
	cmds_path \
	cmd_exec \
	pipe_exec \
	redirappend_exec \
	redirin_exec \
	redirout_exec \
	heredoc_exec \
	exec_utils \

SRC	+= $(addprefix $(BUILTINDIR), $(addsuffix .c, $(BUILTINSRC)))

override BUILTINSRC	:= \
	built_in \
	pwd \
	cd \
	cd_update_env \
	unset \
	export \
	export_args \
	export_copy_env \
	export_add_env \
	export_append \
	utils_builtin \
	echo \
	exit \

SRC += $(addprefix $(HEREDOCDIR), $(addsuffix .c, $(HEREDOCSRC)))

override HEREDOCSRC	:= \
	heredoc_exec \
	heredoc_utils \
	heredoc_file_utils \
	heredoc_in_out \
	heredoc_process \
	heredoc \

SRC += $(addprefix $(WILDCARDIR), $(addsuffix .c, $(WILDCARDSRC)))

override WILDCARDSRC	:= \
	file_utils \
	patterns \
	wildcard_cleanup \
	wildcard_utils \
	wildcard \

SRC += $(addprefix $(OPTIONSDIR), $(addsuffix .c, $(OPTIONSSRC)))

override OPTIONSSRC	:= \
	options_setup \
	print_tokens \
	wrappers \
