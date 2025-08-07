/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:27:14 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/07 13:53:14 by tlorette         ###   ########.fr       */
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

int	is_here_doc(char **av, int ac)
{
	if (av[1] == "here_doc")
		return (0);
	return (-1);
}
