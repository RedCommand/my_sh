##
## EPITECH PROJECT, 2021
## libmy Makefile
## File description:
## Makefile to build libmy.a
##

override CFLAGS += -fno-builtin -W -Wall -Wextra -Wno-ignored-qualifiers -Llib
override CPPFLAGS += -Iinclude -lmy -llist -lprintf -lprinterr

SRC	=	src/commands/unsetenv_command.c	\
		src/commands/setenv_command.c	\
		src/commands/env_command.c	\
		src/commands/cd_command.c	\
		src/redirect/std_out.c		\
		src/redirect/std_err.c		\
		src/redirect/std_in.c		\
		src/perror/execve.c		\
		src/pipe_proccess.c		\
		src/run_proccess.c		\
		src/run_commands.c		\
		src/get_command.c		\
		src/pipes_utils.c		\
		src/env_utils.c			\
		src/get_files.c			\
		src/minishell.c			\
		src/variables.c			\
		src/globals.c			\
		src/input.c			\
		src/exec.c

OBJ = $(SRC:.c=.o)

TESTSRC = tests/test_make.c

TESTOBJ = $(TESTSRC:.c=.o)

MAINSRC = main.c

MAINOBJ = $(MAINSRC:.c=.o)

NAME = mysh

all: $(NAME)

$(NAME): $(OBJ) $(MAINOBJ)
				make -C lib/my
				make -C lib/printf
				make -C lib/printerr
				make -C lib/list
				gcc -o $(NAME) $(MAINOBJ) $(OBJ) $(CFLAGS) $(CPPFLAGS)

clean:
				rm -f $(OBJ) $(MAINOBJ)
				find . -type f -name '*.gcda' -delete
				find . -type f -name '*.gcno' -delete
				make clean -C lib/my
				make clean -C lib/printf
				make clean -C lib/printerr
				make clean -C lib/list

fclean: clean
				rm -f $(NAME)
				make fclean -C lib/my
				make fclean -C lib/printf
				make fclean -C lib/printerr
				make fclean -C lib/list

re: fclean all

tests_run:	CFLAGS += -lcriterion --coverage
tests_run: re $(TESTOBJ)
				gcc -o unit_tests $(TESTOBJ) $(SRC) $(CFLAGS) $(CPPFLAGS)
				./unit_tests

cover:
				gcovr --exclude tests
				gcovr --exclude tests --branches
				rm -f unit_tests*

debug: CFLAGS += -g
debug: re
