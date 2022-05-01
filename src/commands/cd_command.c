/*
** EPITECH PROJECT, 2022
** B-PSU-101-BDX-1-1-minishell1-maxime.senard
** File description:
** cd_command
*/

#include <string.h>
#include "local.h"

void pwd_handling(shell_env_t *shell_env)
{
    char *tmp = NULL;

    if (shell_env->old_cwd != NULL)
        free(shell_env->old_cwd);
    shell_env->old_cwd = shell_env->cwd;
    if ((tmp = getcwd(NULL, 0)) != NULL)
        shell_env->cwd = tmp;
    else
        shell_env->cwd = my_strdup(shell_env->cwd);
}

char *get_cd_home(shell_env_t *shell_env)
{
    char *home = NULL;

    home = get_env_var(shell_env->env, "HOME");
    if (home == NULL) {
        write(2, "No $HOME variable in environement.\n", 35);
        return NULL;
    }
    home = my_strdup(home);
    if (home == NULL) {
        write(2, "No $HOME variable in environement.\n", 35);
        return NULL;
    }
    return home;
}

int change_path(char *path)
{
    int ch = 0;
    char *err = NULL;

    if (path == NULL)
        return 84;
    ch = chdir(path);
    if (ch < 0) {
        err = strerror(errno);
        my_printerr("%s: %s.\n", path, err);
        return 84;
    }
    return 0;
}

char *parse_path(char *path, shell_env_t *shell_env)
{
    char *newpath = NULL;
    char *tmp = NULL;

    if (path == NULL)
        return NULL;
    for (; path[0] == ' '; path++);
    if (path[0] == '~') {
        path++;
        if ((tmp = get_cd_home(shell_env)) == NULL) {
            return NULL;
        }
        newpath = my_strcat(tmp, path);
        free(tmp);
        return newpath;
    }
    if (path[0] == '-')
        return my_strdup(shell_env->old_cwd);
    return my_strdup(path);
}

int cd_command(char **user_input_arr, shell_env_t *shell_env)
{
    int len = my_char_tabl_len(user_input_arr) - 1;
    char *path = NULL;

    if (len > 2) {
        write(2, "cd: Too many arguments.\n", 24);
        return 84;
    }
    if (len < 2) {
        if ((path = get_cd_home(shell_env)) == NULL)
            return 84;
    }
    if (len == 2)
        path = parse_path(user_input_arr[1], shell_env);
    if (path == NULL)
        return 84;
    if ((len = change_path(path)) == 0)
        pwd_handling(shell_env);
    free(path);
    return len;
}
