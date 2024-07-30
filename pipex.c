#include "pipex.h"

int	manage_processes(int argc, char **argv, char **envp, int ***fd);
void	open_input_file(char *file, int ***fd);
void	standard_procedure(int ***fd, int index);
void	open_output_file(char *file, int ***fd, int index);
void	close_fds(int ***fd, int len);

int	main(int argc, char **argv, char **envp)
{
	//char	**command;
	int	**fd;
	//int		*pid;
	int	con;
	int	exit_code;

	if (argc < 5)
	{
		if (write(2, "Please check the format\n", 24) < 0)
		       return (2);	
		return (1);
	}
	//fd = NULL;
	//pid = NULL;
	//if (argv[1] == "here_doc")
	//	here_doc();
	charge_fds(argc - 4, &fd/*, &pid*/);
	build_pipes(&fd, argc - 4);
	exit_code = manage_processes(argc, argv, envp, &fd);
	/*con = 0;
	while (con < argc - 3)
	{
		pid[con] = fork();
		if (pid[con] < 0)
			finish("fork failed", 5);
		if (pid[con] == 0)
		{		
			if (con == 0)
				open_input_file(argv[1], &fd);
			else if (con == argc - 4)
				open_output_file(argv[argc - 1], &fd, con - 1);
			else
				standard_procedure(&fd, con - 1);
			close_fds(&fd, argc - 4);
			command = ft_split(argv[con + 2], ' ');
			if (execve(find_path(envp, command[0]), command, envp) < 0)
				finish("execve failed", 16);
			exit (17);
		}
		con++;
	}*/
	//close_fds(&fd, argc - 4);
	//wait_pids(&pid, argc - 3);
	con = 0;
	while (con < argc - 4)
		free(fd[con++]);
	free(fd);
	//free(pid);
	return (exit_code);
}

int	manage_processes(int argc, char **argv, char **envp, int ***fd)
{
	int	con;
	int	*pid;
	int	exit_code;

	charge_pid(argc - 3, &pid);
	con = -1;
	while (++con < argc - 3)
	{
		fork_pid(&pid, con);
		//pid[con] = fork();
		//if (pid[con] < 0)
		//	finish("fork failed", 5);
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
			/*command = ft_split(argv[con + 2], ' ');
			if (execve(find_path(envp, command[0]), command, envp) < 0)
				finish("execve failed", 16);
			exit (17);*/
		}
		//con++;
	}
	close_fds(fd, argc - 4);
	exit_code = wait_pids(&pid, argc - 3);
	free(pid);
	return (exit_code);
}

void	open_input_file(char *file, int ***fd)
{
	int	file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
		finish("open_failed", 0);
	if (dup2(file_fd, 0) < 0)
		finish("dup2 failed", 7);
	if (dup2((*fd)[0][1], 1) < 0)
		finish("dup2 failed", 8);
	if (close(file_fd) < 0)
		finish("close failed", 9);
}

void	standard_procedure(int ***fd, int index)
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

void	open_output_file(char *file, int ***fd, int index)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd < 0)
		finish("open failed", 10);
	if (dup2(file_fd, 1) < 0)
		finish("dup2 failed", 11);
	if (dup2((*fd)[index][0], 0) < 0)
		finish("dup2 failed", 12);
	if (close(file_fd) < 0)
		finish("close failed", 13);
}
