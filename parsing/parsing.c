/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:58:21 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/07 19:03:43 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_list	*map_to_list(int map_fd, t_cub *cub)
{
	t_list	*head;
	size_t	max;

	max = 0;
	head = process_map_lines(map_fd, cub, &max);
	if (!head || !map_checker(head))
		return (head);
	max--;
	extend_all_lines(head, max, cub);
	if (check_adjacent_x(head))
		return (head);
	replace_x_with_one(head);
	if (validate_twos(head))
		return (head);
	return (head);
}

int	parse_map_name(char *map_file, t_cub *cub)
{
	int		map_fd;
	char	*extention;

	if (ft_strlen(map_file) < 5)
	{
		ft_putstr_fd("Error: The scene description file", 2);
		ft_putstr_fd(" name must be at least 4 characters long!\n", 2);
		return (-1);
	}
	extention = ft_substr(map_file, ft_strlen(map_file) - 4, 4, cub);
	if (ft_strcmp(".cub", extention))
	{
		ft_putstr_fd("Error: scene description file ", 2);
		ft_putstr_fd("must end up with the .cub extension!\n", 2);
		return (-1);
	}
	map_fd = open(map_file, O_RDONLY, 0644);
	cub->map_fd = map_fd;
	if (map_fd == -1)
	{
		ft_putstr_fd("Error: opening the scene description file failed!\n", 2);
		return (-1);
	}
	return (map_fd);
}
