/*
** EPITECH PROJECT, 2022
** B-PSU-101-BDX-1-1-minishell1-maxime.senard
** File description:
** get_files
*/

#include <sys/types.h>
#include <dirent.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "local.h"

dir_t *init_dir_arr(void)
{
    dir_t *dir_arr;

    dir_arr = malloc(sizeof(dir_t));
    if (dir_arr == NULL)
        return NULL;
    dir_arr->nb_files = 0;
    dir_arr->types = malloc(sizeof(char) * 1);
    dir_arr->types[0] = '\0';
    dir_arr->filenames = malloc(sizeof(char*) * 1);
    dir_arr->filenames[0] = NULL;
    return dir_arr;
}

dir_t *get_file_in_dir(char *path)
{
    DIR *dirs = opendir(path);
    struct dirent *dir;
    dir_t *dir_arr = init_dir_arr();

    if (dirs == NULL || dir_arr == NULL) {
        return NULL;
    }
    while ((dir = readdir(dirs)) != NULL) {
        dir_arr->filenames = add_str_to_tabl(dir_arr->filenames, dir->d_name);
        dir_arr->nb_files++;
    }
    closedir(dirs);
    free(dir);
    return dir_arr;
}

static char *get_commands_path(char *path)
{
    int len = 0;

    if (path == NULL)
        return NULL;
    len = my_strlen(path) - 1;
    if (len < 0)
        return NULL;
    if (path[len] == '/')
        return my_strdup(path);
    return my_strcat(path, "/");
}

static list_t *get_command(list_t *commands, char *path)
{
    command_t *command = NULL;
    DIR *dirs = opendir(path);
    struct dirent *dir;
    char *fullpath = NULL;

    if (commands == NULL || path == NULL || dirs == NULL ||
        (fullpath = get_commands_path(path)) == NULL)
        return NULL;
    while ((dir = readdir(dirs)) != NULL) {
        if (dir->d_name[0] == '.')
            continue;
        if ((command = malloc(sizeof(command_t))) == NULL)
            return NULL;
        command->name = my_strdup(dir->d_name);
        command->path = my_strcat(fullpath, command->name);
        commands = list_append(commands, (void*)command);
    }
    free(fullpath);
    closedir(dirs);
    return commands;
}

list_t *get_avalable_command(char **paths)
{
    int nb_paths = my_char_tabl_len(paths);
    list_t *commands = list_init(NULL);
    list_t *tmpcommands = commands;
    int failed = 1;

    if (nb_paths < 1 || commands == NULL)
        return NULL;
    for (int i = 0; i < nb_paths - 1; i++) {
        tmpcommands = get_command(commands, paths[i]);
        if (tmpcommands != NULL) {
            commands = tmpcommands;
            failed = 0;
        } else
            my_printerr("error: unable to read path: %s\n", paths[i]);
    }
    if (failed == 1)
        return NULL;
    commands = list_del(commands, 0, false);
    return commands;
}
