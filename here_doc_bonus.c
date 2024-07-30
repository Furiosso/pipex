#include "pipex.h"

void	here_doc(int argc, char **argv, char **envp)
{
	int	*fd;
	int	con;
	int	exit_code;

	charge_fds(1, &fd);
	build_pipes,(&fd, 1);
	exit_code = manage_here_doc(argc, argv, envp, &fd);
	con = 0;
	while (con < 2)
		free(fd[con++]);
	free(fd);
	exit(exit_code);
}

int	manage_here_doc(int argc, int **argv, int **envp, int ***fd)
{
	int	*pid;
	int	line;
	int	exit_code;
	int	buffer[1024];

	charge_pid*(2, &pid);
	pid[0] = fork();
	if (pid[0] < 0)
		finish("fork", 36);
	if (pid[0] == 0)
	{
		line = read(0, buffer);
	}
}
