/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:39:09 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/07 22:06:12 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_p(int c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	clear_textures(t_cub *cub)
{
	if (cub->ea_pic_data)
		mlx_delete_texture(cub->ea_pic_data);
	if (cub->we_pic_data)
		mlx_delete_texture(cub->we_pic_data);
	if (cub->so_pic_data)
		mlx_delete_texture(cub->so_pic_data);
	if (cub->no_pic_data)
		mlx_delete_texture(cub->no_pic_data);
	if (cub->door_pic_data)
		mlx_delete_texture(cub->door_pic_data);
}

static void	offset_seeker(int map_fd, char *map_file, t_cub *cub)
{
	int		iter;
	char	*line;

	iter = 6;
	line = NULL;
	while (1)
	{
		if (get_next_line(map_fd, cub) == NULL)
			break ;
	}
	close(map_fd);
	map_fd = open(map_file, O_RDONLY, 0644);
	cub->map_fd = map_fd;
	while (iter)
	{
		line = get_next_line(map_fd, cub);
		if (!line)
			break ;
		if (*line && !empty_line(line))
			iter--;
	}
}

t_list	*map_split(int map_fd, char *map_file, t_cub *cub)
{
	offset_seeker(map_fd, map_file, cub);
	return (map_to_list(map_fd, cub));
}
