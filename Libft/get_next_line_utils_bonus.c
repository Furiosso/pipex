/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:02:24 by dagimeno          #+#    #+#             */
/*   Updated: 2024/07/12 13:41:46 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_index	*create_list(int fd, t_index **index);
size_t	get_len(t_buffer *list);
void	record_first_line(t_buffer **list);
void	*ft_calloc(size_t count, size_t size);
char	*clean_bonus(t_index **index, int fd);

t_index	*create_list(int fd, t_index **index)
{
	t_index	*node;
	t_index	*aux;

	aux = *index;
	while (aux)
	{
		if (aux->fd == fd)
			return (aux);
		aux = aux->next;
	}
	node = ft_calloc(1, sizeof(t_index));
	if (!node)
		return (NULL);
	if (*index)
	{
		aux = *index;
		while (aux->next)
			aux = aux->next;
		aux->next = node;
		node->previous = aux;
	}
	else
		*index = node;
	node->fd = fd;
	return (node);
}

size_t	get_len(t_buffer *list)
{
	size_t		i;
	size_t		cont;

	cont = 0;
	while (list)
	{
		i = 0;
		while (list->line[i])
		{
			cont++;
			if (list->line[i++] == 10)
				break ;
		}
		list = list->next;
	}
	return (cont);
}

void	record_first_line(t_buffer **list)
{
	size_t	i;
	size_t	mark;

	i = 0;
	mark = 0;
	while ((*list)->line[i])
	{
		if ((*list)->line[i++] == 10)
		{
			mark = i;
			break ;
		}
	}
	i = 0;
	while ((*list)->line[mark])
		(*list)->line[i++] = (*list)->line[mark++];
	while ((*list)->line[i])
		(*list)->line[i++] = 0;
}

char	*clean_bonus(t_index **index, int fd)
{
	t_index		*temp;
	t_buffer	*aux;

	temp = *index;
	while (temp && temp->fd != fd)
		temp = temp->next;
	if (!temp)
		return (NULL);
	while (temp->list)
	{
		aux = temp->list->next;
		free(temp->list->line);
		free(temp->list);
		temp->list = aux;
	}
	if (temp->previous)
		temp->previous->next = temp->next;
	else
		*index = temp->next;
	if (temp->next)
		temp->next->previous = temp->previous;
	free(temp);
	return (NULL);
}
