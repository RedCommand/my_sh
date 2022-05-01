/*
** EPITECH PROJECT, 2022
** B-PSU-101-BDX-1-1-minishell1-maxime.senard
** File description:
** unsetenv_command
*/

#include "local.h"

int dell_env_var(char *key, char **env)
{
    int i = 0;
    char *newkey = my_strcat(key, "=");
    int lenkey = my_strlen(newkey);

    if (get_env_var(env, key) == NULL)
        return 84;
    for (i = 0; env[i] != NULL; i++) {
        if (str_start_with(env[i], newkey, my_strlen(env[i]), lenkey) == 1)
            break;
    }
    if (env[i] != NULL)
        free(env[i]);
    for (; env[i + 1] != NULL; i++)
        env[i] = env[i + 1];
    env[i] = NULL;
    return 0;
}

int unsetenv_command(char **user_input_arr, shell_env_t *shell_env)
{
    int nb_val = 0;

    if (shell_env == NULL || shell_env->env == NULL) {
        write(2, "No environment variables.\n", 26);
        return 84;
    }
    nb_val = my_char_tabl_len(user_input_arr) - 2;
    if (nb_val <= 0) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        return 84;
    }
    for (int i = 0; i < nb_val; i++)
        dell_env_var(user_input_arr[i + 1], shell_env->env);
    return 0;
}
