/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:29:01 by akoutate          #+#    #+#             */
/*   Updated: 2025/02/05 10:26:31 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_texture(int right_x_pixel, t_cub *cube,
	mlx_texture_t *pic_data, t_tinfo t_data)
{
	int				i;
	int				texture_offset_y;
	unsigned int	how_much_to_add;
	uint8_t			*init_color;

	i = 0;
	while (i < t_data.pixels)
	{
		texture_offset_y = (t_data.y0 + (t_data.wall_strip_height / 2)
				- ((double)W_HEIGHT / 2)) * (pic_data->height
				/ t_data.wall_strip_height);
		how_much_to_add = (pic_data->width * pic_data->bytes_per_pixel
				* texture_offset_y) + right_x_pixel;
		init_color = pic_data->pixels + how_much_to_add;
		mlx_put_pixel(cube->mlx_img, (int)t_data.x, (int)t_data.y0, create_trgb
			(init_color[0], init_color[1], init_color[2], init_color[3]));
		t_data.y0++;
		i++;
	}
}

void	textures(t_cub *cube, double id,
	t_tinfo t_data, mlx_texture_t *pic_data)
{
	int		right_x_pixel;

	right_x_pixel = (int)(id * pic_data->width / TILESIZE)
		* pic_data->bytes_per_pixel;
	t_data.pixels = t_data.y1 - t_data.y0;
	draw_texture(right_x_pixel, cube, pic_data, t_data);
}
