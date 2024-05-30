# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 09:55:06 by mevonuk           #+#    #+#              #
#    Updated: 2024/05/29 14:25:20 by trysinsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		cub3d

# Compiler
CC		= cc
CFLAGS	= -Werror -Wextra -Wall

# Minilibx
MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC			=	-I ./includes/\
				-I ./libft/\
				-I ./minilibx-linux/

# Sources
SRC_PATH	=	src/
MAP_CHECKING	=	$(addprefix map_checking/, extention_check.c \
					parse_map_1.c parse_map_2.c map_validation_1.c \
					map_validation_2.c)
ERROR_MANAGING	=	$(addprefix error_managing/, quit.c)
WINDOW_UTILS	=	$(addprefix window_utils/, utils.c color.c move1.c move2.c \
					rotation.c mouse_controls.c )
RAYCASTING		=	$(addprefix raycasting/, raycast.c raycasting_utils.c rendering.c )
SRC 			=	cub3D.c clean.c init.c toggle_map.c\
					$(MAP_CHECKING) \
					$(ERROR_MANAGING) \
					$(WINDOW_UTILS) \
					$(RAYCASTING) \

SRCS		= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(MLX):
	@echo "Making MiniLibX..."
	@make -sC $(MLX_PATH)

$(LIBFT):
	@echo "Making libft..."
	@make -sC $(LIBFT_PATH)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@echo "Compiling cub3d..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBFT) $(INC) -lXext -lX11 -lm
	@echo "cub3d ready."

clean:
	clear
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_PATH)
	@make clean -C $(MLX_PATH)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@echo "Removing executable..."
	@rm -f $(NAME)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: fclean all

.PHONY: all re clean fclean
