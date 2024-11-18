/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:15:54 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/16 19:03:42 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	manage_processes(int n, char **argv, char **envp, t_params *params);
static void	open_input_file(char *file, t_params *params);
static void	standard_procedure(t_params *params, int index);
static void	open_output_file(char *file, t_params *params, int index);

int	main(int argc, char **argv, char **envp)
{
	t_params	*params;
	int			exit_code;

	call_check_arg(argc);
	params = ft_calloc(1, sizeof(t_params));
	if (!params)
		finish("ft_calloc", 99, NULL);
	params->f_num = argc - 4;
	params->p_num = argc - 3;
	charge_fds(params);
	build_pipes(params);
	exit_code = manage_processes(argc, argv, envp, params);
	free_fds(params);
	free(params);
	return (exit_code);
}

static int	manage_processes(int n, char **argv, char **envp, t_params *params)
{
	int		con;
	int		exit_code;

	charge_pid(params);
	con = -1;
	while (++con < params->p_num)
	{
		fork_pid(params, con);
		if (params->pid[con] == 0)
		{
			if (con == 0)
				open_input_file(argv[1], params);
			else if (con == params->f_num)
				open_output_file(argv[n - 1], params, con - 1);
			else
				standard_procedure(params, con - 1);
			close_fds(params);
			execute_command(argv, envp, con + 2, params);
		}
	}
	close_fds(params);
	exit_code = wait_pids(params);
	free(params->pid);
	return (exit_code);
}

static void	open_input_file(char *file, t_params *params)
{
	int	file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
		finish(file, 9, params);
	if (dup2(file_fd, 0) < 0)
	{
		if (close(file_fd) < 0)
			finish("close", 12, params);
		finish("dup2", 10, params);
	}
	if (dup2(params->fd[0][1], 1) < 0)
	{
		if (close(file_fd) < 0)
			finish("close", 12, params);
		finish("dup2", 11, params);
	}
	if (close(file_fd) < 0)
		finish("close", 12, params);
}

static void	standard_procedure(t_params *params, int index)
{
	int	con;

	con = 0;
	while (con < 2)
	{
		if (dup2(params->fd[index++][con], con) < 0)
			finish("dup2", 13, params);
		con++;
	}
}

static void	open_output_file(char *file, t_params *params, int index)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd < 0)
		finish(file, 14, params);
	if (dup2(file_fd, 1) < 0)
	{
		if (close(file_fd) < 0)
			finish("close", 15, params);
		finish("dup2", 11, params);
	}
	if (dup2(params->fd[index][0], 0) < 0)
	{
		if (close(file_fd) < 0)
			finish("close", 16, params);
		finish("dup2", 11, params);
	}
	if (close(file_fd) < 0)
		finish("close", 17, params);
}
