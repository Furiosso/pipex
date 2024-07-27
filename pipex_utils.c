#include "pipex.h"

void	charge_fds(int len, int ***fd/*, int **pid*/)
{
	int	con;

	*fd = ft_calloc(len, sizeof(int *));
	if (!*fd)
		finish("malloc failed", 2);
	con = 0;
	while (con < len)
	{
		(*fd)[con] = ft_calloc(2, sizeof(int));
		if (!(*fd)[con])
		{
			//while (con)
			//	free((*fd)[--con]);
			//free(*fd);
			finish("malloc failed", 3);
		}
		con++;
	}
}

void	charge_pid(int len, int **pid)
{
	*pid = ft_calloc(len, sizeof(int));
	if (!*pid)
	//{
		//while (con)
		//	free((*fd)[--con]);
		//free(*fd);
		finish("malloc failed", 4);
	//}
}

void	build_pipes(int ***fd, int len)
{
	int	con;

	con = 0;
	while (con < len)
	{
		if (pipe((*fd)[con++]) < 0)
			finish("pipe failed", 4);
	}
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
				finish("close failed", 15);
			con[1]++;
		}
		con[0]++;
	}
}

int	wait_pids(int **pid, int len)
{
	int	con;
	int	exit_code;

	//exit_code = 0;
	con = 0;
	while (con < len)
	{
		if (waitpid((*pid)[con++], &exit_code, 0) < 0)
			finish("waitpid failed", 18);
        exit_code = WEXITSTATUS(exit_code);
		//exit_code = WEXITSTATUS(exit_code);
	}
	//exit_code = WEXITSTATUS(exit_code);
	return (exit_code);
}
