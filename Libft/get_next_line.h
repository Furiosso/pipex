/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:41:43 by dagimeno          #+#    #+#             */
/*   Updated: 2024/07/12 13:51:59 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>

typedef struct s_line
{
	char			*line;
	struct s_line	*next;
}				t_buffer;

char	*get_next_line(int fd);
size_t	get_len(t_buffer *list);
void	record_first_line(t_buffer **list);
void	*ft_calloc(size_t count, size_t size);
void	clean(t_buffer **list);

#endif
