/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:15:54 by dagimeno          #+#    #+#             */
/*   Updated: 2024/08/05 20:16:45 by dagimeno         ###   ########.fr       */
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
	int	con;
	int	exit_code;

	if (argc != 5)
	{
		if (write(2, "Please, check the format\n", 25) < 0)
			return (2);
		return (1);
	}
	charge_fds(argc - 4, &fd);
	build_pipes(&fd, argc - 4);
	exit_code = manage_processes(argc, argv, envp, &fd);
	con = 0;
	while (con < argc - 4)
		free(fd[con++]);
	free(fd);
	return (exit_code);
}

static int	manage_processes(int argc, char **argv, char **envp, int ***fd)
{
	int	con;
	int	*pid;
	int	exit_code;

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
		finish("open", 0);
	if (dup2(file_fd, 0) < 0)
		finish("dup2", 7);
	if (dup2((*fd)[0][1], 1) < 0)
		finish("dup2", 8);
	if (close(file_fd) < 0)
		finish("close", 9);
}

static void	standard_procedure(int ***fd, int index)
{
	int	con;

	con = 0;
	while (con < 2)
	{
		if (dup2((*fd)[index++][con], con) < 0)
			finish("dup2", 14);
		con++;
	}
}

static void	open_output_file(char *file, int ***fd, int index)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd < 0)
		finish("open", 10);
	if (dup2(file_fd, 1) < 0)
		finish("dup2", 11);
	if (dup2((*fd)[index][0], 0) < 0)
		finish("dup2", 12);
	if (close(file_fd) < 0)
		finish("close", 13);
}
