# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbonnefo <sbonnefo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/10 18:28:41 by sbonnefo          #+#    #+#              #
#    Updated: 2017/06/04 02:47:16 by sbonnefo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC_PATH = src
OBJ_PATH = obj
LIB_PATH = src/libft

SRC =	$(addprefix $(SRC_PATH)/, main.c \
		ft_get_opt.c \
		ft_args_to_direct_lsts.c \
		ft_get_dircontent.c \
		ft_tool_for_ldisplay.c \
		ft_display_long.c \
		ft_display_dircontent.c \
		ft_display_tree.c \
		ft_display_argfiles.c \
		time_tools.c \
		tool_for_recurs.c \
		ft_path_tools.c \
		ft_errors.c \
		stock_wgdir.c \
		free_tab.c)

OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

INCLUDE = src/include src/libft

LIB = $(LIB_PATH)/libft.a

FLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	@gcc $(FLAGS) -o $(NAME) $(LIB) $(OBJ)
	@echo "$(NAME) \033[30;42mmade\033[0m"

$(LIB):
	@make -C $(LIB_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCLUDES)
	@gcc $(FLAGS) -o $@ -c $< $(addprefix -I , $(INCLUDES))

debug:
	@gcc -g $(FLAGS) -o $(NAME) $(LIB) $(OBJ)

clean:
	@rm -Rf $(OBJ)
	@make clean -C $(LIB_PATH)

fclean: clean
	@rm -Rf $(NAME)
	@make fclean -C $(LIB_PATH)
	@echo "$(NAME) \t\033[30;42m Delete\033[0m\033[0m (make $@ done for $(NAME))"

re: fclean all
