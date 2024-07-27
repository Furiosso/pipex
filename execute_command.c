#include "pipex.h"

char	*find_path(char **envp, char *command);
void	finish(char *s, int err_key);

void	execute_command(char **argv, char **envp, int index)
{
	char	**command;
	char	*path;

	command = ft_split(argv[index], ' ');
	path = find_path(envp, command[0]);
	if (!path)
		finish(ft_strjoin(command[0], ": command not found"), 127);
	printf("Executing command: %s with path: %s\n", command[0], path);
	if (execve(path/*find_path(envp, command[0])*/, command, envp) < 0)
		finish("execve failed", 16);
	//finish("command not found", 17);
}

char	*find_path(char **envp, char *command)
{
	char	*path;
	char	**addresses;
	int		i;
	char	flag;

	if (!access(command, F_OK))
		return (command);
	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i++], "PATH=", 5))
			break ;
	}
	addresses = ft_split(ft_strtrim(envp[--i], "PATH="), ':');
	//addresses[0] = ft_strtrim(addresses[0], "PATH=");
	flag = 1;
	i = 0;
	while (addresses[i])
	{
		path = ft_strjoin(addresses[i++], ft_strjoin("/", command));
		if (!access(path, F_OK))
		{
			flag = 0;
			break ;
		}
		free(path);
	}
	if (flag)
		return (0);
		//finish("command not found", 26);
	/*i = 0;
	while (addresses[i])
		free(addresses[i++]);
	free (addresses);*/
	return (path);
}

void	finish(char *s, int err_key)
{
	perror(s);
	exit(err_key);
}
