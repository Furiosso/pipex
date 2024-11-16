/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:18:05 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/15 17:42:55 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	charge_fds(int len, int ***fd)
{
	int	con;

	*fd = ft_calloc(len, sizeof(int *));
	if (!*fd)
		finish("malloc", 3);
	con = 0;
	while (con < len)
	{
		(*fd)[con] = ft_calloc(2, sizeof(int));
		if (!(*fd)[con])
			finish("malloc", 4);
		con++;
	}
}

void	build_pipes(int ***fd, int len)
{
	int	con;

	con = 0;
	while (con < len)
	{
		if (pipe((*fd)[con++]) < 0)
			finish("pipe", 6);
	}
}

void	charge_pid(int len, pid_t **pid)
{
	*pid = ft_calloc(len, sizeof(pid_t));
	if (!*pid)
		finish("malloc", 5);
}

void	close_fds(int ***fd, int len)
{
	int	con[2];

	con[0] = 0;
	while (con[0] < len)
	{
		con[1] = 0;
		while (con[1] < 2)
		{
			if (close((*fd)[con[0]][con[1]]) < 0)
				finish("close", 7);
			con[1]++;
		}
		con[0]++;
	}
}

int	wait_pids(pid_t **pid, int len)
{
	int	con;
	int	exit_code;

	con = 0;
	while (con < len)
	{
		if (waitpid((*pid)[con++], &exit_code, 0) < 0)
			finish("waitpid", 8);
		exit_code = WEXITSTATUS(exit_code);
	}
	return (exit_code);
}
