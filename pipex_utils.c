/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:18:05 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/16 19:09:42 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	charge_fds(t_params *params)
{
	int	con;

	params->fd = ft_calloc(params->f_num, sizeof(int *));
	if (!params->fd)
		finish("malloc", 9, params);
	con = 0;
	while (con < params->f_num)
	{
		params->fd[con] = ft_calloc(2, sizeof(int));
		if (!params->fd[con])
			finish("malloc", 10, params);
		con++;
	}
}

void	build_pipes(t_params *params)
{
	int	con;

	con = 0;
	while (con < params->f_num)
	{
		if (pipe(params->fd[con++]) < 0)
			finish("pipe", 11, params);
	}
}

void	charge_pid(t_params *params)
{
	params->pid = ft_calloc(params->p_num, sizeof(pid_t));
	if (!params->pid)
		finish("malloc", 12, params);
}

void	close_fds(t_params *params)
{
	int	con[2];

	con[0] = 0;
	while (con[0] < params->f_num)
	{
		con[1] = 0;
		while (con[1] < 2)
		{
			if (close(params->fd[con[0]][con[1]]) < 0)
				finish("close", 19, params);
			con[1]++;
		}
		con[0]++;
	}
}

int	wait_pids(t_params *params)
{
	int	con;
	int	exit_code;

	con = 0;
	while (con < params->p_num)
	{
		if (waitpid(params->pid[con++], &exit_code, 0) < 0)
			finish("waitpid", 21, params);
		exit_code = WEXITSTATUS(exit_code);
	}
	return (exit_code);
}
