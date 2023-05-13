##
## EPITECH PROJECT, 2022
## Untitled (Workspace)
## File description:
## Makefile
##

SRC	=	src/main.c										\
		src/get_file_path.c								\
		src/destroy_array.c								\
		\
		src/builtin/builtin.c							\
		src/builtin/clear_screen.c						\
		src/builtin/my_exit.c							\
        src/builtin/my_cd.c								\
		src/builtin/echo.c								\
        src/builtin/echo_special_cases.c				\
		src/builtin/environment/setenv.c				\
		src/builtin/environment/setenv_variable.c		\
		src/builtin/environment/unsetenv.c				\
		src/builtin/environment/set_environment.c		\
		src/builtin/environment/parse_args_setenv.c		\
		src/builtin/environment/set_get_env.c			\
		src/builtin/variable_builtins.c					\
		\
		src/execution/my_exec.c							\
		src/execution/command_error_handling.c			\
		src/execution/my_put_errors.c					\
		src/execution/check_usr_bin.c					\
		\
		src/ncurse/my_getline_ncurses.c					\
		src/ncurse/my_str_to_array_max_size.c			\
		src/ncurse/write_in_term.c						\
		src/ncurse/my_put.c								\
		src/ncurse/set_get_term_name.c					\
		src/ncurse/start_ncurses.c						\
		src/ncurse/line_edition/move_in_history.c		\
		src/ncurse/is_ncurses.c							\
		src/ncurse/get_string.c							\
		\
		src/parser/parser.c								\
		src/parser/parsing_error.c						\
		src/parser/parsing_error_pipe.c					\
		src/parser/parsing_error_redir.c				\
		src/parser/get_token.c							\
		src/parser/token_dup.c							\
		src/parser/pipe_gestion.c						\
		src/parser/redir_gestion.c						\
		src/parser/get_quote.c							\
		\
		src/prompt/my_getenv.c							\
		src/prompt/print_prompt.c						\
		src/prompt/my_getpwd.c							\
		src/prompt/var_are_init.c						\
		\
		src/history/history.c				            \
		src/history/get_history_array.c					\
		\
		src/redirection/redirections.c					\
		src/redirection/double_left_redirection.c		\
		\
		src/variables/variables.c						\
		src/variables/variables_getters.c				\
		src/variables/variables_special_cases.c			\
		src/variables/local_variables.c					\
		\
		src/sublime/cmd_in_sublime.c					\

TEST_SRC = tests/test_my_sh.c

OBJ	=   $(SRC:.c=.o)

SATAN = -W -Wall -Wextra -Wshadow

INCLUDE = -I./include

LIB =  -L. -lmy

NCURSES = -lncurses

CFLAGS = $(INCLUDE) $(SATAN) $(LIB) $(NCURSES)

NAME	=	42sh

FOLDER = ""

CURRRENT_FOLDER = ""

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
	@echo "#ifndef __"mysh"_H" >> include/mysh.h
	@echo "    #define __"mysh"_H" >> include/mysh.h
	@echo "" >> include/mysh.h
	@echo "    #include <stdbool.h>" >> include/mysh.h
	@echo "    #include <stddef.h>" >> include/mysh.h
	@echo "    #include <unistd.h>" >> include/mysh.h
	@echo "    #include <stdio.h>" >> include/mysh.h
	@echo "    #include \"parser.h\"" >> include/mysh.h
	@echo "" >> include/mysh.h
	@echo "typedef struct token_s token_t;" >> include/mysh.h
	@echo "typedef struct pipe_s pipe_t;" >> include/mysh.h
	for file in $(SRC); do \
		FOLDER=`echo "$${file}" | rev | cut -d '/' -f2 | rev`; \
		if [ "$${FOLDER}" != "$${CURRENT_FOLDER}" ]; then \
			CURRENT_FOLDER="$${FOLDER}"; \
			echo "" >> include/mysh.h; \
			echo "/* Functions from "$${FOLDER}" */" >> include/mysh.h; \
		fi; \
		cat "$${file}" | grep -B1 "^{" | grep "(" | grep -v "static" | sed \
		s/"$$"/";"/ >> include/mysh.h; \
	done
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
