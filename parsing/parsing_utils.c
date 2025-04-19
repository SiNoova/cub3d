/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:59:39 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/07 13:07:29 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	element_type(char *line)
{
	while (*line && ft_iswspace(*line))
		line++;
	if (!ft_strncmp(line, "NO ", 3))
		return (NO);
	else if (!ft_strncmp(line, "SO ", 3))
		return (SO);
	else if (!ft_strncmp(line, "WE ", 3))
		return (WE);
	else if (!ft_strncmp(line, "EA ", 3))
		return (EA);
	else if (!ft_strncmp(line, "C ", 2))
		return (C);
	else if (!ft_strncmp(line, "F ", 2))
		return (F);
	else if (!line[0])
		return (0);
	else
		return (-1);
}

static char	*get_data(char *line, int type, t_cub *cub)
{
	size_t	len;
	char	*data;
	char	*tmp;

	len = 0;
	while (*line && ft_iswspace(*line))
		line++;
	if (type >= 11 && type <= 14)
		line += 2;
	else if (type == 15 || type == 16)
		line++;
	while (*line && ft_iswspace(*line))
		line++;
	tmp = line;
	while (*tmp && *tmp != '\n')
	{
		tmp++;
		len++;
	}
	data = gc_malloc(len + 1, cub);
	ft_strlcpy(data, line, len + 1);
	return (data);
}

int	fill_field(char *line, int type, t_cub *cub)
{
	if (!cub->so && type == SO)
		cub->so = get_data(line, type, cub);
	else if (!cub->no && type == NO)
		cub->no = get_data(line, type, cub);
	else if (!cub->we && type == WE)
		cub->we = get_data(line, type, cub);
	else if (!cub->ea && type == EA)
		cub->ea = get_data(line, type, cub);
	else if (!cub->color_floor && type == F)
		cub->color_floor = line;
	else if (!cub->color_ceiling && type == C)
		cub->color_ceiling = line;
	else
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("➜Element field is redifined!\n", 2);
		return (-1);
	}
	return (0);
}

int	empty_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_iswspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	full_cub(t_cub *cub)
{
	if (cub->no
		&& cub->so
		&& cub->we
		&& cub->ea
		&& cub->color_floor
		&& cub->color_ceiling)
		return (1);
	return (0);
}
