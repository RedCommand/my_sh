/*
** EPITECH PROJECT, 2022
** B-PSU-101-BDX-1-1-minishell1-maxime.senard
** File description:
** run_command
*/

#include "local.h"
#include <string.h>

int get_exit_status(int *exit_code)
{
    if (WIFSIGNALED(*exit_code) == false)
        return WEXITSTATUS(*exit_code);
    my_printf("%s.\n", strsignal(WTERMSIG(*exit_code)));
    if (WCOREDUMP(*exit_code) == true)
        my_printerr("Core dumped. UwU\n");
    return WTERMSIG(*exit_code);
}

void sigint_handler(int signal __attribute__((unused)))
{
    write(1, "\n", 1);
}

void signals_handler(void)
{
    signal(SIGINT, &sigint_handler);
}

int run_proccess(run_t *run, int stds[3])
{
    int res = 0;

    res = exec_p(run, stds[0], stds[1], stds[2]);
    switch (res) {
        case 0:
            exit(0);
        case -84:
            return -84;
        default:
            waitpid(res, run->exit_code, 0);
            *run->exit_code = get_exit_status(run->exit_code);
            break;
    }
    return 0;
}
