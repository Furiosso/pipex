#include "pipex_bonus.h"

int		manage_here_doc(char **argv, char **envp, int **fd);
void		get_input(char **argv);
void	input_file(/*int file_fd, */int **fd);
void	output_file(char *file, int **fd);

void	here_doc(char **argv, char **envp)
{
	int	exit_code;
	int	*fd;

	fd = ft_calloc(sizeof(int), 2);
	if (!fd)
		finish("malloc", 123);
	if (pipe(fd) < 0)
		finish("pipe", 98);
	exit_code = manage_here_doc(argv, envp, &fd);
	free(fd);
	exit(exit_code);
}

int	manage_here_doc(char **argv, char **envp, int **fd)
{
	int	pid[2];
	int	exit_code;
	//int	file_fd;
	int	con;

	get_input(argv);
	pid[0] = fork();
	if (pid[0] < 0)
		finish("fork", 36);
	if (pid[0] == 0)
	{
		input_file(/*file_fd, */fd);
		execute_command(argv, envp, 3);
	}
	pid[1] = fork();
	if (pid[1] < 0)
		finish("fork", 122);
	if (pid[1] == 0)
	{
		output_file(argv[5], fd);
		execute_command(argv, envp, 4);
	}
	close((*fd)[0]);
	close((*fd)[1]);
	con = 0;
	while (con < 2)
		waitpid(pid[con++], &exit_code, 0);
	exit_code = WEXITSTATUS(exit_code);
	//unlink("tempfile");
	return(exit_code);
}

void	get_input(char **argv)
{
	int		file_fd;
	int		len;
	char	line[1024];

	file_fd = open("tempfile", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fd < 0)
		finish("open", 37);
	ft_bzero(line, 1024);
	ft_printf("> ");
	len = read(0, line, sizeof(line));
	if (len < 0)
		finish("read", 38);
	while (ft_strncmp(line, argv[2], ft_strlen(argv[2])))
	{
		if (write(file_fd, line, len) < 0)
			finish("write", 69);
		ft_printf("> ");
		len = read(0, line, sizeof(line));
		if (len < 0)
			finish("read", 39);
	}
	close(file_fd);
}

void	input_file(/*int file_fd, */int **fd)
{
	int	file_fd;
	int	con;

	file_fd = open("tempfile", O_RDONLY, 0777);
	if (file_fd < 0)
		finish("open", 94);
	if (dup2(file_fd, 0) < 0)
		finish("dup2", 126);
	if (dup2((*fd)[1], 1) < 0)
		finish("dup2", 125);
	if (close(file_fd) < 0)
		finish("close", 124);
	unlink("tempfile");
	con = 0;
	while (con < 2)
	{
		if (close((*fd)[con++]) < 0)
			finish("close", 123);
	}
}

void	output_file(char *file, int **fd)
{
	int	file_fd;
	int	con;

	file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file_fd < 0)
		finish("open", 121);
	if (dup2(file_fd, 1) < 0)
		finish("dup2", 120);
	if (dup2((*fd)[0], 0) < 0)
		finish("dup2", 119);
	if (close(file_fd) < 0)
		finish("close", 118);
	con = 0;
	while (con < 2)
	{
		if (close((*fd)[con++]) < 0)
			finish("close", 117);
	}
}
