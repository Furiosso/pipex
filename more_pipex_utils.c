/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_pipex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:18:57 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/16 19:06:52 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_input(t_params *params);

void	fork_pid(t_params *params, int con)
{
	params->pid[con] = fork();
	if ((params->pid)[con] < 0)
		finish("fork", 13, params);
}

void	free_fds(t_params *params)
{
	int	con;

	con = 0;
	while (con < params->f_num)
		free(params->fd[con++]);
	free(params->fd);
}

void	fill_params(t_params *params, char **envp)
{
	params->envp = envp;
	if (params->is_here_doc)
	{
		params->index_first_argument = 3;
		params->f_num = params->argc - 5;
		params->p_num = params->argc - 4;
		get_input(params);
		return ;
	}
	params->index_first_argument = 2;
	params->f_num = params->argc - 4;
	params->p_num = params->argc - 3;
}

static void	get_input(t_params *params)
{
	int		file_fd;
	char	*line;

	unlink("eoirfngjksdfveaoi48");
	file_fd = open("eoirfngjksdfveaoi48", O_CREAT | O_WRONLY, 0777);
	if (file_fd < 0)
		finish("eoirfngjksdfveaoi48", 6, params);
	ft_printf("> ");
	line = get_next_line(0);
	if (!line)
		close_file_fd_and_finish(file_fd, params, "get_next_line");
	while (ft_strncmp(line, params->argv[2], ft_strlen(params->argv[2])))
	{
		if (write(file_fd, line, ft_strlen(line)) < 0)
			close_file_fd_and_finish(file_fd, params, "get_next_line");
		free(line);
		ft_printf("> ");
		line = get_next_line(0);
		if (!line)
			close_file_fd_and_finish(file_fd, params, "get_next_line");
	}
	free(line);
	if (close(file_fd) < 0)
		finish("close", 8, params);
}
