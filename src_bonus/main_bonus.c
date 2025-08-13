/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:48:44 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/13 17:42:10 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;

	split_cmd = ft_split(cmd, ' ');
	path = get_path(split_cmd[0], env);
	if (execve(path, split_cmd, env) == -1)
	{
		ft_putstr_fd("pipex : command not found: ", 2);
		ft_putendl_fd(split_cmd[0], 2);
		free_tab(split_cmd);
		exit (0);
	}
}

char	*is_here_doc(char **av, int *p_fd)
{
	char	*res;

	close(p_fd[0]);
	while (1)
	{
		res = get_next_line(0);
		if (strncmp(res, av[2], ft_strlen(av[2])) == 0)
		{
			free(res);
			exit (0);
		}
		ft_putstr_fd(res, 1);
		free(res);
	}
}

void	here_doc_infile(char **av)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit (0);
	pid = fork();
	if (pid == -1)
		exit (0);
	if (!pid)
		is_here_doc(av, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		wait(NULL);
	}
}

void	fill_pipe(char *cmd, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		exec(cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	fd_infile;
	int	fd_outfile;

	if (ac < 5)
		ft_error(1);
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
	{
		if (ac < 6)
			ft_error(1);
		i = 3;
		fd_outfile = open_files(av[ac -1], 2);
		here_doc_infile(av);
	}
	else
	{
		i = 2;
		fd_infile = open_files(av[1], 0);
		fd_outfile = open_files(av[ac - 1], 1);
		dup2(fd_infile, 0);
	}
	while (i < ac -2)
		fill_pipe(av[i++], env);
	dup2(fd_outfile, 1);
	exec(av[ac - 2], env);
}
