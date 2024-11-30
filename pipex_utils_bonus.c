/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:25:06 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/30 13:45:58 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_input(t_params *params)
{
	int		len;
	char	*arg;

	len = params->argc;
	arg = params->argv[1];
	if (len < 5 || (len == 5 && !ft_strncmp(arg, "here_doc", ft_strlen(arg))))
	{
		if (write(2, "Please check the format\n", 25) < 0)
			finish ("write", 5, params, 0);
		free(params);
		exit (4);
	}
	if (!ft_strncmp(arg, "here_doc", ft_strlen(arg)))
		params->is_here_doc = 1;
}

void	call_check_input(t_params *params)
{
	check_input(params);
}
