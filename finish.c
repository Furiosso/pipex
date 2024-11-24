/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-24 09:48:27 by daniel            #+#    #+#             */
/*   Updated: 2024-11-24 09:48:27 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	finish(char *s, int err_key, t_params *params)
{
	unlink("tempfile");
	if (params->fd)
	{
		close_fds(params);
		free_fds(params);
	}
	if (params->pid)
		free(params->pid);
	free(params);
	perror(s);
	exit(err_key);
}

void	close_file_fd_and_finish(int file_fd, t_params *params, char *s)
{
	if (close(file_fd) < 0)
		finish("close", 12, params);
	finish(s, 10, params);
}
