/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:44:17 by ymassiou          #+#    #+#             */
/*   Updated: 2024/06/10 11:34:36 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_trash	*gc_last(t_trash *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

void	gc_add(t_trash **head, t_trash *new)
{
	t_trash	*last;

	if (!new)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		last = gc_last(*head);
		if (last)
			last->next = new;
	}
}

t_trash	*gc_new(void *address, t_cub *data)
{
	t_trash	*new;

	new = malloc(sizeof(t_trash));
	if (!new)
	{
		terminate(data);
		ft_putstr_fd("Error: Appending new allocated buffer failed!", 2);
		gc_free(data);
		exit(EXIT_FAILURE);
	}
	new->to_free = address;
	new->next = NULL;
	return (new);
}

void	gc_free(t_cub *data)
{
	t_trash	*head;

	head = data->garbage;
	while (head)
	{
		if (head->to_free)
		{
			free(head->to_free);
			head->to_free = NULL;
		}
		head = head->next;
	}
}

void	*gc_malloc(size_t size, t_cub *data)
{
	void	*buffer;

	buffer = malloc(size);
	if (buffer == NULL)
	{
		terminate(data);
		ft_putstr_fd("Error: Allocating buffer failed!", 2);
		gc_free(data);
		exit(EXIT_FAILURE);
	}
	gc_add(&data->garbage, gc_new(buffer, data));
	return (buffer);
}
