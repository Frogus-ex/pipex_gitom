/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:14:11 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/15 17:48:50 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_empty_args(int ac, char **av)
{
	int	i;

	i = 0;
	while (ac > i)
	{
		if (ft_strlen(av[i]) == 0)
		{
			ft_putstr_fd("error : one of the args is empty\n", 2);
			exit(0);
		}
		i++;
	}
}
