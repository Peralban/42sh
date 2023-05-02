##
## EPITECH PROJECT, 2022
## Untitled (Workspace)
## File description:
## Makefile
##

SRC	=	src/main.c							\
		src/builtin/builtin.c				\
		src/builtin/parse_args_setenv.c		\
		src/builtin/unsetenv.c				\
		src/builtin/setenv.c				\
		src/builtin/my_exit.c				\
		src/prompt/my_getenv.c				\
		src/prompt/print_prompt.c			\
		src/prompt/my_getpwd.c				\
		src/builtin/set_environment.c		\
		src/prompt/var_are_init.c			\
		src/builtin/echo.c					\
		src/builtin/echo_special_cases.c	\
		src/variables.c

TEST_SRC = tests/test_my_sh.c

OBJ	=   $(SRC:.c=.o)

SATAN = -W -Wall -Wextra -Wshadow

INCLUDE = -I./include

LIB =  -L. -lmy

NCURSES = -lncurses

CFLAGS = $(INCLUDE) $(SATAN) $(LIB) $(NCURSES)

NAME	=	42sh

CC = gcc

.PHONY: all clean fclean re lib include gitignore val delval
.SILENT: all clean fclean re lib include gitignore val delval a $(NAME) $(OBJ)

all: $(NAME)

$(NAME): $(OBJ)
	@make -s -C lib/my
	@$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

clean:
	@rm -f $(OBJ)
	@make clean -s -C lib/my

include:
	@make minclude -s -C lib/my
	@mkdir -p include
	@echo "/*" > include/mysh.h
	@echo "** EPITECH PROJECT, `date +"%Y"`" >> include/mysh.h
	@echo "** mysh" >> include/mysh.h
	@echo "** File description:" >> include/mysh.h
	@echo "** The mysh's include file" >> include/mysh.h
	@echo "*/" >> include/mysh.h
	@echo "" >> include/mysh.h
	@echo "#include <stdbool.h>" >> include/mysh.h
	@echo "" >> include/mysh.h
	@echo "#ifndef __"mysh"_H" >> include/mysh.h
	@echo "    #define __"mysh"_H" >> include/mysh.h
	@echo "" >> include/mysh.h
	@cat $(SRC) | grep -B1 "^{" | grep "(" | grep -v "static" | sed \
		s/"$$"/";"/ >> include/mysh.h
	@echo "" >> include/mysh.h
	@echo "#endif" >> include/mysh.h

a: include lib re

lib:
	@rm -f libmy.a
	@make clean -s -C lib/my
	@make -s -C lib/my

gitignore:
	@echo "vgcore*" >> .gitignore
	@echo $(NAME) >> .gitignore
	@echo "*.o" >> .gitignore
	@echo "libmy.a" >> .gitignore

val:
	@make val -s -C lib/my
	@$(CC) $(SRC) -g -o $(NAME) $(CFLAGS)
	@valgrind ./$(NAME)

delval:
	@rm -f vgcore*
	@rm -f a.out
	@rm -f libmy.a

fclean: clean delval
	@rm -f libmy.a
	@rm -f $(NAME)

re:    fclean all
	@rm -f $(OBJ)
	@make re -s -C lib/my

tests_run: all
	@mv $(NAME) tests/
	@cd tests && ./tester.sh
	@rm -f tests/$(NAME)

run_tests:
	@$(CC) -o unit_tests $(TEST_SRC) $(CFLAGS) -L. -lmy --coverage -lcriterion
	./unit_tests
