/*
** EPITECH PROJECT, 2022
** B-PSU-210-BDX-2-1-minishell2-maxime.senard
** File description:
** run_std
*/

#include "local.h"

int set_stds(int fd_in, int fd_out, int fd_err)
{
    if (fd_in != STDIN_FILENO) {
        if (dup2(fd_in, STDIN_FILENO) == -1)
            return -1;
        close(fd_in);
    }
    if (fd_out != STDOUT_FILENO) {
        if (dup2(fd_out, STDOUT_FILENO) == -1)
            return -2;
        close(fd_out);
    }
    if (fd_err != STDERR_FILENO) {
        if (dup2(fd_err, STDERR_FILENO) == -1)
            return -3;
        close(fd_err);
    }
    return 0;
}

void close_stds(int fd_in, int fd_out, int fd_err)
{
    if (fd_in != STDIN_FILENO)
        close(fd_in);
    if (fd_out != STDOUT_FILENO)
        close(fd_out);
    if (fd_err != STDERR_FILENO)
        close(fd_err);
}

void put_in_std(int fd_in, run_t *run)
{
    if (run->std_in == NULL)
        return;
    write(run->std_in_fd, run->std_in, my_strlen(run->std_in) + 1);
    free(run->std_in);
    close(run->std_in_fd);
    close(fd_in);
}

int exec_p(run_t *run, int fd_in, int fd_out, int fd_err)
{
    pid_t pid = fork();

    if (run == NULL || run->shell_env->env == NULL || run->command == NULL ||
        run->exit_code == NULL || run->command_path == NULL)
        return -84;
    signals_handler();
    if (pid == 0) {
        if (set_stds(fd_in, fd_out, fd_err) < 0)
            return -84;
        if (execve(run->command_path, run->command, run->shell_env->env) < 0)
            command_error_message(run->command_path, run->command[0]);
        exit(84);
    } else {
        put_in_std(fd_in, run);
        close_stds(fd_in, fd_out, fd_err);
        return pid;
    }
    return 0;
}
