/*
** EPITECH PROJECT, 2022
** B-PSU-210-BDX-2-1-minishell2-maxime.senard
** File description:
** variables
*/

#include "local.h"

static int get_var_size(char *var_start)
{
    int size = 1;

    for (; var_start[size] != '\0' && is_in_str(
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890éèÉÈçÇ_",
        var_start[size]) == 1; size++);
    return size - 1;
}

static char *replace_with_var(char *command, int i, int v_size, char *var)
{
    char *new_command = NULL;
    int new_size = 0;
    int var_size = 0;

    if (command == NULL || var == NULL)
        return NULL;
    var_size = my_strlen(var);
    new_size = (my_strlen(command) - v_size + var_size);
    if ((new_command = malloc(sizeof(char) * (new_size + 1))) == NULL)
        return NULL;
    new_command = my_strncpy(new_command, command, i);
    for (int j = 0; j < var_size; j++)
        new_command[j + i] = var[j];
    for (int j = i + var_size; j < new_size; j++)
        new_command[j] = command[(j - var_size) + v_size + 1];
    new_command[new_size] = '\0';
    free(command);
    return new_command;
}

char *parse_variables(char *command, char **env)
{
    int v_size = 0;
    char *var = NULL;
    char *tmp = NULL;

    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] != '$')
            continue;
        v_size = get_var_size(&command[i]);
        tmp = my_strndup(&command[i + 1], v_size);
        if ((var = get_env_var(env, tmp)) == NULL)
            return NULL;
        free(tmp);
        command = replace_with_var(command, i, v_size, var);
    }
    return command;
}
