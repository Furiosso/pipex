#include "pipex.h"

int		manage_here_doc(char **argv/*, char **envp, int ***fd*/);
void	get_input(/*char **argv*/);

void	here_doc(/*int argc, */char **argv/*, char **envp*/, int ***fd)
{
	//int	con;
	int	exit_code;

	charge_fds(1, fd);
	build_pipes(fd, 1);
	exit_code = manage_here_doc(argv/*, envp, fd*/);
	/*con = 0;
	while (con < 2)
		free((*fd)[con++]);
	free(*fd);*/
	exit(exit_code);
}

int	manage_here_doc(char **argv/*, char **envp, int ***fd*/)
{
	int	*pid;
	int	exit_code;

	charge_pid(2, &pid);
	pid[0] = fork();
	if (pid[0] < 0)
		finish("fork", 36);
	if (pid[0] == 0)
		get_input(argv);
	exit_code = 0;
	return(exit_code);
}

void	get_input(/*char **argv*/)
{
	//int		file_fd;
	int		len;
	char	line[1024];

	//line = ft_calloc(sizeof(char), 1024);
	//file_fd = open("tempfile", O_CREAT, 0777);
	//if (file_fd < 0)
	//	finish("open", 37);
	ft_printf("> ");
	len = read(0, line, sizeof(line));
	ft_printf("len = %d\n", len);
	if (len < 0)
		finish("read", 38);
	/*while (ft_strncmp(line, argv[2], ft_strlen(argv[2])))
	{
		write(file_fd, line, len);
		ft_printf("> ");
		len = read(0, line, sizeof(line));
		if (len < 0)
			finish("read", 39);
	}*/
}
