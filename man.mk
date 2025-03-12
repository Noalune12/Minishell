# ********** MAN PAGE SETTINGS *********************************************** #

MAN_BASE_DIR := man
MAN_DIR      := $(MAN_BASE_DIR)/man1
MAN_PAGE     := $(MAN_DIR)/options.1

# ********** MAN PAGE CONTENT ************************************************ #

$(MAN_PAGE):
	@echo "$(CYAN)[Setting up]$(RESETC) man page directory structure"
	@mkdir -p $(MAN_DIR)
	@echo "$(CYAN)[Creating]$(RESETC) man page for options >>>> 'man pages ?'
	@echo ".\\\"Man page for minishell options builtin" > $@
	@echo ".TH OPTIONS 1 \"March 2025\" \"minishell 1.0\" \"User Commands\"" >> $@
	@echo ".SH NAME" >> $@
	@echo "options \\- display and control debugging options in minishell" >> $@
	@echo ".SH SYNOPSIS" >> $@
	@echo ".B options" >> $@
	@echo "[debug_option]" >> $@
	@echo ".SH DESCRIPTION" >> $@
	@echo "The" >> $@
	@echo ".B options" >> $@
	@echo "command displays or modifies the debugging information" >> $@
	@echo "shown during minishell execution. When used without arguments, it" >> $@
	@echo "shows the current state of all available debug options." >> $@
	@echo ".SH OPTIONS" >> $@
	@echo ".TP" >> $@
	@echo ".B ptree" >> $@
	@echo "Enable or toggle the display of Abstract Syntax Tree (AST)" >> $@
	@echo "creation during command parsing and execution. This shows" >> $@
	@echo "the hierarchical structure of commands and operators." >> $@
	@echo ".TP" >> $@
	@echo ".B ptokens" >> $@
	@echo "Enable or toggle the display of tokenization process, showing" >> $@
	@echo "how input is split into tokens before parsing." >> $@
	@echo ".SH EXAMPLES" >> $@
	@echo ".TP" >> $@
	@echo ".B options" >> $@
	@echo "Display current state of all debug options." >> $@
	@echo ".TP" >> $@
	@echo ".B options ptree" >> $@
	@echo "Toggle the AST visualization option." >> $@
	@echo ".TP" >> $@
	@echo ".B options ptokens" >> $@
	@echo "Toggle the token visualization option." >> $@
	@echo ".SH NOTES" >> $@
	@echo "These debugging options are intended for development purposes." >> $@
	@echo "They provide insight into how the shell parser works" >> $@
	@echo "internally." >> $@
	@echo ".SH SEE ALSO" >> $@
	@echo ".BR minishell (1)" >> $@
	@echo ".SH AUTHOR" >> $@
	@echo "42 Student" >> $@
	@chmod 644 $(MAN_PAGE)
