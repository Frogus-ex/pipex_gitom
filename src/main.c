/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:27:14 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/13 10:18:45 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_here_doc(char **av)
{
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		return (0);
	return (-1);
}

void	exec(char	*cmd, char **env)
{
	char	**split_cmd;
	char	*path;

	split_cmd = ft_split(cmd, ' ');
	path = get_path(split_cmd[0], env);
	if (execve(path, split_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(split_cmd[0], 2);
		free_tab(split_cmd);
		exit (0);
	}
}

void	child(char	**av, int pip_fd[2], char **env)
{
	int	fd;

	fd = open_files(av[1], 0);
	dup2(fd, 0);
	dup2(pip_fd[1], 1);
	close(pip_fd[0]);
	close(pip_fd[1]);
	close(fd);
	exec(av[2], env);
}

void	parent(char **av, int pip_fd[2], char **env)
{
	int	fd;

	fd = open_files(av[4], 1);
	dup2(pip_fd[0], 0);
	dup2(fd, 1);
	close(pip_fd[0]);
	close(pip_fd[1]);
	close(fd);
	exec(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		pip_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		ft_error(1);
	if (pipe(pip_fd) == -1)
		ft_error(-1);
	pid1 = fork();
	if (pid1 == -1)
		exit(-1);
	if (!pid1)
		child(av, pip_fd, env);
	pid2 = fork();
	if (pid2 == -1)
		exit(-1);
	if (!pid2)
		parent(av, pip_fd, env);
	close(pip_fd[0]);
	close(pip_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
