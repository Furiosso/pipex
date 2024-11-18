/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_pipex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:18:57 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/16 19:06:52 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	finish(char *s, int err_key, t_params *params)
{
	if (params)
	{
		if (params->fd)
		{
			close_fds(params);
			free_fds(params);
		}
		if (params->pid)
			free(params->pid);
		free(params);
	}
	perror(s);
	exit(err_key);
}

void	fork_pid(t_params *params, int con)
{
	params->pid[con] = fork();
	if ((params->pid)[con] < 0)
		finish("fork", 5, params);
}

void	free_fds(t_params *params)
{
	int	con;

	con = 0;
	while (con < params->f_num)
		free(params->fd[con++]);
	free(params->fd);
}
