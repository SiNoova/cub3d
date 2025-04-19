/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouvements2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:30:40 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/05 13:34:35 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_circle(int cx, int cy, int r, void *img)
{
	int	x;
	int	y;

	y = cy - r;
	while (y < cy + r)
	{
		x = cx - r;
		while (x <= cx + r)
		{
			if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r)
				mlx_put_pixel(img, x, y, RED);
			x++;
		}
		y++;
	}
}

char	get_tile_mode(t_cub *cube, int tile_x, int tile_y)
{
	if (tile_x < 0 || tile_y < 0 || tile_x * TILESIZE >= cube->window_width
		|| tile_y * TILESIZE >= cube->window_height)
		return ('1');
	if ((size_t)tile_x > ft_strlen(cube->map[tile_y]))
		return ('1');
	return (cube->map[tile_y][tile_x]);
}

void	render_tile(t_cub *cube, int x, int y)
{
	int	color;
	int	mode;
	int	color_x;
	int	color_y;

	color_x = cube->player->x - ((double)MINI_MAP_WH / 2) / 0.25 + (x / 0.25);
	color_y = cube->player->y - ((double)MINI_MAP_WH / 2) / 0.25 + (y / 0.25);
	mode = get_tile_mode(cube, color_x / TILESIZE, color_y / TILESIZE);
	if (mode == '1')
		color = LIGHT_GREEN;
	else if (mode == '2')
		color = CYAN;
	else
		color = BLACK;
	mlx_put_pixel(cube->mlx_img, x, y, color);
}

void	render_minimap(t_cub *cube)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINI_MAP_WH)
	{
		x = 0;
		while (x < MINI_MAP_WH)
		{
			render_tile(cube, x, y);
			x++;
		}
		y++;
	}
	draw_circle(MINI_MAP_WH / 2, MINI_MAP_WH / 2, 5, cube->mlx_img);
}

void	my_keyhook(void *param)
{
	t_cub	*cub;
	int		is_moving;

	cub = (t_cub *)param;
	is_moving = 0;
	mouse_hook(cub);
	wasd_keyhook(cub, &is_moving);
	arrows_keyhook(cub);
	player_update(cub);
	put_frame(cub);
	sprite(cub, 0, is_moving);
	render_minimap(cub);
	cub->player->walk_direction = 0;
	cub->player->strafe_direction = 0;
	cub->player->turn_direction = 0;
	is_moving = 0;
}
