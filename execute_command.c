/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:26:06 by dagimeno          #+#    #+#             */
/*   Updated: 2024/12/01 12:44:43 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_path(char **envp, char *command);
static char	*charge_path(char **addresses, char *command);
static void	free_addresses(char **addresses);

void	execute_command(int index, t_params *params, int pindex)
{
	char	**command;
	char	*path;

	if (!ft_strlen(params->argv[index]))
		finish("''", 22, params, 0);
	command = ft_split(params->argv[index], ' ');
	path = find_path(params->envp, command[0]);
	if (!path)
	{
		if (write(2, command[0], ft_strlen(command[0])) < 0)
			free_command_and_finish(command, "write", params);
		free_command(command);
		if (write(2, ": command not found\n", 20) < 0)
			finish("write", 19, params, 1);
		if (params->pid[pindex] == 0)
			free_params(params, 0);
		exit(127);
	}
	if (execve(path, command, params->envp) < 0)
	{
		free(path);
		finish("execve", 20, params, 1);
	}
}

static char	*find_path(char **envp, char *command)
{
	char	*path;
	char	*aux;
	char	**addresses;
	int		i;

	if (!access(command, F_OK | X_OK) && ft_strchr(command, '/'))
		return (command);
	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i++], "PATH=", 5))
		{
			aux = ft_strtrim(envp[--i], "PATH=");
			addresses = ft_split(aux, ':');
			free(aux);
			path = charge_path(addresses, command);
			free_addresses(addresses);
			break ;
		}
	}
	if (!path && !access(command, F_OK | X_OK))
		return (command);
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

static void	free_addresses(char **addresses)
{
	int	i;

	i = 0;
	while (addresses[i])
		free(addresses[i++]);
	free(addresses);
}
