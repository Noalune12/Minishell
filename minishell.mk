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
override SIGNALSDIR	:= signals/

SRC	+= $(addprefix $(EXPANDDIR), $(addsuffix .c, $(EXPANDSRC)))

override EXPANDSRC	:= \
	expand_calc_len \
	expand_heredoc \
	expand_init \
	expand_len_utils \
	expand_main_loop \
	expand_quote_handling \
	expand_utils \
	expand \

SRC	+= $(addprefix $(MAINDIR), $(addsuffix .c, $(MAINSRC)))

override MAINSRC	:= \
	minishell \
	loop \
	prompt \

SRC +=  $(addprefix $(INITDIR), $(addsuffix .c, $(INITSRC)))

override INITSRC	:= \
	env_init \
	minishell_init \

SRC += $(addprefix $(UTILSDIR), $(addsuffix .c, $(UTILSSRC)))

override UTILSSRC	:= \
	cleanup_minishell \
	free_utils \
	list_utils \
	t_token_utils

SRC += $(addprefix $(ENVDIR), $(addsuffix .c, $(ENVSRC)))

override ENVSRC		:= \
	env_update \
	env_utils \

SRC += $(addprefix $(ASTDIR), $(addsuffix .c, $(ASTSRC)))

override ASTSRC		:= \
	ast_add \
	ast_built \
	ast_cmd_redir \
	ast_heredoc \
	ast_identification \
	ast_node_creation \
	ast_print_utils \
	ast_print \
	ast_utils \

SRC	+= $(addprefix $(PARSINGDIR), $(addsuffix .c, $(PARSINGSRC)))

override PARSINGSRC	:= \
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
	and_exec \
	exec \
	cmd_check \
	cmd_path \
	cmd_path_utils \
	cmd_exec \
	or_exec \
	pipe_exec \
	redirappend_exec \
	redirin_exec \
	redirout_exec \
	heredoc_exec \
	exec_utils \
	handle_fd \
	expand_quotes_exec \
	quotes_utils \
	remake_cmds \

SRC	+= $(addprefix $(BUILTINDIR), $(addsuffix .c, $(BUILTINSRC)))

override BUILTINSRC	:= \
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
	wildcard_utils \
	wildcard \

SRC += $(addprefix $(OPTIONSDIR), $(addsuffix .c, $(OPTIONSSRC)))

override OPTIONSSRC	:= \
	print_tokens \
	wrappers \

SRC	+= $(addprefix $(SIGNALSDIR), $(addsuffix .c, $(SIGNALSSRC)))

override SIGNALSSRC	:= \
	signals_init \
	signals_utils \
