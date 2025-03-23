#ifndef COMMON_H
# define COMMON_H

/* ---------- COLORS -------------------------------------------------------- */

# define RED        "\001\033[0;31m\002"
# define BOLD_RED   "\001\033[1;31m\002"
# define GREEN      "\001\033[1;32m\002"
# define YELLOW     "\001\033[1;33m\002"
# define BLUE       "\001\033[1;34m\002"
# define WHITE_BOLD "\001\033[1;37m\002"
# define PURPLE     "\001\033[0;35m\002"
# define CYAN       "\001\033[1;36m\002"
# define RESET      "\001\033[0m\002"

# define GREEN_ARROW "\001\033[32m\xe2\x9e\002\x9c\001\033[0m\002"
# define RED_ARROW   "\001\033[31m\xe2\x9e\002\x9c\001\033[0m\002"

/* ---------- ERROR MESSAGES ------------------------------------------------ */

# define SHLVL_TOO_HIGH	\
			"minishell: warning: shell level (%d) too high, resetting to 1\n"
# define FILENAME_SYNTAX "syntax error: missing filename after redirection\n"
# define NEWLINE_SYNTAX \
					"minishell: syntax error near unexpected token `newline'\n"
# define STR_SYNTAX "minishell: syntax error near unexpected token `%s'\n"
# define CHAR_SYNTAX "minishell: syntax error near unexpected token `%c'\n"
# define CMD_NOT_FOUND "minishell: %s: command not found\n"
# define FILE_NOT_FOUND "minishell: %s: %s: No such file or directory\n"
# define HEREDOC_ERROR_MESSAGE \
	"minishell: warning: here-document delimited by end-of-file (wanted `%s')\n"
# define ERROR_SYNTAX_TO_MODIFY "syntax error\n"
# define ERROR_OUTFILE "minishell: %s: Permission denied\n"
# define ERROR_INFILE "minishell: %s: No such file or directory\n"
# define SIGQUIT_MESSAGE "Quit (core dumped)\n"

/* ---------- BUILTIN ERRORS ------------------------------------------------ */

# define EXIT_ERROR "minishell: exit: %s: numeric argument required\n"
# define TOO_MANY_ARGS "minishell: %s: too many arguments\n"
# define EXPORT_ERROR "minishell: export: `%s': not a valid identifier\n"
# define CD_HOME "minishell: cd: HOME not set\n"
# define PWD_ERROR "minishell: pwd: %s: invalid option\npwd: usage: pwd\n"

/* ---------- ENV VARIABLES ------------------------------------------------- */

# define PWD            "PWD"
# define OLDPWD         "OLDPWD"
# define PATH           "PATH"
# define SHLVL          "SHLVL"
# define HOME           "HOME"
# define USER           "USER"
# define ENV_DEFAULT    "_/usr/bin/env"
# define MANPATH        "MANPATH=/usr/share/man:"

# define INIT_SHLVL		"SHLVL=1"

# define RESEARCHSHLVL	"SHLVL="
# define RESEARCHPWD	"PWD="

#endif
