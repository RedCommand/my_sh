/*
** EPITECH PROJECT, 2022
** B-PSU-210-BDX-2-1-minishell2-maxime.senard
** File description:
** redirect
*/

#include "local.h"

static int get_fd_out_1(run_t *run, int i, int finded)
{
    int fd = STDOUT_FILENO;

    if (finded > 1)
        return fd;
    if (run->command[i + 1] == NULL) {
        my_printerr("Missing name for redirect.\n");
        return -1;
    }
    if ((fd = open(run->command[i + 1], O_WRONLY | O_CREAT, 0644)) == -1) {
        my_printerr("%s: Permission denied.\n", run->command[i + 1]);
        return -2;
    }
    run->command = del_in_arr((void **)run->command, i);
    run->command = del_in_arr((void **)run->command, i);
    return fd;
}

static int get_fd_out_2(run_t *run, int i, int finded)
{
    int fd = STDOUT_FILENO;

    if (finded > 1)
        return fd;
    if (run->command[i + 1] == NULL) {
        my_printerr("Missing name for redirect.\n");
        return -1;
    }
    if ((fd = open(run->command[i + 1], O_APPEND | O_WRONLY | O_CREAT, 0644)
        ) == -1) {
        my_printerr("%s: Permission denied.\n", run->command[i + 1]);
        return -2;
    }
    run->command = del_in_arr((void **)run->command, i);
    run->command = del_in_arr((void **)run->command, i);
    return fd;
}

int get_fd_out(run_t *run)
{
    int finded = 0;
    int fd = STDOUT_FILENO;

    for (int i = 0; run->command[i] != NULL && fd >= 0; i++) {
        if (my_strcmp(run->command[i], ">") == 0 ||
            my_strcmp(run->command[i], "&>") == 0) {
            finded++;
            fd = get_fd_out_1(run, i, finded);
        }
        if (my_strcmp(run->command[i], ">>") == 0 ||
            my_strcmp(run->command[i], "&>>") == 0) {
            finded++;
            fd = get_fd_out_2(run, i, finded);
        }
    }
    if (finded <= 1 && fd >= 0)
        return fd;
    if (fd >= 0)
        my_printerr("Ambiguous output redirect.\n");
    return -84;
}
