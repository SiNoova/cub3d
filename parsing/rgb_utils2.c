/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:19:15 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/05 17:50:45 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	extract_and_validate_color(char **string)
{
	int	color;

	while (**string && **string != ',')
		(*string)++;
	(*string)++;
	color = ft_atoi(*string);
	if (!rgb_range(color))
		return (-1);
	return (color);
}

static int	validate_remaining_string(char *string)
{
	while (*string && ft_iswspace(*string))
		string++;
	while (*string && ft_isdigit(*string))
		string++;
	if (*string)
	{
		ft_putstr_fd("Error\n➜Value cannot represent a RGB color!\n", 2);
		return (0);
	}
	return (1);
}

static t_rgb	*extract_rgb(char *string, t_cub *cub)
{
	int	red;
	int	green;
	int	blue;

	if (!pre_check(&string))
		return (NULL);
	if (misplaced_space(string, cub))
		return (NULL);
	string = ft_substr(string, 0, ft_strlen(string) - 1, cub);
	red = ft_atoi(string);
	if (!rgb_range(red))
		return (NULL);
	green = extract_and_validate_color(&string);
	if (green == -1)
		return (NULL);
	blue = extract_and_validate_color(&string);
	if (blue == -1)
		return (NULL);
	if (!validate_remaining_string(string))
		return (NULL);
	return (rgb_new(red, green, blue, cub));
}

int	check_rgb(t_cub *cub)
{
	char	*floor;
	char	*ceilng;

	if (!cub)
		return (-1);
	floor = cub->color_floor;
	ceilng = cub->color_ceiling;
	cub->floor = extract_rgb(floor, cub);
	if (cub->floor == NULL)
		return (-1);
	cub->ceiling = extract_rgb(ceilng, cub);
	if (cub->ceiling == NULL)
		return (-1);
	return (0);
}
