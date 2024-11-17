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

static int	manage_processes(int argc, char **argv, char **envp, int ***fd);
static void	open_input_file(char *file, int ***fd);
static void	standard_procedure(int ***fd, int index);
static void	open_output_file(char *file, int ***fd, int index);

int	main(int argc, char **argv, char **envp)
{
	int	**fd;
	int	exit_code;

	//call_check_arg(argc);
	charge_fds(argc - 4, &fd);
	build_pipes(&fd, argc - 4);
	exit_code = manage_processes(argc, argv, envp, &fd);
	free_fds(fd, argc - 4);
	return (exit_code);
}

static int	manage_processes(int argc, char **argv, char **envp, int ***fd)
{
	int		con;
	pid_t	*pid;
	int		exit_code;

	charge_pid(argc - 3, &pid);
	con = -1;
	while (++con < argc - 3)
	{
		fork_pid(&pid, con);
		if (pid[con] == 0)
		{
			if (con == 0)
				open_input_file(argv[1], fd);
			else if (con == argc - 4)
				open_output_file(argv[argc - 1], fd, con - 1);
			else
				standard_procedure(fd, con - 1);
			close_fds(fd, argc - 4);
			execute_command(argv, envp, con + 2);
		}
	}
	close_fds(fd, argc - 4);
	exit_code = wait_pids(&pid, argc - 3);
	free(pid);
	return (exit_code);
}

static void	open_input_file(char *file, int ***fd)
{
	int	file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
		finish("open", 9);
	if (dup2(file_fd, 0) < 0)
		finish("dup2", 10);
	if (dup2((*fd)[0][1], 1) < 0)
		finish("dup2", 11);
	if (close(file_fd) < 0)
		finish("close", 12);
}

static void	standard_procedure(int ***fd, int index)
{
	int	con;

	con = 0;
	while (con < 2)
	{
		if (dup2((*fd)[index++][con], con) < 0)
			finish("dup2", 13);
		con++;
	}
}

static void	open_output_file(char *file, int ***fd, int index)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd < 0)
		finish("open", 14);
	if (dup2(file_fd, 1) < 0)
		finish("dup2", 15);
	if (dup2((*fd)[index][0], 0) < 0)
		finish("dup2", 16);
	if (close(file_fd) < 0)
		finish("close", 17);
}
