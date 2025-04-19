/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:39:20 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/05 13:45:17 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static double	find_closest_inter(t_point *chosen,
	t_cub *cub, double ray_angle)
{
	double	vertical_distance;
	double	horizontal_distance;
	double	closest_inter;
	t_point	v_inter;
	t_point	h_inter;

	horizontal_distance = closest_horizontal_inter(cub, ray_angle, &h_inter);
	vertical_distance = closest_vertical_inter(cub, ray_angle, &v_inter);
	*chosen = h_inter;
	closest_inter = horizontal_distance;
	chosen->hori_or_vert = 1;
	if (horizontal_distance >= vertical_distance)
	{
		*chosen = v_inter;
		closest_inter = vertical_distance;
		chosen->hori_or_vert = 0;
	}
	closest_inter = closest_inter
		* cos(ray_angle - cub->player->rotation_angle);
	return (closest_inter);
}

void	founc(t_point chosen, t_cub *cub, t_tinfo t_data)
{
	if (chosen.hori_or_vert && (cub->map[(long)(chosen.y / TILESIZE)]
		[(long)(chosen.x / TILESIZE)] == '2'
		|| cub->map[(long)((chosen.y - TILESIZE) / TILESIZE)]
		[(long)(chosen.x / TILESIZE)] == '2'))
		textures(cub, fmod(chosen.x, TILESIZE), t_data, cub->door_pic_data);
	else if (!chosen.hori_or_vert && (cub->map[(long)(chosen.y / TILESIZE)]
		[(long)(chosen.x / TILESIZE)] == '2'
		|| cub->map[(long)(chosen.y / TILESIZE)]
		[(long)((chosen.x - TILESIZE) / TILESIZE)] == '2'))
		textures(cub, fmod(chosen.y, TILESIZE), t_data, cub->door_pic_data);
	else if (cub->player->down && chosen.hori_or_vert)
		textures(cub, TILESIZE - fmod(chosen.x,
				TILESIZE), t_data, cub->so_pic_data);
	else if (cub->player->left && !chosen.hori_or_vert)
		textures(cub, TILESIZE - fmod(chosen.y,
				TILESIZE), t_data, cub->we_pic_data);
	else if (cub->player->right && !chosen.hori_or_vert)
		textures(cub, fmod(chosen.y, TILESIZE), t_data, cub->ea_pic_data);
	else if (cub->player->up && chosen.hori_or_vert)
		textures(cub, fmod(chosen.x, TILESIZE), t_data, cub->no_pic_data);
}

void	ray_cast(t_cub *cub, double ray_angle,
	double fov_in_rad, t_tinfo t_data)
{
	long	ray_id;
	double	closest_inter;
	double	project_plane_distance;
	t_point	chosen;

	ray_id = 0;
	project_plane_distance = ((double)WIN_WIDTH / 2)
		/ tan((FOV * M_PI) / 180.0 / 2);
	while (ray_id < WIN_WIDTH)
	{
		closest_inter = find_closest_inter(&chosen, cub, ray_angle);
		t_data.wall_strip_height = (TILESIZE / closest_inter)
			* project_plane_distance;
		t_data.y0 = ((double)W_HEIGHT / 2) - (t_data.wall_strip_height / 2);
		t_data.y1 = t_data.wall_strip_height + ((double)W_HEIGHT / 2)
			- (t_data.wall_strip_height / 2);
		if (t_data.y0 < 0)
			t_data.y0 = 0;
		if (t_data.y1 > W_HEIGHT)
			t_data.y1 = W_HEIGHT;
		t_data.x = ray_id;
		founc(chosen, cub, t_data);
		ray_angle += fov_in_rad / WIN_WIDTH;
		ray_id++;
	}
}
