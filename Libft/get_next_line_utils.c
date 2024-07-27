/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:56:02 by dagimeno          #+#    #+#             */
/*   Updated: 2024/03/20 17:39:00 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_len(t_buffer *list);
void	record_first_line(t_buffer **list);
void	*ft_calloc(size_t count, size_t size);
void	clean(t_buffer **list);

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

void	clean(t_buffer **list)
{
	t_buffer	*aux;
	t_buffer	*aux2;

	aux = *list;
	*list = NULL;
	while (aux)
	{
		aux2 = aux->next;
		free(aux->line);
		free(aux);
		aux = aux2;
	}
}
