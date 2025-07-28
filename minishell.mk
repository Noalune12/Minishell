override SRCSDIR	:= srcs/
override SRCS		= $(addprefix $(SRCSDIR), $(SRC))

override ASTDIR		:= ast/
override BUILTINDIR	:= built_in/
override ENVDIR		:= env/
override EXECDIR	:= exec/
override EXPANDDIR	:= expand/
override HEREDOCDIR	:= heredoc/
override INITDIR	:= init/
override OPTIONSDIR	:= options/
override PARSINGDIR	:= parsing/
override PROCESSDIR	:= minishell_process/
override SIGNALSDIR	:= signals/
override UTILSDIR	:= utils/
override WILDCARDIR	:= wildcard/

SRC	+= $(addsuffix .c, $(MAIN))

override MAIN			:= \
	minishell \

SRC += $(addprefix $(ASTDIR), $(addsuffix .c, $(ASTSRC)))

override ASTSRC			:= \
	ast_add \
	ast_built \
	ast_cmd_redir \
	ast_heredoc \
	ast_identification \
	ast_node_creation \
	ast_print_utils \
	ast_print \
	ast_utils \

SRC	+= $(addprefix $(BUILTINDIR), $(addsuffix .c, $(BUILTINSRC)))

override BUILTINSRC		:= \
	built_in \
	cd_update_env \
	cd \
	echo \
	exit \
	export_add_env \
	export_append \
	export_args \
	export_copy_env \
	export \
	options \
	pwd \
	unset \
	utils_builtin \

SRC += $(addprefix $(ENVDIR), $(addsuffix .c, $(ENVSRC)))

override ENVSRC			:= \
	env_update \
	env_utils \

SRC	+= $(addprefix $(EXECDIR), $(addsuffix .c, $(EXECSRC)))

override EXECSRC		:= \
	and_exec \
	cmd_check \
	cmd_exec \
	cmd_path_utils \
	cmd_path \
	exec_utils \
	exec \
	expand_routine \
	expand_utils \
	handle_fd \
	heredoc_exec \
	or_exec \
	pipe_exec \
	quotes_utils \
	redirappend_exec \
	redirin_exec \
	redirout_exec \
	remake_cmds

SRC	+= $(addprefix $(EXPANDDIR), $(addsuffix .c, $(EXPANDSRC)))

override EXPANDSRC		:= \
	expand_calc_len \
	expand_heredoc \
	expand_init \
	expand_len_utils \
	expand_main_loop \
	expand_quote_handling \
	expand_utils \
	expand

SRC += $(addprefix $(HEREDOCDIR), $(addsuffix .c, $(HEREDOCSRC)))

override HEREDOCSRC	:= \
	heredoc_file_utils \
	heredoc_in_out \
	heredoc_process \
	heredoc_utils \
	heredoc \

SRC +=  $(addprefix $(INITDIR), $(addsuffix .c, $(INITSRC)))

override INITSRC		:= \
	env_init \
	minishell_init \
	prompt \

SRC	+= $(addprefix $(PROCESSDIR), $(addsuffix .c, $(PROCESSSRC)))

override PROCESSSRC		:= \
	loop \

SRC += $(addprefix $(OPTIONSDIR), $(addsuffix .c, $(OPTIONSSRC)))

override OPTIONSSRC		:= \
	print_tokens \
	wrappers \

SRC	+= $(addprefix $(PARSINGDIR), $(addsuffix .c, $(PARSINGSRC)))

override PARSINGSRC		:= \
	operator_utils \
	operators \
	parenthesis_check \
	quotes \
	syntax_check \
	token_utils \
	tokenizer \
	word_utils \

SRC	+= $(addprefix $(SIGNALSDIR), $(addsuffix .c, $(SIGNALSSRC)))

override SIGNALSSRC		:= \
	signals_init \
	signals_utils \

SRC += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRC)))

override UTILSSRC		:= \
	cleanup_minishell \
	free_utils \
	list_utils \
	t_token_utils

SRC += $(addprefix $(WILDCARDIR), $(addsuffix .c, $(WILDCARDSRC)))

override WILDCARDSRC	:= \
	create_array \
	file_utils \
	patterns \
	wildcard \
	wildcard_utils
