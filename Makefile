# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 17:58:59 by ymassiou          #+#    #+#              #
#    Updated: 2025/02/08 23:16:16 by akoutate         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRC = main.c                  \
       parsing/get_next_line.c \
       parsing/libft_utils1.c   \
       parsing/libft_utils2.c    \
       parsing/libft_utils3.c     \
       parsing/libft_utils4.c      \
       parsing/lst_utils.c          \
       parsing/parsing.c             \
       parsing/parsing_utils.c        \
       parsing/parsing_utils1.c        \
       parsing/parsing_utils2.c         \
       parsing/map_parse.c               \
       parsing/rgb_utils1.c               \
       gc/free_utils.c                     \
       gc/gc_utils.c                        \
       map_render/map_casting.c              \
       map_render/player_mouvements.c         \
       ray_casting/ray_casting_utils.c         \
       parsing/map_parse2.c                     \
       ray_casting/ray_casting.c                 \
       put/put.c                                  \
       ray_casting/hor_inter.c                     \
       ray_casting/ver_inter.c                      \
	   sprite_doors_bonus/render_sprite_bonus.c      \
       parsing/map_parse3.c                           \
       parsing/parsing_utils3.c                        \
       parsing/rgb_utils2.c                             \
       map_render/player_mouvements2.c                   \
       parsing/split.c                                    \
       parsing/str_trim.c                                  \
	   map_render/textures.c


CC = cc
INCLUDE = MLX42/MLX42.h cub3d.h
CFLAGS = -Wall -Wextra -Werror -Ofast
MLX_LIB = MLX42/libmlx42.a /Users/$(shell whoami)/.brew/lib/libglfw3.a -framework Cocoa -framework IOKit

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(MLX_LIB) -o $(NAME)
	@echo "Executable linked successfully!"

%.o: %.c $(INCLUDE)
	@($(CC) $(CFLAGS) -c $< -o $@)
	@echo "Compiled $<"

clean:
	@rm -f $(OBJ)
	@echo "Cleaned object files"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned executables"

re: fclean all
