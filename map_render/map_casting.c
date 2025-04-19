/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 23:02:56 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/07 09:54:21 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	func(t_pinfo *player_info, t_cub *cub)
{
	while (player_info->count)
	{
		player_info->tmp_x = roundf(player_info->new_x + cos(cub
					->player->rotation_angle + player_info->angle)
				* player_info->step);
		player_info->tmp_y = roundf(player_info->new_y + sin(cub
					->player->rotation_angle + player_info->angle)
				* player_info->step);
		if (cub->map[(int)(player_info->tmp_y / TILESIZE)][(int)
			(player_info->tmp_x / TILESIZE)] == '1' || cub->map[(int)
			(player_info->tmp_y / TILESIZE)][(int)(player_info->tmp_x
			/ TILESIZE)] == '2')
			return ;
		player_info->angle += M_PI / 4;
		player_info->count--;
	}
}

void	player_update(t_cub *cub)
{
	t_pinfo	player_info;

	player_info.step = cub->player->walk_direction * cub->player->move_speed;
	player_info.count = 8;
	cub->player->rotation_angle += cub->player->turn_direction
		* cub->player->rotation_speed;
	player_info.strafe_step = STRAFE_SPEED * cub->player->strafe_direction;
	player_info.new_x = roundf(cub->player->x
			+ cos(cub->player->rotation_angle) * player_info.step
			+ (cos(cub->player->rotation_angle + M_PI / 2))
			* player_info.strafe_step);
	player_info.new_y = roundf(cub->player->y
			+ sin(cub->player->rotation_angle) * player_info.step
			+ (sin(cub->player->rotation_angle + M_PI / 2))
			* player_info.strafe_step);
	player_info.tmp_y = player_info.new_y;
	player_info.tmp_x = player_info.new_x;
	player_info.angle = 0;
	player_info.step = 2;
	func(&player_info, cub);
	if (!player_info.count)
	{
		cub->player->x = player_info.new_x;
		cub->player->y = player_info.new_y;
	}
}
