/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:18:29 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/05 14:49:59 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*gen_word(const char *s, char c, t_cub *cub)
{
	size_t	i;
	char	*result;

	result = NULL;
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	result = ft_substr(s, 0, i, cub);
	return (result);
}

static void	*ft_free(char **to_free, size_t elements)
{
	size_t	i;

	i = 0;
	while (i < elements)
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
	return (NULL);
}

static int	words_count(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c, t_cub *data)
{
	size_t	words;
	char	**result;
	size_t	j;

	if (s == NULL)
		return (NULL);
	words = words_count(s, c);
	result = NULL;
	j = 0;
	result = (char **)gc_malloc((words + 1) * sizeof(char *), data);
	if (result == NULL)
		return (NULL);
	while (*s && words--)
	{
		while (*s == c && *s)
			s++;
		result[j] = gen_word(s, c, data);
		if (result[j] == NULL)
			return (ft_free(result, j));
		j++;
		while (*s != c && *s)
			s++;
	}
	result[j] = 0;
	return (result);
}
