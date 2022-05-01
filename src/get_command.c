/*
** EPITECH PROJECT, 2022
** B-PSU-101-BDX-1-1-minishell1-maxime.senard
** File description:
** get_command
*/

#include "local.h"

static const char *custom_commands[] = {
    "cd",
    "env",
    "setenv",
    "unsetenv"
};
static const int len_custom_commands = 4;
static const int (*custom_commands_func[])(char **, shell_env_t *) = {
    &cd_command,
    &env_command,
    &setenv_command,
    &unsetenv_command
};

char *find_command_path(char *command, list_t *commands)
{
    list_t *tmpcommands = commands;

    if (command == NULL || commands == NULL)
        return NULL;
    while (tmpcommands != NULL) {
        if (is_str_eq(command, ((command_t*)tmpcommands->data)->name) == true)
            return ((command_t*)tmpcommands->data)->path;
        tmpcommands = tmpcommands->next;
    }
    return NULL;
}

char *get_user_command(char *user_command, shell_env_t *shell_env)
{
    if (user_command[0] == '/' ||
        (user_command[0] == '.' && user_command[1] == '/'))
        return user_command;
    return find_command_path(user_command, shell_env->commands);
}

char *get_user_command_line(char **user_input_arr, shell_env_t *shell_env,
int *exit_code)
{
    char *command = NULL;

    for (int i = 0; i < len_custom_commands; i++) {
        if (my_strcmp(user_input_arr[0], custom_commands[i]) == 0) {
            *exit_code = custom_commands_func[i](user_input_arr, shell_env);
            return NULL;
        }
    }
    command = get_user_command(user_input_arr[0], shell_env);
    if (command == NULL)
        return user_input_arr[0];
    return command;
}

char **clear_useless_commands(char **user_commands)
{
    int size = my_char_tabl_len(user_commands) - 1;
    char **arr = malloc(sizeof(char *) * (size + 1));
    int j = 0;

    if (arr == NULL)
        return NULL;
    for (int i = 0; i < size; i++)
        arr[i] = NULL;
    for (int i = 0; i < size; i++) {
        if (str_with_str(user_commands[i], " \t\n") == 1) {
            free(user_commands[i]);
            continue;
        }
        arr[j] = user_commands[i];
        j++;
    }
    free(user_commands);
    arr[size] = NULL;
    return arr;
}

char **extract_commands(char *user_input, char **env)
{
    char **commands = NULL;

    if (user_input == NULL)
        return NULL;
    commands = str_to_array_s(user_input, ";``&&``\0");
    if (commands == NULL)
        return NULL;
    if ((commands = clear_useless_commands(commands)) == NULL)
        return NULL;
    for (int i = 0; commands[i] != NULL; i++) {
        if ((commands[i] = parse_variables(commands[i], env)) == NULL)
            break;
    }
    return commands;
}
