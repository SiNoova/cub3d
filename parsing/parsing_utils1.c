/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:13:48 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/07 21:07:49 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	element_not_valid(int iter)
{
	if (iter)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("➜Elements are not correct!\n", 2);
	}
	else
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("➜Element type not defined!\n", 2);
	}
	return (1);
}

static int	element_redifined(char *line, int map_fd, int ret, t_cub *cub)
{
	line = get_next_line(map_fd, cub);
	if (line)
	{
		ret = element_type(line);
		if (ret >= 11 && ret <= 16)
		{
			ft_putstr_fd("Error\n", 2);
			ft_putstr_fd("➜Element field is redifined!\n", 2);
			return (1);
		}
	}
	return (0);
}

int	fill_cub(t_cub *cub, int map_fd)
{
	int		iter;
	int		ret;
	char	*line;

	iter = 7;
	ret = 0;
	line = NULL;
	while (iter)
	{
		line = get_next_line(map_fd, cub);
		if (line == NULL)
			break ;
		if (*line != 0 && !empty_line(line) && --iter)
		{
			ret = element_type(line);
			if ((ret >= 11 && ret <= 16) && fill_field(line, ret, cub) == -1)
				return (1);
			else if (ret == -1)
				return (element_not_valid(iter));
			if (full_cub(cub) && element_redifined(line, map_fd, ret, cub))
				return (1);
		}
	}
	return (0);
}

void	init_player(t_cub *cub)
{
	cub->player = gc_malloc(sizeof(t_player), cub);
	cub->player->x = (double)cub->window_width / 2;
	cub->player->y = (double)cub->window_height / 2;
	cub->player->radius = (double)PLAYER_RADIUS;
	cub->player->turn_direction = 0;
	cub->player->walk_direction = 0;
	cub->player->strafe_direction = 0;
	cub->player->move_speed = 4;
	cub->player->rotation_speed = 3 * M_PI / 180;
}

void	init_cub(t_cub *cub)
{
	cub->no = NULL;
	cub->so = NULL;
	cub->we = NULL;
	cub->ea = NULL;
	cub->no_pic_data = NULL;
	cub->so_pic_data = NULL;
	cub->we_pic_data = NULL;
	cub->ea_pic_data = NULL;
	cub->door_pic_data = NULL;
	cub->color_floor = NULL;
	cub->color_ceiling = NULL;
	cub->garbage = NULL;
	cub->mlx_window = NULL;
	cub->window_height = 0;
	cub->window_width = 0;
	cub->mlx_img = NULL;
	cub->map = NULL;
	cub->map_fd = -1;
	cub->sprites_ready = false;
	init_player(cub);
}
