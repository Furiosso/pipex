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

#include "pipex_mandatory.h"

static void	check_arg(int argc)
{
	if (argc != 5)
	{
		if (write(2, "Please, check the format\n", 25) < 0)
			finish("write", 2);
		exit(1);
	}
}

void	call_check_arg(int argc)
{
	check_arg(argc);
}
