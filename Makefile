# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmustach <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 21:13:35 by nmustach          #+#    #+#              #
#    Updated: 2020/01/21 19:35:34 by nmustach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = bonus.c dec_to_base.c f_to_str.c f_to_str2.c \
ft_itoa_long.c ft_itoa_unsigned_long.c ft_printf.c \
is_flag.c output_string.c output_string_xof.c parse_format_string.c \
write_arg_with_flags_d_i.c write_arg_with_flags_d_i_add.c write_arg_with_flags_h_o.c \
write_arg_with_flags_s.c
  
BIN = $(SRC:.c=.o)  

LIBFUNC = ft_toupper.o ft_strdup.o ft_isdigit.o ft_strlen.o ft_strchr.o

all: $(NAME)


$(NAME): $(BIN)
		@echo 'Making libftprintf.a'
		@make -s -C ./libft
		@cp ./libft/ft_toupper.o \
		./libft/ft_strdup.o ./libft/ft_isdigit.o \
		 ./libft/ft_strlen.o ./libft/ft_strchr.o ./ 
		@gcc -c $(SRC) -Wall -Wextra -Werror 
		@ar rc $(NAME) $(BIN) $(LIBFUNC)
		@echo 'DONE'

clean:
		@echo 'Cleaning .o files...'
		@make clean -s -C ./libft
		@rm -f $(BIN) $(LIBFUNC)
		@echo 'DONE'

fclean: clean
		@echo 'Cleaning .o and .a files...'
		@make fclean -s -C ./libft
		@rm -f $(NAME)
		@echo 'DONE'
	
re: fclean all