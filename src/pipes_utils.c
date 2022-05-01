/*
** EPITECH PROJECT, 2022
** B-PSU-210-BDX-2-1-minishell2-maxime.senard
** File description:
** pipes_utils
*/

#include "local.h"

void free_pipe(run_t *runs, int nb_runs, char **pipes)
{
    for (int i = 0; i < nb_runs; i++)
        free_char_arr(runs[i].command, true);
    free(runs);
    free_char_arr(pipes, true);
}
