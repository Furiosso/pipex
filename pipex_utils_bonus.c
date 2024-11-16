/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:25:06 by dagimeno          #+#    #+#             */
/*   Updated: 2024/08/06 20:57:35 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_input(int argc, char **argv)
{
	if (argc < 5 || (argc == 5 && !ft_strncmp(argv[1], "here_doc", 8)))
	{
		if (write(2, "Please check the format\n", 25) < 0)
			finish ("write", 2);
		exit (1);
	}
}

void	free_fds(int ***fd, int len)
{
	int	con;

	con = 0;
	while (con < len)
		free((*fd)[con++]);
	free(*fd);
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
