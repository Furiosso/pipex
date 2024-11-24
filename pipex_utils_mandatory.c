/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_mandatory.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:09:06 by dagimeno          #+#    #+#             */
/*   Updated: 2024/11/16 18:06:38 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_input(t_params *params)
{
	if (params->argc != 5)
	{
		if (write(2, "Please, check the format\n", 25) < 0)
			finish("write", 3, params);
		exit(2);
	}
}

void	call_check_input(t_params *params)
{
	check_input(params);
}
