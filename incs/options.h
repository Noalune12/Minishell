#ifndef OPTIONS_H
# define OPTIONS_H

# include "stdbool.h"

typedef struct s_minishell	t_minishell;
typedef void				(*t_option_handler)(t_minishell *);

# define PRINT_ACTIVATED	"print %s\t%sactivated%s\n"
# define PRINT_UNACTIVATED	"print %s\t%sunactivated%s\n"

# define PTREE				"tree"
# define PTOKENS			"tokens"

# define OPTIONS_MAN		"%sOPTIONS(1)%s\t\t\t\t%sUser Commands%s\t\t\t \
	\t%sOPTIONS(1)%s\n\n%sNAME%s\n\t \
	options - display and control debugging options in minishell \
	\n\n%sSYNOPSIS%s\n\t\toptions [debug_option]\n\n%sDESCRIPTION%s\n \
	\tThe options command displays or modifies the debugging information\n \
	\tshown during minishell execution. When used without arguments, it\n \
	\tshows the current state of all available debug options.\n\n%sOPTIONS%s \
	\n\n\t\t%sptree%s\t \
	Enable or toggle the display of Abstract Syntax Tree \
	(AST)\n\t\t\t\tcreation during command parsing and execution. This shows\n \
	\t\t\tthe hierarchical structure of commands and operators.\n\n \
	\t%sptokens%s\t\tEnable or toggle the display of tokenization process, \
	showing\n\t\t\t\thow input is split into tokens before parsing. \
	\n\n%sEXAMPLES%s\n\t\toptions\n\t\t\t \
	Display current state of all debug options.\n\n\t\tptree\n \
	\t\t\tToggle the AST visualization option.\n\n\t\tptokens\n \
	\t\t\tToggle the token visualization option.\n\n%sNOTES%s\n \
	\tThese debugging options are intended for development and purposes. \
	\n\t\tThey provide insight into how the shell parser works\n \
	\tinternally.\n\n"

typedef enum e_options
{
	AST,
	TOKENS,
	OPTIONS,
	MAN,
}	t_options_enum;

typedef struct s_options
{
	bool	display_ast;
	bool	display_tokens;
}	t_options;

void	check_entry(t_minishell *minishell);
void	man_options(void);
void	print_toggled_options(t_minishell *minishell);
void	print_tokens(t_minishell *minishell);

void	ast_wrapper(t_minishell *minishell);
void	man_wrapper(t_minishell *minishell);
void	options_wrapper(t_minishell *minishell);
void	tokens_wrapper(t_minishell *minishell);

#endif
