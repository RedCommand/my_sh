/*
** EPITECH PROJECT, 2022
** B-PSU-210-BDX-2-1-minishell2-maxime.senard
** File description:
** redirect
*/

#include "local.h"

static int get_fd_in_1(run_t *run, int i, int finded)
{
    int fd = STDIN_FILENO;

    if (finded > 1)
        return fd;
    if (run->command[i + 1] == NULL) {
        my_printerr("Missing name for redirect.\n");
        return -1;
    }
    if ((fd = open(run->command[i + 1], O_RDONLY)) == -1) {
        my_printerr("%s: No such file or directory.\n", run->command[i + 1]);
        return -2;
    }
    run->command = del_in_arr((void **)run->command, i);
    run->command = del_in_arr((void **)run->command, i);
    return fd;
}

char *list_to_str(list_t *list)
{
    char *str = NULL;
    int size = 0;
    char *tmp_str = NULL;

    for (list_t *tmp = list; tmp != NULL && tmp->next != NULL; tmp = tmp->next)
        size += my_strlen(((char *)tmp->data));
    if ((str = malloc(sizeof(char) * (size + 2))) == NULL)
        return NULL;
    tmp_str = str;
    for (list_t *tmp = list; tmp != NULL && tmp->next != NULL;
        tmp = tmp->next) {
        tmp_str = my_strcpy(tmp_str, tmp->data);
        tmp_str += my_strlen(tmp->data);
    }
    str[size] = -1;
    str[size + 1] = '\0';
    return str;
}

static int get_fd_in_2_input(run_t *run, int i)
{
    char *exit_str = run->command[i + 1];
    char *str_in = NULL;
    ssize_t line_size = 0;
    list_t *user_std = NULL;

    while (my_strncmp(str_in, exit_str, my_strlen(exit_str)) != 0) {
        write(1, ">", 1);
        free(str_in);
        str_in = NULL;
        if ((line_size = getline(&str_in, (size_t *)&line_size, stdin)) < 0) {
            free(str_in);
            list_free(user_std, true);
            return -1;
        }
        user_std = list_append(user_std, my_strdup(str_in));
    }
    free(str_in);
    run->std_in = list_to_str(user_std);
    list_free(user_std, true);
    return 0;
}

static int get_fd_in_2(run_t *run, int i, int finded)
{
    int fd[2];

    if (finded > 1)
        return STDIN_FILENO;
    if (pipe(fd) < 0)
        return -1;
    if (run->command[i + 1] == NULL) {
        my_printerr("Missing text for redirect.\n");
        return -2;
    }
    if (get_fd_in_2_input(run, i) < 0)
        return -3;
    run->command = del_in_arr((void **)run->command, i);
    run->command = del_in_arr((void **)run->command, i);
    run->std_in_fd = fd[1];
    return fd[0];
}

int get_fd_in(run_t *run)
{
    int finded = 0;
    int fd = STDIN_FILENO;

    for (int i = 0; run->command[i] != NULL && fd >= 0; i++) {
        if (my_strcmp(run->command[i], "<") == 0) {
            finded++;
            fd = get_fd_in_1(run, i, finded);
        }
        if (my_strcmp(run->command[i], "<<") == 0) {
            finded++;
            fd = get_fd_in_2(run, i, finded);
        }
    }
    if (fd < 0)
        return -84;
    if (finded <= 1)
        return fd;
    my_printerr("Ambiguous input redirect.\n");
    return -84;
}
