/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hor_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:46:54 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/05 10:30:40 by ymassiou         ###   ########.fr       */
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
	if (check_coordinates(cub->hor_closest_inter_x,
			cub->hor_closest_inter_y, cub))
		return (2);
	check = cub->hor_closest_inter_y;
	if (cub->player->up)
		check = cub->hor_closest_inter_y - 1;
	if (cub->map[(long)(check / TILESIZE)]
		[(long)(cub->hor_closest_inter_x / TILESIZE)] == '1'
		|| cub->map[(long)(check / TILESIZE)]
		[(long)(cub->hor_closest_inter_x / TILESIZE)] == '2')
	{
		*line_len = get_distance(player_x, player_y,
				cub->hor_closest_inter_x, cub->hor_closest_inter_y);
		point->x = cub->hor_closest_inter_x;
		point->y = cub->hor_closest_inter_y;
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
		cub->hor_closest_inter_y += step_y;
		cub->hor_closest_inter_x += step_x;
	}
	return (line_len);
}

static double	define_step(double ray_angle, t_point *point, t_cub *cub)
{
	double	step_x;
	double	step_y;

	step_y = TILESIZE;
	step_x = TILESIZE / tan(ray_angle);
	if (cub->player->up)
	{
		step_x *= -1;
		step_y *= -1;
	}
	return (next_inter_dist(cub, point, step_x, step_y));
}

double	closest_horizontal_inter(t_cub *cub, double ray_angle, t_point *point)
{
	bool	down;
	bool	up;

	ray_angle = limit_angle(ray_angle);
	up = ray_angle > M_PI && ray_angle < 2 * M_PI;
	down = !up;
	cub->player->down = down;
	cub->player->up = up;
	cub->hor_closest_inter_y = floor((double)cub->player->y
			/ TILESIZE) * TILESIZE;
	if (down)
		cub->hor_closest_inter_y += TILESIZE;
	cub->hor_closest_inter_x = cub->player->x
		+ ((cub->hor_closest_inter_y - cub->player->y) / tan(ray_angle));
	return (define_step(ray_angle, point, cub));
}
