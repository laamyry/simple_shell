#ifndef _shell_h
#define _shell_h

#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <signal.h> 
#include <fcntl.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "macros.h"


/**
 * struct info- program's data.
 * @program_name: the name of the executable
 * @new_line: pointer to the input read for _getline
 * @cmd_name: pointer to the first command typed by the user
 * @run_count: number of excecuted comands
 * @file_identifier: file descriptor to the input of commands
 * @symbols: pointer to array of tokenized input
 * @env: copy of the environ
 * @list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *new_line;
	char *cmd_name;
	int run_count;
	int file_identifier;
	char **symbols;
	char **env;
	char **list;
} program_data;

/**
 * struct internals - struct for the internals
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct internals
{
	char *builtin;
	int (*function)(program_data *data);
} internals;


void initialize_data(program_data *data, int arc, char *argv[], char **env);

void sisifo(char *prompt, program_data *data);

void handle_ctrl_c(int opr UNUSED);


int _getline(program_data *data);

int check_operas(char *cmd_array[], int i, char operas_array[]);



void extend_var(program_data *data);

void extend_alias(program_data *data);

int add_buf(char *buff, char *string_add);


void symbolize(program_data *data);

char *_strtok(char *ln, char *delim);

int run(program_data *data);


int internal_list(program_data *data);

int file_chekcer(char *full_path);

char **symbolize_path(program_data *data);

int locat_prog(program_data *data);


void arr_free(char **directs);

void free_Periodic(program_data *data);

void free_data(program_data *data);


int shell_exit(program_data *data);

int shell_cd(program_data *data);

int work_d_set(program_data *data, char *new_d);

int shell_help(program_data *data);

int alias_shell(program_data *data);


int internal_env(program_data *data);

int internal_env_set(program_data *data);

int internal_env_clear(program_data *data);


char *env_key(char *name, program_data *data);

int env_key_set(char *key, char *value, program_data *data);

int delete_env_key(char *key, program_data *data);

void print_env(program_data *data);


int _print(char *string);

int _printf(char *string);

int _print_err(int error_c, program_data *data);


int str_len(char *string);

char *str_dupl(char *string);

int str_cmp(char *str1, char *str2, int number);

char *str_join(char *str1, char *str2);

void flip_str(char *string);


void long_str(long number, char *string, int base);

int _atoi(char *s);

int char_counter(char *string, char *character);


int p_alias(program_data *data, char *alias);

char *obt_alias(program_data *data, char *alias);

int esta_alias(char *alias_str, program_data *data);


#endif
