##
## EPITECH PROJECT, 2022
## epitech
## File description:
## Makefile
##

SRC =	delete_node_in_array.c	\
		my_arraylen.c			\
		print_array.c			\
		my_start_with.c			\
		my_str_to_word_array.c	\
		my_putstr.c				\
		char_isnum.c			\
		my_puterror.c			\
		my_arraydup.c			\
		char_isalpha.c			\
		str_isalphanum.c		\

OBJ	=   $(SRC:.c=.o)

SATAN = -W -Wall -Wextra -Werror -Wshadow

INCLUDE = -I../../include

CFLAGS = $(INCLUDE) $(SATAN)

NAME = my

LIB_NAME = libmy.a

all: $(LIB_NAME)

$(LIB_NAME):	$(OBJ)
	@ar rc $(LIB_NAME) $(OBJ)
	@mv libmy.a ../../

minclude:
	@mkdir -p ../../include
	@echo "/*" > ../../include/$(NAME).h
	@echo "** EPITECH PROJECT, `date +"%Y"`" >> ../../include/$(NAME).h
	@echo "** $(NAME)" >> ../../include/$(NAME).h
	@echo "** File description:" >> ../../include/$(NAME).h
	@echo "** The $(NAME)'s include file" >> ../../include/$(NAME).h
	@echo "*/" >> ../../include/$(NAME).h
	@echo "" >> ../../include/$(NAME).h
	@echo "#include <stdbool.h>" >> ../../include/$(NAME).h
	@echo "" >> ../../include/$(NAME).h
	@echo "#ifndef __"$(NAME)"_H" >> ../../include/$(NAME).h
	@echo "    #define __"$(NAME)"_H" >> ../../include/$(NAME).h
	@echo "" >> ../../include/$(NAME).h
	@cat $(SRC) | grep -B1 "^{" | grep "(" | grep -v "static" | sed \
		s/"$$"/";"/ >> ../../include/$(NAME).h
	@echo "" >> ../../include/$(NAME).h
	@echo "#endif" >> ../../include/$(NAME).h

clean:
	@rm -f $(OBJ)

val:
	@ar rc $(LIB_NAME) $(OBJ)
	@mv libmy.a ../../

fclean:	clean
	@rm -f $(LIB_NAME)
	@rm -f libmy.a

re:	fclean all
	@rm -f $(OBJ)
