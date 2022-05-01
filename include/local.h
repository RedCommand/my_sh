/*
** EPITECH PROJECT, 2022
** B-PSU-101-BDX-1-1-minishell1-maxime.senard
** File description:
** local
*/

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my.h"
#include "list.h"
#include "file.h"
#include "printf.h"
#include "printerr.h"

#ifndef LOCAL_H
    #define LOCAL_H

    #define free_exit(item) free(item); return NULL
    #define free_if_exist(item) if (item != NULL) free(item)

typedef struct command_s {
    char *name;
    char *path;
} command_t;

typedef struct shell_env_s {
    char **env;
    char *path;
    char **paths;
    char *cwd;
    char *old_cwd;
    list_t *commands;
} shell_env_t;

typedef struct run_s {
    shell_env_t *shell_env;
    char *command_path;
    char **command;
    int *exit_code;
    char *std_in;
    int std_in_fd;
} run_t;

int minishell(char **env, bool pt);
int *exit_code_ptr(void);
char **path_ptr(void);
bool *pt_ptr(void);
void set_globals(int exit_code, bool pt, char *path);
char **str_to_array(char *str, char *separators);
char **ducplicate_char_arr(char **arr);
int count_with_separators(char *document, char *separators);
int count_char_before_separator(char *document, char *separators);
int is_in_str(char *str, char c);
list_t *get_avalable_command(char **paths);
bool is_str_eq(char *str1, char *str2);
void free_char_arr(char **arr, bool free_base);
shell_env_t *free_shell_env(shell_env_t *shell_env);
shell_env_t *init_shell_env(char **env);
char *get_env_var(char **env, char *key);
int run_proccess(run_t *run, int stds[3]);
char *get_user_command_line(char **user_input_arr, shell_env_t *shell_env,
int *exit_code);
char *get_user_command(char *user_command, shell_env_t *shell_env);
char *find_command_path(char *command, list_t *commands);
char *get_user_input(char *user_input, int *exit_code, char *path, bool pt);
int check_env_name(char *name);
int dell_env_var(char *key, char **env);
char **extract_commands(char *user_input, char **env);
int run_commands(char **commands, shell_env_t *shell_env);
void command_error_message(char *command_path, char *command_name);
void signals_handler(void);
int exec_p(run_t *run, int fd_in, int fd_out, int fd_err);
int run_pipes(char *command, shell_env_t *shell_env);
char *parse_variables(char *command, char **env);
int get_fd_in(run_t *run);
int get_fd_out(run_t *run);
int get_fd_err(run_t *run);

int cd_command(char **user_input_arr, shell_env_t *shell_env);
int env_command(char **user_input_arr, shell_env_t *shell_env);
int setenv_command(char **user_input_arr, shell_env_t *shell_env);
int unsetenv_command(char **user_input_arr, shell_env_t *shell_env);

#endif
