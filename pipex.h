/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:16:55 by dagimeno          #+#    #+#             */
/*   Updated: 2024/08/05 20:22:18 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "Libft/libft.h"

void	charge_fds(int len, int ***fd);
void	charge_pid(int len, int **pid);
void	build_pipes(int ***fd, int index);
void	fork_pid(int **pid, int con);
void	finish(char *s, int err_key);
void	execute_command(char **argv, char **envp, int index);
void	close_fds(int ***fd, int len);
int		wait_pids(int **pid, int len);

#endif
