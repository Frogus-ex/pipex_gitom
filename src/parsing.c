/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:20:25 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/11 12:33:26 by marvin           ###   ########.fr       */
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

char	*get_env(char *path, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, path, ft_strlen(env[i])) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**all_path;
	char	*part_path;
	char	**s_cmd;
	char	*exec;

	i = -1;
	all_path = ft_split(get_env("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (all_path[++i])
	{
		part_path = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(part_path, s_cmd[0]);
		free(part_path);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_tab(s_cmd);
			return (exec);
		}
		free(exec);
	}
	free_tab(all_path);
	free_tab(s_cmd);
	return (cmd);
}
