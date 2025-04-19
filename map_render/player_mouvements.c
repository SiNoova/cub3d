/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouvements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:06:52 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/05 13:44:11 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	wasd_keyhook(t_cub *cub, int *is_moving)
{
	if (mlx_is_key_down(cub->mlx_window, MLX_KEY_W))
	{
		cub->player->walk_direction = 1;
		*is_moving = 1;
	}
	if (mlx_is_key_down(cub->mlx_window, MLX_KEY_A))
	{
		cub->player->strafe_direction = -1;
		*is_moving = 1;
	}
	if (mlx_is_key_down(cub->mlx_window, MLX_KEY_S))
	{
		cub->player->walk_direction = -1;
		*is_moving = 1;
	}
	if (mlx_is_key_down(cub->mlx_window, MLX_KEY_D))
	{
		cub->player->strafe_direction = 1;
		*is_moving = 1;
	}
}

void	arrows_keyhook(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx_window, MLX_KEY_RIGHT))
		cub->player->turn_direction = 1;
	if (mlx_is_key_down(cub->mlx_window, MLX_KEY_LEFT))
		cub->player->turn_direction = -1;
}

void	mouse_hook(t_cub *cube)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(cube->mlx_window, &x, &y);
	if (x == -780)
		cube->player->turn_direction = -1;
	if (x == 1779)
		cube->player->turn_direction = 1;
	if (x > cube->x_mouse)
		cube->player->turn_direction = 1;
	else if (x < cube->x_mouse)
		cube->player->turn_direction = -1;
	cube->x_mouse = x;
}

void	change_map(t_cub *cub, char old, char new)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = cub->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == old)
				map[i][j] = new;
			j++;
		}
		i++;
	}
}
