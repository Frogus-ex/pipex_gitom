/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:20:25 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/15 14:25:17 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error(int n_exit)
{
	if (n_exit == 1)
	{
		ft_putstr_fd("ERROR IN DECLARATION ! ", 2);
		ft_putstr_fd("./pipex_bonus here_doc Limiter cmd\n", 2);
	}
	exit (0);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	open_files(char *file, int in_or_out)
{
	int	fd;

	if (in_or_out == 0)
		fd = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (in_or_out == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		perror(file);
		close(fd);
		exit(1);
	}
	return (fd);
}

char	*is_path(char *path, char **env)
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
	char	**split_cmd;
	char	*exec;

	i = -1;
	all_path = ft_split(is_path("PATH", env), ':');
	split_cmd = ft_split(cmd, ' ');
	while (all_path[++i])
	{
		part_path = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(part_path, split_cmd[0]);
		free(part_path);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_tab(split_cmd);
			return (exec);
		}
		free(exec);
	}
	free_tab(all_path);
	free_tab(split_cmd);
	return (cmd);
}
