/*
** EPITECH PROJECT, 2022
** B-PSU-101-BDX-1-1-minishell1-maxime.senard
** File description:
** globals
*/

#include <stdbool.h>

int *exit_code_ptr(void)
{
    static int exit_code;

    return &exit_code;
}

bool *pt_ptr(void)
{
    static bool pt;

    return &pt;
}

char **path_ptr(void)
{
    static char *path;

    return &path;
}

void set_globals(int exit_code, bool pt, char *path)
{
    *exit_code_ptr() = exit_code;
    *pt_ptr() = pt;
    *path_ptr() = path;
}
