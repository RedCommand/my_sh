/*
** EPITECH PROJECT, 2022
** B-PSU-101-BDX-1-1-minishell1-maxime.senard
** File description:
** main
*/

#include "local.h"

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
char **env)
{
    return minishell(env, (bool)isatty(0));
}
