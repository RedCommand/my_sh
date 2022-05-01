/*
** EPITECH PROJECT, 2022
** B-PSU-210-BDX-2-1-minishell2-maxime.senard
** File description:
** pipe_proccess
*/

#include "local.h"

void free_pipe(run_t *runs, int nb_runs, char **pipes);

int **get_pipe_fds(int nb_runs)
{
    int **fds = malloc(sizeof(int *) * (nb_runs - 1));

    for (int i = nb_runs - 2; i >= 0; i--) {
        if ((fds[i] = malloc(sizeof(int) * 2)) == NULL)
            return NULL;
        if (pipe(fds[i]) < 0) {
            my_printerr("FATAL ERROR: fail to create pipe.\n");
            return NULL;
        }
    }
    return fds;
}

void wait_pipe_proccess(int pids[], run_t *runs, int nb_runs, int **fds)
{
    for (int i = 0; i < nb_runs; i++) {
        waitpid(pids[i], runs[i].exit_code, 0);
        *(runs[i].exit_code) = WEXITSTATUS(*(runs[i].exit_code));
        if (i != nb_runs - 1)
            kill(pids[i + 1], SIGPIPE);
    }
    for (int i = 0; i < nb_runs - 1; i++)
        free(fds[i]);
    free(fds);
}

int run_pipe(run_t *runs, int nb_runs)
{
    int pids[nb_runs];
    int **fds = get_pipe_fds(nb_runs);
    int b_fd[3] = {0, 0, 0};

    if (runs == NULL || fds == NULL)
        return 84;
    for (int i = nb_runs - 1; i >= 0 ; i--) {
        if ((b_fd[0] = (i == 0) ? get_fd_in(&runs[i]) : fds[i - 1][0]) < 0)
            return 84;
        if ((b_fd[1] = (i == nb_runs - 1) ? get_fd_out(&runs[i]) : fds[i][1])
            < 0)
            return 84;
        if ((b_fd[2] = get_fd_err(&runs[i])) < 0)
            return 84;
        if ((pids[i] = exec_p(&runs[i], b_fd[0], b_fd[1], b_fd[2])) == -84)
            return 84;
        if (pids[i] == 0)
            exit(0);
    }
    wait_pipe_proccess(pids, runs, nb_runs, fds);
    return 0;
}

static int get_pipe_command(char *pipe, shell_env_t *shell_env, int *exit_code,
run_t *run)
{
    char **command = NULL;
    char *command_path = NULL;

    if ((command = str_to_array_s(pipe, " \t\n!!\"!!!!\'!!")) == NULL)
        return -1;
    if ((command_path = get_user_command_line(command, shell_env,
        exit_code)) == NULL) {
        free_char_arr(command, true);
        return -2;
    }
    run->shell_env = shell_env;
    run->command_path = command_path;
    run->command = command;
    run->exit_code = exit_code;
    run->std_in = NULL;
    return 0;
}

int run_pipes(char *command, shell_env_t *shell_env)
{
    char **pipes = NULL;
    run_t *runs = NULL;
    int status = 0;
    int exit_code = 0;
    int nb_runs = 0;

    pipes = str_to_array(command, "|");
    if (pipes == NULL || pipes[0] == NULL || pipes[1] == NULL)
        return 84;
    nb_runs = my_tabl_len((void **)pipes);
    if ((runs = malloc(sizeof(run_t) * nb_runs)) == NULL)
        return 84;
    for (int i = 0; i < nb_runs; i++) {
        if (get_pipe_command(pipes[i], shell_env, &exit_code, &runs[i]) < 0)
            return 84;
    }
    status = run_pipe(runs, nb_runs);
    free_pipe(runs, nb_runs, pipes);
    return status;
}
