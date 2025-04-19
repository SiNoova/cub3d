/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:44:16 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/07 19:09:19 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	load_attr(t_cub *cub, t_list *map, int map_fd)
{
	cub->map = list_to_arr(map, cub);
	player_location(cub);
	cub->window_height = TILESIZE * ft_lstsize(map);
	cub->window_width = TILESIZE * ft_strlen(cub->map[0]);
	cub->no_pic_data = mlx_load_png(cub->no);
	cub->we_pic_data = mlx_load_png(cub->we);
	cub->so_pic_data = mlx_load_png(cub->so);
	cub->ea_pic_data = mlx_load_png(cub->ea);
	cub->door_pic_data = mlx_load_png("textures/door.png");
	if (!cub->no_pic_data || !cub->we_pic_data || !cub->so_pic_data
		|| !cub->ea_pic_data || !cub->door_pic_data)
	{
		clear_textures(cub);
		ft_putstr_fd("\n", 2);
		gc_free(cub);
		return (-1);
	}
	init_sprites(cub);
	close(map_fd);
	return (0);
}

int	map_check(t_cub *cub, char *map_file)
{
	int		map_fd;
	t_list	*map;

	init_cub(cub);
	map_fd = parse_map_name(map_file, cub);
	if (map_fd == -1)
		return (-1);
	if (fill_cub(cub, map_fd))
		return (-1);
	if (!full_cub(cub))
		return (ft_putstr_fd("Error\n➜Invalid map!\n", 2), -1);
	if (check_rgb(cub))
		return (-1);
	map = map_split(map_fd, map_file, cub);
	if (!map_checker(map))
		return (ft_putstr_fd("Error\n➜Invalid map!\n", 2), -1);
	if (load_attr(cub, map, map_fd) == -1)
		return (-1);
	return (0);
}

void	set_spawn_direction(t_cub *cub)
{
	if (cub->player->spawn_direction == 'N')
		cub->player->rotation_angle = 3 * M_PI_2;
	else if (cub->player->spawn_direction == 'S')
		cub->player->rotation_angle = M_PI_2;
	else if (cub->player->spawn_direction == 'W')
		cub->player->rotation_angle = M_PI;
	else
		cub->player->rotation_angle = 0;
}

static int	foreach_str_check(char *input, t_cub *cub)
{
	size_t	i;

	i = 0;
	input = ft_strtrim(input, " ", cub);
	if (input[0] == ' ' || input[0] == '\n')
		return (0);
	while (input[i])
	{
		if (ft_iswspace(input[i]) && input[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	misplaced_space(char *input, t_cub *cub)
{
	char	**res;
	size_t	idx;

	idx = 0;
	res = ft_split(input, ',', cub);
	while (res[idx])
	{
		if (*res[idx] == '\0' || *res[idx] == '\n')
		{
			ft_putstr_fd("Error\n➜Value cannot represent a RGB color!\n", 2);
			return (1);
		}
		if (!foreach_str_check(res[idx], cub))
		{
			ft_putstr_fd("Error\n➜Value cannot represent a RGB color!\n", 2);
			return (1);
		}
		idx++;
	}
	return (0);
}
