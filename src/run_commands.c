/*
** EPITECH PROJECT, 2022
** B-PSU-210-BDX-2-1-minishell2-maxime.senard
** File description:
** run commands
*/

#include "local.h"

int run_command(char **command, shell_env_t *shell_env)
{
    int exit_code = 84;
    char *command_path = get_user_command_line(command, shell_env, &exit_code);
    run_t run = {.shell_env = shell_env, .command_path = command_path,
    .command = command, .exit_code = &exit_code, .std_in = NULL};
    int stds[3] = {get_fd_in(&run), get_fd_out(&run), get_fd_err(&run)};

    if (command_path == NULL || stds[0] < 0 || stds[1] < 0 || stds[2] < 0)
        return exit_code;
    run_proccess(&run, stds);
    return *run.exit_code;
}

int run_commands(char **commands, shell_env_t *shell_env)
{
    int status = 0;
    char **command = NULL;

    for (int i = 0; commands[i] != NULL; i++) {
        if (is_in_str(commands[i], '|')) {
            run_pipes(commands[i], shell_env);
            continue;
        }
        command = str_to_array_s(commands[i], " \t\n!!\"!!!!\'!!");
        if (command == NULL)
            return 84;
        status = run_command(command, shell_env);
        free_char_arr(command, true);
    }
    free_char_arr(commands, true);
    return status;
}
