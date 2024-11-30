/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 09:48:27 by daniel            #+#    #+#             */
/*   Updated: 2024/11/29 17:57:43 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	finish(char *s, int err_key, t_params *params, char are_fds_open)
{
	unlink("eoirfngjksdfveaoi48");
	if (params)
		free_params(params, are_fds_open);
	perror(s);
	exit(err_key);
}

void	close_file_fd_and_finish(int file_fd, t_params *params, char *s)
{
	if (close(file_fd) < 0)
		finish("close", 7, params, 1);
	finish(s, 10, params, 1);
}

void	free_params(t_params *params, char are_fds_open)
{
	if (params->fd)
	{
		if (are_fds_open)
			close_fds(params);
		free_fds(params);
	}
	if (params->pid)
		free(params->pid);
	free(params);
}

void	free_command(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		free(command[i++]);
	free(command);
}

void	free_command_and_finish(char **command, char *s, t_params *params)
{
	free_command(command);
	finish(s, 23, params, 0);
}
