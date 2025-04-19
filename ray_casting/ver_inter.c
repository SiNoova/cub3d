/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ver_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:46:12 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/05 10:20:01 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	updater(t_cub *cub, double *line_len, t_point *point)
{
	double	check;
	double	player_x;
	double	player_y;

	player_x = cub->player->x;
	player_y = cub->player->y;
	if (check_coordinates(cub->closest_inter_x, cub->closest_inter_y, cub))
		return (2);
	check = cub->closest_inter_x;
	if (cub->player->left)
		check = cub->closest_inter_x - 1;
	if (cub->map[(long)(cub->closest_inter_y / TILESIZE)]
		[(long)(check / TILESIZE)] == '1'
		|| cub->map[(long)(cub->closest_inter_y / TILESIZE)]
		[(long)(check / TILESIZE)] == '2')
	{
		*line_len = get_distance(player_x, player_y,
				cub->closest_inter_x, cub->closest_inter_y);
		point->x = cub->closest_inter_x;
		point->y = cub->closest_inter_y;
		return (1);
	}
	return (0);
}

static double	next_inter_dist(t_cub *cub,
	t_point *point, double step_x, double step_y)
{
	double	line_len;
	int		res;

	line_len = 0;
	while (1)
	{
		res = updater(cub, &line_len, point);
		if (res == 1)
			break ;
		else if (res == 2)
			return (LONG_MAX);
		cub->closest_inter_y += step_y;
		cub->closest_inter_x += step_x;
	}
	return (line_len);
}

static double	define_step(double ray_angle, t_point *point, t_cub *cub)
{
	double	step_x;
	double	step_y;

	step_x = TILESIZE;
	step_y = TILESIZE * tan(ray_angle);
	if (cub->player->left)
	{
		step_x *= -1;
		step_y *= -1;
	}
	return (next_inter_dist(cub, point, step_x, step_y));
}

double	closest_vertical_inter(t_cub *cub, double ray_angle, t_point *point)
{
	bool	right;
	bool	left;

	ray_angle = limit_angle(ray_angle);
	right = ray_angle < M_PI_2 || ray_angle > 3 * M_PI_2;
	left = !right;
	cub->player->right = right;
	cub->player->left = left;
	cub->closest_inter_x = floor((double)cub->player->x / TILESIZE) * TILESIZE;
	if (right)
		cub->closest_inter_x += TILESIZE;
	cub->closest_inter_y = cub->player->y
		+ ((cub->closest_inter_x - cub->player->x) * tan(ray_angle));
	return (define_step(ray_angle, point, cub));
}
