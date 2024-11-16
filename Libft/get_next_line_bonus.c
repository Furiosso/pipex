/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:01:37 by dagimeno          #+#    #+#             */
/*   Updated: 2024/07/12 13:39:35 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char		*get_next_line(int fd);
static void	fill_list(int fd, t_buffer **list);
static void	handle_node(t_buffer **list, t_buffer *node);
static char	lf_is_found(t_buffer **list);
static void	charge_line(t_index **node, char *line);

char	*get_next_line(int fd)
{
	static t_index	*index = NULL;
	t_index			*node;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1
		|| BUFFER_SIZE > 0xffffffffffffffff || (read(fd, &line, 0)) < 0)
		return (clean_bonus(&index, fd));
	node = create_list(fd, &index);
	if (!node)
		return (clean_bonus(&index, fd));
	fill_list(fd, &node->list);
	if (!node->list)
		return (clean_bonus(&index, fd));
	line = ft_calloc((get_len(node->list) + 1), sizeof(char));
	if (!line)
		return (clean_bonus(&index, fd));
	charge_line(&node, line);
	if (!node->list)
		clean_bonus(&index, fd);
	return (line);
}

static void	fill_list(int fd, t_buffer **list)
{
	t_buffer	*node;

	while (!(lf_is_found(list)))
	{
		node = ft_calloc(1, sizeof(t_buffer));
		if (!node)
		{
			handle_node(list, NULL);
			return ;
		}
		node->line = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!node->line)
		{
			free(node);
			handle_node(list, NULL);
			return ;
		}
		if (read(fd, node->line, BUFFER_SIZE) < 1)
		{
			free(node->line);
			free(node);
			return ;
		}
		handle_node(list, node);
	}
}

static void	handle_node(t_buffer **list, t_buffer *node)
{
	t_buffer	*aux;

	if (!node)
	{
		while (*list)
		{
			aux = (*list)->next;
			free((*list)->line);
			free(*list);
			*list = aux;
		}
		return ;
	}
	if (!*list)
	{
		*list = node;
		return ;
	}
	aux = *list;
	while (aux->next)
		aux = aux->next;
	aux->next = node;
}

static char	lf_is_found(t_buffer **list)
{
	t_buffer	*aux;
	size_t		i;

	if (!*list)
		return (0);
	aux = *list;
	while (aux->next)
		aux = aux->next;
	i = 0;
	while (aux->line[i] && i < BUFFER_SIZE)
	{
		if (aux->line[i++] == 10)
			return (1);
	}
	return (0);
}

static void	charge_line(t_index **node, char *line)
{
	size_t		i;
	size_t		j;
	t_buffer	*list;
	t_buffer	*aux;

	list = (*node)->list;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->line[i] && i < BUFFER_SIZE)
		{
			line[j++] = list->line[i];
			if (list->line[i++] == 10 && list->line[i])
			{
				record_first_line(&list);
				return ;
			}
		}
		aux = list;
		list = aux->next;
		(*node)->list = list;
		free(aux->line);
		free(aux);
	}
}
