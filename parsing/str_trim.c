/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_trim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:32:49 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/07 09:18:40 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check(char needle, const char *haystack)
{
	size_t	i;

	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle)
			return (1);
		i++;
	}
	return (0);
}

static char	*generate(size_t len, const char *src, t_cub *cub)
{
	char	*result;
	size_t	i;

	i = 0;
	result = NULL;
	result = (char *)gc_malloc(len + 1, cub);
	if (result == NULL)
		return (NULL);
	while (i < len)
	{
		result[i] = src[i];
		i++;
	}
	result[len] = '\0';
	return (result);
}

char	*ft_strtrim(const char *s1, const char *set, t_cub *cub)
{
	size_t	i;
	size_t	j;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	result = NULL;
	j = ft_strlen(s1) - 1;
	while (check(s1[i], set))
		i++;
	if (!s1[i])
		return (ft_strdup("", cub));
	while (check(s1[j], set))
		j--;
	result = generate(j - i + 1, &s1[i], cub);
	if (result == NULL)
		return (NULL);
	return (result);
}
