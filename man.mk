# ********** MAN PAGE SETTINGS *********************************************** #

MAN_BASE_DIR := man
MAN_DIR      := $(MAN_BASE_DIR)/man1
MAN_PAGE     := $(MAN_DIR)/options.1

# ********** MAN PAGE CONTENT ************************************************ #

$(MAN_PAGE):
	@echo "$(CYAN)[Setting up]$(RESETC) man page directory structure"
	@mkdir -p $(MAN_DIR)
	@echo "$(CYAN)[Creating]$(RESETC) man page for minishell"
	@echo ".\\\"Man page for minishell shell" > $@
	@echo ".TH MINISHELL 1 \"March 2025\" \"minishell 1.0\" \"User Commands\"" >> $@
	@echo ".SH NAME" >> $@
	@echo "minishell \\- a simplified Unix shell with bash-like functionality" >> $@
	@echo ".SH SYNOPSIS" >> $@
	@echo ".B minishell" >> $@
	@echo ".SH DESCRIPTION" >> $@
	@echo "Minishell is a simplified Unix shell that mimics bash in POSIX mode." >> $@
	@echo "It provides command execution, environment variable management, and" >> $@
	@echo "various other shell functionalities." >> $@
	@echo ".SH FEATURES" >> $@
	@echo ".SS Command Execution" >> $@
	@echo "Minishell executes commands found in PATH and handles" >> $@
	@echo "both internal builtins and external commands." >> $@
	@echo ".SS Operators" >> $@
	@echo "Minishell supports the following operators:" >> $@
	@echo ".TP" >> $@
	@echo ".B |" >> $@
	@echo "Pipe operator - connects output of one command to input of another." >> $@
	@echo ".TP" >> $@
	@echo ".B >" >> $@
	@echo "Output redirection - redirects command output to a file." >> $@
	@echo ".TP" >> $@
	@echo ".B <" >> $@
	@echo "Input redirection - uses file as input for a command." >> $@
	@echo ".TP" >> $@
	@echo ".B >>" >> $@
	@echo "Append redirection - appends command output to a file." >> $@
	@echo ".TP" >> $@
	@echo ".B <<" >> $@
	@echo "Here document - reads input until a delimiter is encountered." >> $@
	@echo ".TP" >> $@
	@echo ".B &&" >> $@
	@echo "Logical AND - executes second command only if first succeeds." >> $@
	@echo ".TP" >> $@
	@echo ".B ||" >> $@
	@echo "Logical OR - executes second command only if first fails." >> $@
	@echo ".TP" >> $@
	@echo ".B ()" >> $@
	@echo "Parentheses - used for grouping commands to control operator precedence." >> $@
	@echo ".SS Environment Variables" >> $@
	@echo "Environment variables can be set, unset, and expanded using the $ symbol." >> $@
	@echo ".SS Special Features" >> $@
	@echo ".TP" >> $@
	@echo ".B Variable expansion in heredocs" >> $@
	@echo "Environment variables are expanded in heredoc content." >> $@
	@echo ".TP" >> $@
	@echo ".B export +=" >> $@
	@echo "Append mode for export - allows appending values to existing variables." >> $@
	@echo ".TP" >> $@
	@echo ".B cd -" >> $@
	@echo "Returns to the previous directory (OLDPWD)." >> $@
	@echo ".SS Debugging Options" >> $@
	@echo "Minishell includes debugging tools accessed via special builtins:" >> $@
	@echo ".TP" >> $@
	@echo ".B options" >> $@
	@echo "Displays current state of all debugging options." >> $@
	@echo ".TP" >> $@
	@echo ".B ptree" >> $@
	@echo "Toggles display of the Abstract Syntax Tree (AST)." >> $@
	@echo ".TP" >> $@
	@echo ".B ptokens" >> $@
	@echo "Toggles display of the token list from lexical analysis." >> $@
	@echo ".SH BUILTINS" >> $@
	@echo "Minishell implements the following builtin commands:" >> $@
	@echo ".TP" >> $@
	@echo ".B cd [dir]" >> $@
	@echo "Change the current directory to DIR." >> $@
	@echo ".TP" >> $@
	@echo ".B echo [-n] [string ...]" >> $@
	@echo "Display a line of text." >> $@
	@echo ".TP" >> $@
	@echo ".B env" >> $@
	@echo "Print the environment." >> $@
	@echo ".TP" >> $@
	@echo ".B exit [n]" >> $@
	@echo "Exit the shell with a status of N." >> $@
	@echo ".TP" >> $@
	@echo ".B export [name[=value] ...]" >> $@
	@echo "Set export attribute for shell variables." >> $@
	@echo ".TP" >> $@
	@echo ".B pwd" >> $@
	@echo "Print the current working directory." >> $@
	@echo ".TP" >> $@
	@echo ".B unset [name ...]" >> $@
	@echo "Unset values and attributes of shell variables." >> $@
	@echo ".TP" >> $@
	@echo ".B options [debug_option]" >> $@
	@echo "Display or toggle debugging options." >> $@
	@echo ".TP" >> $@
	@echo ".B ptree" >> $@
	@echo "Toggle the AST visualization." >> $@
	@echo ".TP" >> $@
	@echo ".B ptokens" >> $@
	@echo "Toggle token visualization." >> $@
	@echo ".SH EXAMPLES" >> $@
	@echo ".TP" >> $@
	@echo ".B ls -la | grep file" >> $@
	@echo "List files and filter for 'file'." >> $@
	@echo ".TP" >> $@
	@echo ".B (ls && echo success) || echo failure" >> $@
	@echo "Uses grouping and logical operators." >> $@
	@echo ".TP" >> $@
	@echo ".B cat << EOF > output.txt" >> $@
	@echo "Here document redirected to a file." >> $@
	@echo ".TP" >> $@
	@echo ".B cd - && pwd" >> $@
	@echo "Return to previous directory and display it." >> $@
	@echo ".TP" >> $@
	@echo ".B export VAR+=value" >> $@
	@echo "Append to existing environment variable." >> $@
	@echo ".TP" >> $@
	@echo ".B options" >> $@
	@echo "Show current debugging options." >> $@
	@echo ".SH EXIT STATUS" >> $@
	@echo "The exit status of the last command executed is stored in the" >> $@
	@echo "environment variable '?' and displayed in the prompt." >> $@
	@echo ".SH SEE ALSO" >> $@
	@echo ".BR bash (1)" >> $@
	@echo ".SH AUTHOR" >> $@
	@echo "lbuisson & gueberso" >> $@
	@chmod 644 $(MAN_PAGE)
