/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:06:52 by ymassiou          #+#    #+#             */
/*   Updated: 2024/10/25 15:09:11 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*set_line(char *save, t_cub *cub)
{
	ssize_t	i;
	char	*result;

	i = 0;
	if (save == NULL)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	result = ft_substr(save, 0, i, cub);
	return (result);
}

static char	*prepare_next(char *save, t_cub *cub)
{
	ssize_t	i;
	char	*result;

	i = 0;
	if (save == NULL)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	result = ft_strdup(save + i, cub);
	return (result);
}

static char	*fill_the_line(char *save, char *buffer, int fd, t_cub *cub)
{
	ssize_t	rbytes;
	char	*tmp;

	rbytes = 1;
	while (!ft_strchr(save, '\n') && rbytes)
	{
		rbytes = read(fd, buffer, 10);
		if (rbytes == -1)
			return (NULL);
		buffer[rbytes] = '\0';
		tmp = save;
		save = ft_strjoin(save, buffer, cub);
	}
	if (save && save[0] == '\0')
		return (NULL);
	return (save);
}

char	*get_next_line(int fd, t_cub *cub)
{
	static char	*save;
	char		*line;
	char		*buffer;

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	buffer = gc_malloc(11, cub);
	save = fill_the_line(save, buffer, fd, cub);
	line = set_line(save, cub);
	save = prepare_next(save, cub);
	return (line);
}
