/*
** EPITECH PROJECT, 2021
** B-PSU-100-BDX-1-1-myprintf-maxime.senard
** File description:
** my_printf
*/

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "printerr.h"

void my_printerr_char_arr(va_list args, char *)
{
    char **arr = (char **)va_arg(args, char*);
    if (arr == NULL)
        return;
    for (int i = 0; arr[i] != NULL; i++) {
        my_putstr_err(arr[i]);
        write(2, "\n", 1);
    }
}
