/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:20:25 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/07 18:48:27 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	struct_init(t_pipex *pipex, char **av, int ac)
{
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		pipex->infile = NULL;
		pipex->is_here_doc = 1;
		pipex->outfile = av[ac - 1];
		pipex->cmd_count = ac - 4;
	}
	else
	{
		pipex->is_here_doc = 0;
		pipex->infile = av[1];
		pipex->outfile = av[ac - 1];
		pipex->cmd_count = ac - 3;
	}
}

void	open_infile(t_pipex *pipex)
{
	int	fd;

	fd = open(pipex->infile, O_RDONLY);
	if (fd == -1)
		perror(pipex->infile);
	pipex->fd_in = fd;
}

void	open_outfile(t_pipex *pipex)
{
	int	fd;

	fd = open(pipex->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror(pipex->outfile);
	else
		pipex->fd_out = fd;
}

void	get_env(char *name, char **env)
{
	int		i;
	int		j;
	char	sub;

	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(env[i])) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub)
		i++;
	}
	return (NULL);
}
