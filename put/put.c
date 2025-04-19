/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:52:05 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/05 10:27:03 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_ceiling(t_cub *cub, int color)
{
	long	x;
	long	y;

	x = 0;
	y = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < W_HEIGHT / 2)
		{
			mlx_put_pixel(cub->mlx_img, x, y, color);
			y++;
		}
		x++;
	}
}

void	put_floor(t_cub *cub, int color)
{
	long	x;
	long	y;

	x = 0;
	y = W_HEIGHT / 2;
	while (x < WIN_WIDTH)
	{
		y = W_HEIGHT / 2;
		while (y < W_HEIGHT)
		{
			mlx_put_pixel(cub->mlx_img, x, y, color);
			y++;
		}
		x++;
	}
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*a;
	size_t			i;

	i = 0;
	a = (unsigned char *)b;
	while (i < len)
	{
		a[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	put_frame(t_cub *cub)
{
	double	start_angle;
	double	fov_in_rad;
	double	player_angle;
	t_tinfo	t_data;

	ft_memset(&t_data, 0, sizeof(t_tinfo));
	put_ceiling(cub, (cub->ceiling->red << 24)
		| (cub->ceiling->green << 16) | (cub->ceiling->blue << 8) | 0xFF);
	put_floor(cub, (cub->floor->red << 24)
		| (cub->floor->green << 16) | (cub->floor->blue << 8) | 0xFF);
	fov_in_rad = (FOV * M_PI / 180);
	player_angle = limit_angle(cub->player->rotation_angle);
	start_angle = player_angle - fov_in_rad / 2;
	ray_cast(cub, start_angle, fov_in_rad, t_data);
}
