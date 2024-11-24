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

static int	manage_processes(t_params *params);
static void	open_input_file(char *file, t_params *params);
static void	standard_procedure(t_params *params, int index);
static void	open_output_file(char *file, t_params *params, int index);

int	main(int argc, char **argv, char **envp)
{
	t_params	*params;
	int			exit_code;

	params = ft_calloc(1, sizeof(t_params));
	if (!params)
		finish("ft_calloc", 1, NULL);
	params->argc = argc;
	params->argv = argv;
	call_check_input(params);
	fill_params(params, envp);
	charge_fds(params);
	build_pipes(params);
	exit_code = manage_processes(params);
	free_fds(params);
	free(params);
	return (exit_code);
}

static int	manage_processes(t_params *params)
{
	int		i;
	int		exit_code;

	charge_pid(params);
	i = -1;
	while (++i < params->p_num)
	{
		fork_pid(params, i);
		if (params->pid[i] == 0)
		{
			if (i == 0)
				open_input_file(params->argv[1], params);
			else if (i == params->f_num)
				open_output_file(params->argv[params->argc - 1], params, i - 1);
			else
				standard_procedure(params, i - 1);
			close_fds(params);
			execute_command(params->index_first_argument + i, params);
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

	if (params->is_here_doc)
		file_fd = open("eoirfngjksdfveaoi48", O_RDONLY, 0777);
	else
		file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
		finish(file, 14, params);
	if (dup2(file_fd, 0) < 0)
		close_file_fd_and_finish(file_fd, params, "dup2");
	if (dup2(params->fd[0][1], 1) < 0)
		close_file_fd_and_finish(file_fd, params, "dup2");
	if (close(file_fd) < 0)
		finish("close", 15, params);
	if (params->is_here_doc)
		unlink("eoirfngjksdfveaoi48");
}

static void	standard_procedure(t_params *params, int index)
{
	int	con;

	con = 0;
	while (con < 2)
	{
		if (dup2(params->fd[index++][con], con) < 0)
			finish("dup2", 18, params);
		con++;
	}
}

static void	open_output_file(char *file, t_params *params, int index)
{
	int	file_fd;

	if (params->is_here_doc)
		file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd < 0)
		finish(file, 16, params);
	if (dup2(file_fd, 1) < 0)
		close_file_fd_and_finish(file_fd, params, "dup2");
	if (dup2(params->fd[index][0], 0) < 0)
		close_file_fd_and_finish(file_fd, params, "dup2");
	if (close(file_fd) < 0)
		finish("close", 17, params);
}
