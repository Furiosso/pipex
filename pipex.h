/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:16:55 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/16 18:11:39 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "Libft/libft.h"

typedef struct s_params
{
	int		**fd;
	int		argc;
	char	**argv;
	char	**envp;
	pid_t	*pid;
	int		f_num;
	int		p_num;
	int		index_first_argument;
	char	is_here_doc;
}				t_params;

void	build_pipes(t_params *params);
void	call_check_input(t_params *params);
void	charge_fds(t_params *params);
void	close_fds(t_params *params);
void	close_file_fd_and_finish(int file_fd, t_params *params, char *s);
void	charge_pid(t_params *params);
void	execute_command(int index, t_params *params);
void	fill_params(t_params *params, char **envp);
void	fork_pid(t_params *params, int con);
void	finish(char *s, int err_key, t_params *params);
void	free_fds(t_params *params);
int		wait_pids(t_params *params);

#endif
