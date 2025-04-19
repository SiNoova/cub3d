/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:37:23 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/08 15:42:31 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_two_neighbors(char *str, size_t idx,
								t_list *prev, t_list *next)
{
	int	flag;

	flag = 0;
	if (str[idx - 1] == '1' && str[idx + 1] == '1')
		flag++;
	if (prev->c[idx] == '1' && next->c[idx] == '1')
		flag++;
	return (flag != 1);
}

int	validate_twos(t_list *head)
{
	t_list	*prev;
	char	*tmp_str;
	size_t	idx;

	prev = head;
	head = head->next;
	while (head && head->next)
	{
		tmp_str = head->c;
		idx = 0;
		while (tmp_str[idx])
		{
			if (idx && tmp_str[idx] == '2'
				&& check_two_neighbors(tmp_str, idx, prev, head->next))
			{
				head->c[idx] = 'X';
				return (1);
			}
			idx++;
		}
		prev = head;
		head = head->next;
	}
	return (0);
}

static int	space_bound_check(t_list *list, t_cub *cub)
{
	char	*line;
	t_list	*prev;
	size_t	idx;

	prev = NULL;
	while (list)
	{
		idx = 0;
		line = ft_substr(list->c, 0, ft_strlen(list->c) - 1, cub);
		while (line[idx])
		{
			if ((line[idx] == '0' || line[idx] == '2'
					|| is_p(line[idx])) && prev && list->next)
			{
				if (line[idx - 1] == ' ' || line[idx + 1] == ' ')
					return (0);
				if (prev->c[idx] == ' ' || list->next->c[idx] == ' ')
					return (0);
			}
			idx++;
		}
		prev = list;
		list = list->next;
	}
	return (1);
}

t_list	*process_map_lines(int map_fd, t_cub *cub, size_t *max)
{
	t_list	*head;
	t_list	*tmp;
	char	*line;
	size_t	line_len;

	head = NULL;
	tmp = NULL;
	while (1)
	{
		line = get_next_line(map_fd, cub);
		if (!line)
			break ;
		if (*line == '\n' && head != NULL)
			return (NULL);
		line_len = ft_strlen(line);
		if (line_len > *max)
			*max = line_len;
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(line, cub), cub));
		replace_whitespace(line);
		transform_mtl(line, cub, &head);
	}
	if (!space_bound_check(tmp, cub))
		return (NULL);
	return (head);
}

void	extend_all_lines(t_list *head, size_t max, t_cub *cub)
{
	while (head)
	{
		extend_line(head, max, cub);
		head = head->next;
	}
}
