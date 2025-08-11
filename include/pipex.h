/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:17:08 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/11 12:25:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft.h"
# include "ft_printf.h"

typedef struct s_pipex
{
	int		is_here_doc;
	int		cmd_count;
	int		ac;
	int		fd_out;
	int		fd_in;
	char	*infile;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	char	**env;
	char	**av;
}	t_pipex;

int		main(int ac, char **av, char **env);
int		check_args(int ac);
int		pip_error(char *var, char *msg);
int		is_here_doc(char **av);
void	free_tab(char **tab);

#endif