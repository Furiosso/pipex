/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:42:06 by dagimeno          #+#    #+#             */
/*   Updated: 2024/03/23 13:17:49 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*get_next_line(int fd);
static void	fill_list(int fd, t_buffer **list);
static void	append_node(t_buffer **list, t_buffer *node);
static char	lf_is_found(t_buffer **list);
static void	charge_line(t_buffer **list, char *line);

char	*get_next_line(int fd)
{
	static t_buffer	*list = NULL;
	char			*line;
	size_t			len;

	if (fd < 0 || BUFFER_SIZE < 1
		|| BUFFER_SIZE > 0xffffffffffffffff || (read(fd, &line, 0)) < 0)
	{
		clean(&list);
		return (NULL);
	}
	fill_list(fd, &list);
	if (!list)
		return (NULL);
	len = get_len(list);
	line = ft_calloc((len + 1), sizeof(char));
	if (!line)
	{
		clean(&list);
		return (NULL);
	}
	charge_line(&list, line);
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
			clean(list);
			return ;
		}
		node->line = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!node->line)
		{
			free(node);
			clean(list);
			return ;
		}
		if (read(fd, node->line, BUFFER_SIZE) < 1)
		{
			free(node->line);
			free(node);
			return ;
		}
		append_node(list, node);
	}
}

static void	append_node(t_buffer **list, t_buffer *node)
{
	t_buffer	*aux;

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

static void	charge_line(t_buffer **list, char *line)
{
	size_t		i;
	size_t		j;
	t_buffer	*aux;

	j = 0;
	while (*list)
	{
		i = 0;
		while ((*list)->line[i] && i < BUFFER_SIZE)
		{
			line[j++] = (*list)->line[i];
			if ((*list)->line[i++] == 10 && (*list)->line[i])
			{
				record_first_line(list);
				return ;
			}
		}
		aux = *list;
		*list = aux->next;
		free(aux->line);
		free(aux);
	}
}
