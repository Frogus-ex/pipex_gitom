/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:27:14 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/15 18:14:38 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(int n_exit)
{
	if (n_exit == 1)
	{
		ft_putstr_fd("ERROR IN DECLARATION ! PIPEX MUST BE DECLARED LIKE ", 2);
		ft_putstr_fd("THIS -> ./pipex infile cmd cmd outfile\n", 2);
		exit(0);
	}
}

void	exec(char	*cmd, char **env)
{
	char	**split_cmd;
	char	*path;

	if (!cmd || !*cmd)
	{
		ft_putstr_fd("pipex: command not found: (empty)\n", 2);
		exit(127);
	}
	split_cmd = ft_split(cmd, ' ');
	path = get_path(split_cmd[0], env);
	if (execve(path, split_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(split_cmd[0], 2);
		free_tab(split_cmd);
		exit(127);
	}
}

void	child(char	**av, int pip_fd[2], char **env)
{
	int	fd;

	close(pip_fd[0]);
	fd = open_files(av[1], 0);
	if (fd == -1)
	{
		close(pip_fd[1]);
		exit(1);
	}
	dup2(fd, 0);
	dup2(pip_fd[1], 1);
	close(pip_fd[1]);
	close(fd);
	exec(av[2], env);
}

void	parent(char **av, int pip_fd[2], char **env)
{
	int	fd;

	close(pip_fd[1]);
	fd = open_files(av[4], 1);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: failed to open output file\n", 2);
		close(pip_fd[0]);
		exit(1);
	}
	dup2(pip_fd[0], 0);
	dup2(fd, 1);
	close(pip_fd[0]);
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
	check_empty_args(ac, av);
	if (pipe(pip_fd) == -1)
		ft_error(1);
	pid1 = fork();
	if (pid1 == -1)
		exit(-1);
	if (pid1 == 0)
		child(av, pip_fd, env);
	pid2 = fork();
	if (pid2 == -1)
		exit(-1);
	if (pid2 == 0)
		parent(av, pip_fd, env);
	close(pip_fd[0]);
	close(pip_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
