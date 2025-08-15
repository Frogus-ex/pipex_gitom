/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:48:44 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/15 17:36:17 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;

	if (!cmd || !*cmd)
	{
		ft_putstr_fd("pipex : command not found: (empty)\n", 2);
		exit(127);
	}
	split_cmd = ft_split(cmd, ' ');
	path = get_path(split_cmd[0], env);
	if (execve(path, split_cmd, env) == -1)
	{
		ft_putstr_fd("pipex : command not found: ", 2);
		ft_putendl_fd(split_cmd[0], 2);
		free_tab(split_cmd);
		exit(127);
	}
}

char	*is_here_doc(char **av, int *p_fd)
{
	char	*res;

	close(p_fd[0]);
	while (1)
	{
		write(1, "pipe heredoc> ", ft_strlen("here_doc> "));
		res = get_next_line(0);
		if (ft_strncmp(res, av[2], ft_strlen(res) - 1) == 0
			&& ft_strlen(res) - 1 == ft_strlen(av[2]))
		{
			free(res);
			close(p_fd[1]);
			get_next_line(-1);
			exit (0);
		}
		ft_putstr_fd(res, p_fd[1]);
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
	{
		close(p_fd[0]);
		close(p_fd[1]);
		exit (0);
	}
	if (!pid)
		is_here_doc(av, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		wait(NULL);
	}
}

void	fill_pipe(char *cmd, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit (0);
	pid = fork();
	if (pid == -1)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		exit(0);
	}
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		close(p_fd[1]);
		exec(cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
	}
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	fd_infile;
	int	fd_outfile;

	check_empty_args(ac, av);
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
	{
		if (ac < 6)
			ft_error(1);
		i = 3;
		here_doc_infile(av);
	}
	else
	{
		i = 2;
		fd_infile = open_files(av[1], 0);
		dup2(fd_infile, 0);
		close(fd_infile);
	}
	while (i < ac -2)
		fill_pipe(av[i++], env);
	fd_outfile = open_files(av[ac - 1], outfile_mode(av[1]));
	dup2(fd_outfile, 1);
	close(fd_outfile);
	exec(av[ac - 2], env);
}
