/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:23:02 by dagimeno          #+#    #+#             */
/*   Updated: 2024/08/06 20:57:32 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	manage_processes(int /*argc*/*params, char **argv, char **envp, int ***fd);
static void	open_input_file(char *file, int ***fd, int is_here_doc);
static void	standard_procedure(int ***fd, int index);
static void	open_output_file(char *file, int ***fd, int index, int is_here_doc);

//params[0]: indice del primer argumento(1 o 2);
//params[1]: numero de argumentos(argc - 3 o argc - 4);
//params[2]: indice del ultimo argumenot(argc - 1); 

int	main(int argc, char **argv, char **envp)
{
	int	**fd;
	int	params[3];
	int	exit_code;

	check_input(argc, argv);
	params[0] = 1;
	params[1] = argc - 3;
	params[2] = argc - 1;
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		get_input(argv);
		params[0] = 2;
		params[1] = argc - 4;
	}
	charge_fds(/*argc - 4*/params[1] - 1, &fd);
	build_pipes(&fd, /*argc - 4*/params[1] - 1);
	exit_code = manage_processes(/*argc*/params, argv, envp, &fd);
	free_fds(&fd, params[1] - 1);
	return (exit_code);
}

static int	manage_processes(int /*argc*/*params, char **argv, char **envp, int ***fd)
{
	int	con;
	int	*pid;
	int	exit_code;

	charge_pid(/*argc - 3*/params[1], &pid);
	con = -1;
	while (++con < /*argc - 3*/params[1])
	{
		fork_pid(&pid, con);
		if (pid[con] == 0)
		{
			if (con == 0)
				open_input_file(argv[/*1*/params[0]], fd, params[0]);
			else if (con == /*argc - 4*/params[1] - 1)
				open_output_file(argv[/*argc - 1*/params[2]], fd, con - 1, params[0]);
			else
				standard_procedure(fd, con - 1);
			close_fds(fd, /*argc - 4*/params[1] - 1);
			execute_command(argv, envp, con + /*2*/params[0] + 1);
		}
	}
	close_fds(fd, /*argc - 4*/params[1] - 1);
	exit_code = wait_pids(&pid, /*argc - 3*/params[1]);
	free(pid);
	return (exit_code);
}

static void	open_input_file(char *file, int ***fd, int is_here_doc)
{
	int	file_fd;

	if (is_here_doc == 2)
		file_fd = open("tempfile", O_RDONLY, 0777);
	else
		file_fd = open(file, O_RDONLY, 0777);
	if (file_fd < 0)
		finish("open", 0);
	if (dup2(file_fd, 0) < 0)
		finish("dup2", 7);
	if (dup2((*fd)[0][1], 1) < 0)
		finish("dup2", 8);
	if (close(file_fd) < 0)
		finish("close", 9);
	if (is_here_doc == 2)
		unlink("tempfile");
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

static void	open_output_file(char *file, int ***fd, int index, int is_here_doc)
{
	int	file_fd;

	if (is_here_doc == 2)
		file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
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
