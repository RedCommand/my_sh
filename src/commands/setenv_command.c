/*
** EPITECH PROJECT, 2022
** B-PSU-101-BDX-1-1-minishell1-maxime.senard
** File description:
** setenv_command
*/

#include "local.h"

char *gen_env_var(char *name, char *value)
{
    char *env_var = NULL;

    if ((env_var = my_strcat(name, "=")) == NULL)
        return NULL;
    if (value == NULL)
        return env_var;
    if ((env_var = my_strcat(env_var, value)) == NULL)
        return NULL;
    return env_var;
}

int set_env_command_proccess(char *name, char *value, shell_env_t *shell_env)
{
    char *env_var = NULL;

    if ((env_var = gen_env_var(name, value)) == NULL)
        return 84;
    dell_env_var(name, shell_env->env);
    if  (shell_env->env == NULL || shell_env->env[0] == NULL) {
        if (shell_env->env == NULL)
            shell_env->env = malloc(sizeof(char*) * 2);
        if (shell_env->env == NULL)
            return 84;
        if ((shell_env->env[1] = my_strdup(env_var)) == NULL)
            return 84;
        return 0;
    }
    if ((shell_env->env = add_str_to_tabl(shell_env->env, env_var)) == NULL)
        return 84;
    return 0;
}

int check_env_name(char *name)
{
    if (name == NULL)
        return 0;
    if (str_with_str(name, "abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890éèÉÈçÇ_") == 1)
        return 1;
    write(2, "setenv: Variable name must contain alphanumeric characters.\n",
    60);
    return 0;
}

int setenv_command(char **user_input_arr, shell_env_t *shell_env)
{
    int len = 0;

    if (shell_env == NULL || user_input_arr == NULL)
        return 84;
    len = my_char_tabl_len(user_input_arr) - 1;
    if (len < 2)
        return env_command(user_input_arr, shell_env);
    if (len == 2) {
        if (check_env_name(user_input_arr[1]) != 1)
            return 84;
        return set_env_command_proccess(user_input_arr[1], NULL, shell_env);
    }
    if (len == 3) {
        if (check_env_name(user_input_arr[1]) != 1)
            return 84;
        return set_env_command_proccess(user_input_arr[1], user_input_arr[2],
        shell_env);
    }
    write(2, "setenv: Too many arguments.\n", 28);
    return 84;
}
