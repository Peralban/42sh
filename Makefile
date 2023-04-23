##
## EPITECH PROJECT, 2022
## Untitled (Workspace)
## File description:
## Makefile
##

SRC	=	src/main.c					\
		src/builtin.c				\
		src/parse_args_setenv.c		\
		src/unsetenv.c				\
		src/setenv.c				\

OBJ	=   $(SRC:.c=.o)

SATAN = -W -Wall -Wextra -Werror -Wshadow

INCLUDE = -I./include

LIB =  -L. -lmy

NCURSES = -lncurses

CFLAGS = $(INCLUDE) $(SATAN) $(LIB) $(NCURSES)

NAME	=	42sh

CC = gcc

.PHONY: all clean fclean re lib include gitignore val delval
.SILENT: all clean fclean re lib include gitignore val delval aa $(NAME) $(OBJ)

all: $(NAME)

$(NAME): $(OBJ)
	@cd lib/my && make -s
	@$(CC) $(OBJ) -o $(NAME) $(CFLAGS)
clean:
	@rm -f $(OBJ)
	@cd lib/my && make clean -s

include:
	@cd lib/my && make minclude -s
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
	@cat $(SRC) | grep -B1 "^{" | grep "(" | grep -v "static" | sed \
		s/"$$"/";"/ >> include/mysh.h
	@echo "" >> include/mysh.h
	@echo "#endif" >> include/mysh.h

aa: include lib re

lib:
	@rm -f libmy.a
	@cd lib/my && make clean -s
	@cd lib/my && make -s

gitignore:
	@echo "vgcore*" >> .gitignore
	@echo $(NAME) >> .gitignore
	@echo "*.o" >> .gitignore
	@echo "libmy.a" >> .gitignore

val:
	@cd lib/my && make val -s
	@gcc $(SRC) -g -o $(NAME) -I./include -L. -lmy
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
	@cd lib/my && make re -s

tests_run: all
	@mv $(NAME) tests/
	@cd tests && ./tester.sh
	@rm -f tests/$(NAME)
