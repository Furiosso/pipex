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

#include "pipex.h"

static void	check_input(t_params *params)
{
	int		argc;
	char	**argv;

	argc = params->argc;
	argv = params->argv;
	if (argc < 5 || (argc == 5 && !ft_strncmp(argv[1], "here_doc", 8)))
	{
		if (write(2, "Please check the format\n", 25) < 0)
			finish ("write", 5, NULL);
		exit (4);
	}
	if (!ft_strncmp(argv[1], "here_doc", 8))
		params->is_here_doc = 1;
}

void	call_check_input(t_params *params)
{
	check_input(params);
}
