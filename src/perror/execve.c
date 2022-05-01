/*
** EPITECH PROJECT, 2022
** B-PSU-210-BDX-2-1-minishell2-maxime.senard
** File description:
** execve
*/

#include "local.h"

void command_error_message_4(char *command_path, char *command_name)
{
    switch (errno) {
        case EMFILE:
            my_printerr("%s: Too many files descriptors.\n", command_name);
            break;
        case ENOMEM:
            my_printerr("%s: Not enough memory.\n", command_name);
            break;
        case ENOTDIR:
            my_printerr("%s: Wrong path.\n", command_name);
            break;
        case EPERM:
            my_printerr("%s: Super user privileges requied.\n", command_name);
            break;
        case ETXTBSY:
            my_printerr("%s: File is busy.\n", command_path);
            break;
        default:
            my_printerr("%s: Unknow error.\n", command_name);
            break;
    }
}

void command_error_message_3(char *command_path, char *command_name)
{
    switch (errno) {
        case ELOOP:
            my_printerr("%s: Syslink loop when resolving path.\n",
            command_name);
            break;
        case ENOEXEC:
            my_printerr("%s: Exec format error. Wrong Architecture.\n",
            command_path);
            break;
        case ENAMETOOLONG:
            my_printerr("%s: Filepath too long.\n", command_name);
            break;
        case ENOENT:
            my_printerr("%s: Command not found.\n", command_name);
            break;
        default:
            command_error_message_4(command_path, command_name);
            break;
    }
}

void command_error_message_2(char *command_path, char *command_name)
{
    switch (errno) {
        case EINVAL:
            my_printerr("%s: Executable had more than one PT_INTERP segment.\n",
            command_name);
            break;
        case EIO:
            my_printerr("%s: An I/O error occurred.\n", command_name);
            break;
        case EISDIR:
            my_printerr("%s: An ELF interpreter was a directory.\n",
            command_name);
            break;
        case ELIBBAD:
            my_printerr("%s: An ELF interpreter was not in a know format.\n",
            command_name);
            break;
        default:
            command_error_message_3(command_path, command_name);
            break;
    }
}

void command_error_message(char *command_path, char *command_name)
{
    switch (errno) {
        case E2BIG:
            my_printerr("%s: Args or env too long.\n", command_name);
            break;
        case EACCES:
            my_printerr("%s: Permission denied.\n", command_name);
            break;
        case EAGAIN:
            my_printerr("%s: Wrong UID.\n", command_name);
            break;
        case EFAULT:
            my_printerr("%s: Invalid address.\n", command_name);
            break;
        default:
            command_error_message_2(command_path, command_name);
            break;
    }
}
