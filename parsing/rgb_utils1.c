/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:06:02 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/05 17:51:48 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	rgb_range(int color)
{
	if (!(color >= 0 && color <= 255))
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	return (1);
}

static int	validate_commas(char *tmp)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == ',')
		{
			if (!ft_isdigit(tmp[i + 1]) && !ft_iswspace(tmp[i + 1]))
				return (ft_putstr_fd("Error\n➜Not a valid RGB color!\n", 2), 0);
			count++;
		}
		i++;
	}
	if (count != 2)
	{
		ft_putstr_fd("Error\n➜Value cannot represent a RGB color!\n", 2);
		return (0);
	}
	return (1);
}

static int	validate_chars(char *tmp)
{
	size_t	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] != ',' && tmp[i] != '\n'
			&& tmp[i] != ' ' && !ft_isdigit(tmp[i]))
		{
			ft_putstr_fd("Error\n➜Value cannot represent a RGB color!\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	pre_check(char **string)
{
	char	*tmp;

	while (**string && ft_iswspace(**string))
		(*string)++;
	(*string)++;
	while (**string && ft_iswspace(**string))
		(*string)++;
	tmp = *string;
	if (!validate_commas(tmp) || !validate_chars(tmp))
		return (0);
	return (1);
}

t_rgb	*rgb_new(unsigned char r,
				unsigned char g, unsigned char b, t_cub *cub)
{
	t_rgb	*new;

	new = gc_malloc(sizeof(t_rgb), cub);
	new->red = r;
	new->green = g;
	new->blue = b;
	return (new);
}
