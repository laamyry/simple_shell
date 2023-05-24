#ifndef _help_h
#define _help_h

#define PROMPT_MSG "$"
#define UNUSED __attribute__((unused))

#define BUFFER_SIZE 1024


#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	change the current directory of the shell.\n\n"\
"	If cd is used without an argument, it will be interpreted\n"\
"	as cd $HOME.\n"\
"	If argumenthelp is set to - (cd -), the command will be interpreted\n"\
"	as cd $OLDPWD.\n\n"

#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Simple-Shell Exit.\n\n"\
"	The shell exits with status N. If N is not specified, the exit status is used\n"\
"	It's the most recent executed command.\n\n"

#define HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\
"	Print environment.\n\n"\
"	The env command will be print a complete list of enviroment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Change or add an environment variable.\n\n"\
"	initialize a new environment variable, or modify an existing one\n"\
"	When there are not correct numbers of arguments print error message.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsetenv function deletes one variable from the environment.\n\n"\
"	Wen there are not correct numbers of arguments print error message.\n\n"

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Show built-in commands information.\n\n"\
"	Builtin commands summarized briefly. Use BUILTIN_NAME to display details\n"\
"	specified, gives detailed help on all commands matching BUILTIN_NAME,\n"\
"	otherwise the list of help topics is printed BUILTIN_NAME list.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifiying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"

#endif
