/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:26:06 by dagimeno          #+#    #+#             */
/*   Updated: 2024/08/05 20:27:01 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_path(char **envp, char *command);
static char	*charge_path(char **addresses, char *command);
void		finish(char *s, int err_key);

void	execute_command(char **argv, char **envp, int index)
{
	char	**command;
	char	*path;

	command = ft_split(argv[index], ' ');
	path = find_path(envp, command[0]);
	if (!path)
	{
		if (write(2, argv[index], ft_strlen(argv[index])) < 0)
			exit(3);
		if (write(2, ": command not found\n", 20) < 0)
			exit(4);
		exit(127);
	}
	if (execve(path, command, envp) < 0)
		finish("execve", 16);
}

static char	*find_path(char **envp, char *command)
{
	char	*path;
	char	*aux;
	char	**addresses;
	int		i;

	if (!access(command, F_OK | X_OK))
		return (command);
	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i++], "PATH=", 5))
			break ;
	}
	aux = ft_strtrim(envp[--i], "PATH=");
	addresses = ft_split(aux, ':');
	free(aux);
	path = charge_path(addresses, command);
	i = 0;
	while (addresses[i])
		free(addresses[i++]);
	free (addresses);
	return (path);
}

static char	*charge_path(char **addresses, char *command)
{
	char	*path;
	char	*aux;
	int		i;

	i = 0;
	while (addresses[i])
	{
		aux = ft_strjoin("/", command);
		path = ft_strjoin(addresses[i++], aux);
		free(aux);
		if (!access(path, F_OK | X_OK))
			return (path);
		free(path);
	}
	return (0);
}

void	finish(char *s, int err_key)
{
	perror(s);
	exit(err_key);
}

void	fork_pid(int **pid, int con)
{
	(*pid)[con] = fork();
	if ((*pid)[con] < 0)
		finish("fork", 5);
}
