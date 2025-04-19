/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:13:18 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/08 15:41:57 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <sys/_types/_size_t.h>

int	is_all(char *string, int c)
{
	int	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i] && string[i] != '\n')
	{
		if (string[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	check_line(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!str || !(str[0] == '1' && str[ft_strlen(str) - 1] == '1'))
		return (-1);
	while (str[i])
	{
		if (str[i] != '0' && str[i] != '1'
			&& str[i] != '2' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != 'W'
			&& str[i] != 'E')
			return (-1);
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (is_p(str[i]))
			count++;
		i++;
	}
	return (count);
}

int	map_checker(t_list *map)
{
	int	player_counter;
	int	ret;

	player_counter = 0;
	if (!map)
		return (0);
	if (ft_lstsize(map) < 3)
		return (0);
	if (!is_all(map->c, '1')
		|| !is_all(ft_lstlast(map)->c, '1'))
		return (0);
	while (map)
	{
		ret = check_line(map->c);
		if (ret == 1)
			player_counter++;
		else if (ret != 0)
			return (0);
		if (player_counter > 1)
			return (0);
		map = map->next;
	}
	return (player_counter);
}

char	**list_to_arr(t_list *head, t_cub *data)
{
	int		size;
	char	**res;
	int		i;

	size = ft_lstsize(head);
	res = gc_malloc((size + 1) * sizeof(char *), data);
	i = 0;
	while (head && i < size)
	{
		res[i] = gc_malloc(ft_strlen(head->c), data);
		res[i] = ft_strdup(head->c, data);
		head = head->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	player_location(t_cub *cub)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (cub->map[j])
	{
		i = 0;
		while (cub->map[j][i])
		{
			if (cub->map[j][i] == 'N'
				|| cub->map[j][i] == 'S'
				|| cub->map[j][i] == 'E'
				|| cub->map[j][i] == 'W')
			{
				cub->player->x = i * TILESIZE + (double)TILESIZE / 2;
				cub->player->y = j * TILESIZE + (double)TILESIZE / 2;
				cub->player->spawn_direction = cub->map[j][i];
				set_spawn_direction(cub);
				break ;
			}
			i++;
		}
		j++;
	}
}
