/*
** EPITECH PROJECT, 2022
** B-PSU-210-BDX-2-1-minishell2-maxime.senard
** File description:
** input
*/

#include "local.h"

void print_prompt(int signal)
{
    char buff[] = "\b\033[K\b\033[K ";
    bool pt = *pt_ptr();
    int exit_code = *exit_code_ptr();
    char *path = *path_ptr();

    if (signal != 1234) {
        write(1, buff, 8);
        write(1, "\n", 1);
    }
    if (pt)
        my_printf("\033[0;31m%d%s\033[0;33m [%s] \033[0;37m$> ", exit_code,
        ((exit_code == 0) ? "\b\033[K\033[0;32m✓" : " ✗"), path);
    return;
}

char *get_user_input(char *user_input, int *ext_c, char *path, bool pt)
{
    ssize_t line_size = 0;

    set_globals(*ext_c, pt, path);
    signal(SIGINT, &print_prompt);
    if (user_input != NULL)
        free(user_input);
    user_input = NULL;
    print_prompt(1234);
    set_globals((*ext_c = 0), pt, path);
    if ((line_size = getline(&user_input, (size_t *)&line_size, stdin)) < 0) {
        write(1, "exit\n", 5);
        free_exit(user_input);
    }
    user_input[line_size - 1] = '\0';
    if (str_start_with(user_input, "exit", my_strlen(user_input), 4) == 1) {
        if (str_with_str(&user_input[4], " -0123456789") == 0)
            return user_input;
        free_exit(user_input);
    }
    return user_input;
}
