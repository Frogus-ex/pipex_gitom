/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:32:32 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/15 17:46:11 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	outfile_mode(char *av)
{
	int	open_mode;

	if (ft_strncmp (av, "here_doc", ft_strlen(av)) == 0)
		open_mode = 2;
	else
		open_mode = 1;
	return (open_mode);
}

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
