/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:20:25 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/15 16:51:46 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		fd = open(file, O_RDONLY);
	if (in_or_out == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		return (-1);
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

char	**get_all_path(char **env)
{
	char	**all_path;
	char	*path_env;

	path_env = is_path("PATH", env);
	if (!path_env)
		return (NULL);
	all_path = ft_split(path_env, ':');
	if (!all_path)
		return (NULL);
	return (all_path);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**all_path;
	char	*part_path;
	char	**split_cmd;
	char	*exec;

	i = -1;
	all_path = get_all_path(env);
	split_cmd = ft_split(cmd, ' ');
	while (all_path[++i])
	{
		part_path = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(part_path, split_cmd[0]);
		free(part_path);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_tab(all_path);
			free_tab(split_cmd);
			return (exec);
		}
		free(exec);
	}
	free_tab(all_path);
	free_tab(split_cmd);
	return (cmd);
}
