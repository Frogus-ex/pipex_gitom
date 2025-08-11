/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:27:14 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/11 11:51:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pip_error(char *var, char *msg)
{
	ft_putstr_fd(var, 2);
	ft_putstr_fd(" : ", 2);
	ft_putstr_fd(msg, 2);
	return (-1);
}

int	is_here_doc(char **av)
{
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		return (0);
	return (-1);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = -1;
	while(tab[++i])
		free(tab[i]);
	free(tab);
}