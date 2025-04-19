/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:02:40 by ymassiou          #+#    #+#             */
/*   Updated: 2024/10/25 15:09:21 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;
	size_t	dlen;
	size_t	i;

	i = 0;
	slen = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (slen);
	while (dst[i])
		i++;
	dlen = i;
	if (dstsize <= dlen)
		return (dstsize + slen);
	if (dlen + slen < dstsize)
		ft_memcpy(&dst[i], src, slen + 1);
	else
	{
		ft_memcpy(&dst[i], src, dstsize - dlen - 1);
		dst[dstsize - 1] = 0;
	}
	return (dlen + slen);
}

char	*ft_strjoin(char *s1, char *s2, t_cub *cub)
{
	char	*result;

	if (s1 == NULL)
		return (ft_strdup(s2, cub));
	if (s2 == NULL)
		return (ft_strdup(s1, cub));
	result = NULL;
	result = (char *)gc_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, cub);
	ft_memcpy(result, s1, ft_strlen(s1) + 1);
	ft_strlcat(result, s2, ft_strlen(s1) + ft_strlen(s2) + 2);
	return (result);
}
