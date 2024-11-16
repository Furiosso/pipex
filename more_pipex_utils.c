/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_pipex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:18:57 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/15 17:16:09 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	finish(char *s, int err_key)
{
	perror(s);
	exit(err_key);
}

void	fork_pid(pid_t **pid, int con)
{
	(*pid)[con] = fork();
	if ((*pid)[con] < 0)
		finish("fork", 5);
}

void	free_fds(int **fd, int len)
{
	int	con;

	con = 0;
	while (con < len)
		free(fd[con++]);
	free(fd);
}
