/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:08:31 by akoutate          #+#    #+#             */
/*   Updated: 2025/02/07 21:00:44 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sprite(t_cub *cube, bool first, bool is_it_moving)
{
	static int	i;
	static int	frame_skip;
	int			img_width;
	int			img_height;

	if (!is_it_moving)
		i = 0;
	frame_skip++;
	if (!first && frame_skip < 3)
		return ;
	frame_skip = 0;
	if (cube->sprites.img)
		mlx_delete_image(cube->mlx_window, cube->sprites.img);
	img_width = cube->sprites.textures[i]->width;
	img_height = cube->sprites.textures[i]->height;
	cube->sprites.img = mlx_texture_to_image(cube->mlx_window,
			cube->sprites.textures[i]);
	mlx_image_to_window(cube->mlx_window, cube->sprites.img,
		(WIN_WIDTH - img_width) / 2, W_HEIGHT - img_height);
	i++;
	if (i == 13)
		i = 1;
}

void	set_the_sprite_protected(t_cub *cube, int current, char *str)
{
	int		i;

	i = 0;
	cube->sprites.textures[current] = mlx_load_png(str);
	if (cube->sprites.textures[current])
		return ;
	while (i < current)
	{
		mlx_delete_texture(cube->sprites.textures[i]);
		i++;
	}
	if (cube->mlx_window && cube->mlx_img)
		mlx_delete_image(cube->mlx_window, cube->mlx_img);
	if (cube->mlx_window)
		mlx_terminate(cube->mlx_window);
	ft_putstr_fd("Error\nloading sprite textures failed\n", 2);
	close(cube->map_fd);
	exit(EXIT_FAILURE);
}

void	init_sprites(t_cub *cube)
{
	set_the_sprite_protected(cube, 0, "sprites_bonus/1.png");
	set_the_sprite_protected(cube, 1, "sprites_bonus/2.png");
	set_the_sprite_protected(cube, 2, "sprites_bonus/3.png");
	set_the_sprite_protected(cube, 3, "sprites_bonus/4.png");
	set_the_sprite_protected(cube, 4, "sprites_bonus/5.png");
	set_the_sprite_protected(cube, 5, "sprites_bonus/6.png");
	set_the_sprite_protected(cube, 6, "sprites_bonus/7.png");
	set_the_sprite_protected(cube, 7, "sprites_bonus/8.png");
	set_the_sprite_protected(cube, 8, "sprites_bonus/9.png");
	set_the_sprite_protected(cube, 9, "sprites_bonus/10.png");
	set_the_sprite_protected(cube, 10, "sprites_bonus/11.png");
	set_the_sprite_protected(cube, 11, "sprites_bonus/12.png");
	set_the_sprite_protected(cube, 12, "sprites_bonus/13.png");
	cube->sprites.img = NULL;
	cube->sprites_ready = true;
}
