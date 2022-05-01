/*
** EPITECH PROJECT, 2022
** B-PSU-101-BDX-1-1-minishell1-maxime.senard
** File description:
** env_command
*/

#include "local.h"

int env_command(char **user_input_arr __attribute__ ((unused)),
shell_env_t *shell_env)
{
    if (shell_env == NULL || shell_env->env == NULL) {
        write(2, "No environment variables.\n", 26);
        return 84;
    }
    for (int i = 0; shell_env->env[i] != NULL; i++) {
        my_putstr(shell_env->env[i]);
        my_putchar('\n');
    }
    return 0;
}
