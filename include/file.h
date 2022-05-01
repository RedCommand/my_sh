/*
** EPITECH PROJECT, 2022
** B-PSU-101-BDX-1-1-minishell1-maxime.senard
** File description:
** file
*/

#ifndef FILE_H
    #define FILE_H

typedef struct dir_s {
    char **filenames;
    int nb_files;
    unsigned char *types;
} dir_t;

#endif
