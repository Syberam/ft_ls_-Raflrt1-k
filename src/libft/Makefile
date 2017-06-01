# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/10 18:28:41 by sbonnefo          #+#    #+#              #
#    Updated: 2017/05/30 23:09:16 by sbonnefo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_itoa.c \
		ft_putendl.c \
		ft_strcmp.c \
		ft_strmap.c \
		ft_strsplit.c \
		ft_putendl_fd.c \
		ft_strcpy.c \
		ft_strmapi.c \
		ft_strstr.c \
		ft_atoi.c \
		ft_putnbr.c \
		ft_strdel.c \
		ft_strncat.c \
		ft_strsub.c \
		ft_bzero.c \
		ft_putnbr_fd.c \
		ft_strdup.c \
		ft_strnchr.c \
		ft_strtrim.c \
		ft_ilen.c \
		ft_putstr.c \
		ft_strequ.c \
		ft_strncmp.c \
		ft_putstr_fd.c \
		ft_striter.c \
		ft_strncpy.c \
		ft_putstri.c \
		ft_striteri.c \
		ft_strnequ.c \
		ft_power.c \
		ft_strcat.c \
		ft_strjoin.c \
		ft_ext_strjoin_free.c \
		ft_strnew.c \
		ft_putchar.c \
		ft_strchr.c \
		ft_strlcat.c \
		ft_strnstr.c \
		ft_memalloc.c \
		ft_putchar_fd.c \
		ft_strclr.c \
		ft_strlen.c \
		ft_strrchr.c \
		ft_strrccpy.c \
		ft_memset.c \
		ft_strccpy.c \
		ft_atoi_base.c

OBJ = $(SRC:%.c=%.o) 

FLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "$(NAME) \033[30;42mmade\033[0m"

$(OBJ):
	@gcc $(FLAGS) -c $(SRC) libft.h

clean:
	@rm -Rf $(OBJ)

fclean: clean
	@rm -Rf $(NAME) libft.h.gch
	@echo "$(NAME) \t\033[30;42m Delete\033[0m\033[0m (make $@ done for $(NAME))"
re: fclean all
	
