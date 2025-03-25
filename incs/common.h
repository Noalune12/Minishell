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

/* ---------- ARROWS -------------------------------------------------------- */

# define GREEN_ARROW "\001\033[32m\xe2\x9e\002\x9c\001\033[0m\002"
# define RED_ARROW   "\001\033[31m\xe2\x9e\002\x9c\001\033[0m\002"

/* ---------- ERROR MESSAGES ------------------------------------------------ */


# define NEWLINE_SYNTAX \
					"minishell: syntax error near unexpected token `newline'\n"
# define STR_SYNTAX "minishell: syntax error near unexpected token `%s'\n"
# define CHAR_SYNTAX "minishell: syntax error near unexpected token `%c'\n"

/* ---------- ENV VARIABLES ------------------------------------------------- */

# define PWD            "PWD"
# define SHLVL          "SHLVL"
# define ENV_DEFAULT    "_/usr/bin/env"
# define MANPATH        "MANPATH=/usr/share/man:"

# define INIT_SHLVL		"SHLVL=1"

# define RESEARCHSHLVL	"SHLVL="
# define RESEARCHPWD	"PWD="

# define DEFAULT_PROMPT	"minishell$>"

# define NOT_A_TTY		"minishell: not a tty\n"
# define MEM_ALLOC_ERR	"Memory allocation error\n"

#endif
