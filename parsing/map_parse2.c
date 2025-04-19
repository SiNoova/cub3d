/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:29:54 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/08 16:12:52 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	transform_mtl(char *line, t_cub *cub, t_list **head)
{
	t_list	*new;

	new = NULL;
	if (*line && !empty_line(line))
	{
		line = ft_substr(line, 0, ft_strlen(line) - 1, cub);
		new = ft_lstnew(line, cub);
		ft_lstadd_back(head, new);
	}
}

void	replace_whitespace(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			line[i] = '1';
		i++;
	}
}

void	extend_line(t_list *node, size_t max, t_cub *cub)
{
	size_t	line_len;
	char	*new_line;
	size_t	i;

	line_len = ft_strlen(node->c);
	if (line_len < max)
	{
		new_line = gc_malloc(max - line_len + 1, cub);
		i = 0;
		while (i < max - line_len)
		{
			new_line[i] = 'X';
			i++;
		}
		new_line[max - line_len] = '\0';
		node->c = ft_strjoin(node->c, new_line, cub);
	}
}

int	check_adjacent_x(t_list *head)
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
			if (idx && (tmp_str[idx] == '0'
					|| tmp_str[idx] == '2' || is_p(tmp_str[idx])))
			{
				if (tmp_str[idx - 1] == 'X' || tmp_str[idx + 1] == 'X'
					|| prev->c[idx] == 'X' || head->next->c[idx] == 'X')
					return (1);
			}
			idx++;
		}
		prev = head;
		head = head->next;
	}
	return (0);
}

void	replace_x_with_one(t_list *head)
{
	size_t	idx;

	while (head)
	{
		idx = 0;
		while (head->c[idx])
		{
			if (head->c[idx] == 'X')
				head->c[idx] = '1';
			idx++;
		}
		head = head->next;
	}
}
