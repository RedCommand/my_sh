/*
** EPITECH PROJECT, 2022
** B-PSU-101-BDX-1-1-minishell1-maxime.senard
** File description:
** minishell
*/

#include "local.h"

void free_char_arr(char **arr, bool free_base)
{
    if (arr == NULL)
        return;
    for (int i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    if (free_base == true)
        free(arr);
}

void free_commands(char ***commands)
{
    for (int i = 0; commands[i] != NULL; i++)
        free_char_arr(commands[i], true);
}

bool is_str_eq(char *str1, char *str2)
{
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);
    bool is_equal = 1;

    if (len1 != len2 || str1 == NULL || str2 == NULL)
        return false;
    for (int i = 0; i < len1; i++) {
        if (str1[i] != str2[i]) {
            is_equal = 0;
            break;
        }
    }
    return is_equal;
}

int minishell(char **env, bool pt)
{
    int ext_c = 0;
    char *user_input = NULL;
    shell_env_t *shell_env = init_shell_env(env);
    char **commands = NULL;

    while (shell_env != NULL) {
        while ((user_input = get_user_input(user_input, &ext_c, shell_env->cwd,
            pt)) != NULL && *user_input == '\0');
        if (user_input == NULL)
            break;
        commands = extract_commands(user_input, shell_env->env);
        if (commands == NULL)
            continue;
        ext_c = run_commands(commands, shell_env);
    }
    free_if_exist(user_input);
    free_shell_env(shell_env);
    return ext_c;
}
