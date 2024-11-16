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

void	build_pipes(int ***fd, int index);
void	call_check_arg(int argc);
void	charge_fds(int len, int ***fd);
void	close_fds(int ***fd, int len);
void	charge_pid(int len, pid_t **pid);
void	execute_command(char **argv, char **envp, int index);
void	fork_pid(pid_t **pid, int con);
void	finish(char *s, int err_key);
void	free_fds(int **fd, int len);
int		wait_pids(pid_t **pid, int len);

#endif
