/*
** EPITECH PROJECT, 2022
** B-PSU-101-BDX-1-1-minishell1-maxime.senard
** File description:
** env_utils
*/

#include "local.h"

char *get_env_var(char **env, char *key)
{
    char *tmpkey = NULL;

    if (env == NULL || key == NULL)
        return NULL;
    if ((tmpkey = my_strcat(key, "=")) == NULL)
        return NULL;
    for (int i = 0; env[i] != NULL; i++) {
        if (str_start_with(env[i], tmpkey, my_strlen(env[i]),
            my_strlen(tmpkey)) == 1) {
            free(tmpkey);
            return (&env[i][my_strlen(key) + 1]);
        }
    }
    free(tmpkey);
    my_printerr("%s: Undefined variable.\n", key);
    return NULL;
}

char **generete_empty_env(void)
{
    char **env = NULL;

    if ((env = malloc(sizeof(char*) * 2)) == NULL)
        return NULL;
    env[1] = NULL;
    if ((env[0] = my_strdup("PATH=/usr/bin")) == NULL)
        return NULL;
    return env;
}

char *init_path(char **env)
{
    char *path = NULL;

    if (env == NULL)
        return NULL;
    if ((path = get_env_var(env, "PATH")) == NULL || path[0] == '\0') {
        my_printerr("setting default path: /usr/bin\n");
        if (opendir("/usr/bin") == NULL) {
            my_printerr("/usr/bin: No such file or directory, exiting.\n");
            return NULL;
        }
        return my_strdup("/usr/bin");
    }
    return path;
}

shell_env_t *init_shell_env(char **env)
{
    shell_env_t *shell_env = malloc(sizeof(shell_env_t));

    if (shell_env == NULL)
        return NULL;
    if (env != NULL && env[0] != NULL) {
        if ((shell_env->env = ducplicate_char_arr(env)) == NULL)
            return free_shell_env(shell_env);
    } else if ((shell_env->env = generete_empty_env()) == NULL)
        return free_shell_env(shell_env);
    if ((shell_env->path = init_path(shell_env->env)) == NULL)
        return free_shell_env(shell_env);
    shell_env->paths = str_to_array(shell_env->path, ": \n\0");
    if (shell_env->paths == NULL || (shell_env->cwd = getcwd(NULL, 0)) == NULL)
        return free_shell_env(shell_env);
    shell_env->old_cwd = my_strdup(shell_env->cwd);
    if ((shell_env->commands = get_avalable_command(shell_env->paths)) == NULL)
        return free_shell_env(shell_env);
    return shell_env;
}

shell_env_t *free_shell_env(shell_env_t *shell_env)
{
    if (shell_env == NULL)
        return NULL;
    free_char_arr(shell_env->paths, true);
    free_char_arr(shell_env->env, true);
    free(shell_env->cwd);
    free(shell_env->old_cwd);
    for (list_t *tmplist = shell_env->commands; tmplist != NULL;
        tmplist = tmplist->next) {
        free(((command_t*)tmplist->data)->path);
        if (((command_t*)tmplist->data)->name != NULL)
            free(((command_t*)tmplist->data)->name);
    }
    list_free(shell_env->commands, true);
    free(shell_env);
    return NULL;
}
