/*
** EPITECH PROJECT, 2021
** B-PSU-100-BDX-1-1-myprintf-maxime.senard
** File description:
** my_printf
*/

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "printf.h"

void my_printf_char_arr(va_list args, char *)
{
    char **arr = (char **)va_arg(args, char*);
    if (arr == NULL)
        return;
    for (int i = 0; arr[i] != NULL; i++) {
        my_putstr(arr[i]);
        write(1, "\n", 1);
    }
}

void my_printf_show_char_arr(va_list args, char *)
{
    char **arr = (char **)va_arg(args, char*);
    if (arr == NULL)
        return;
    for (int i = 0; arr[i] != NULL; i++) {
        my_showstr(arr[i]);
        write(1, "$\n", 2);
    }
}