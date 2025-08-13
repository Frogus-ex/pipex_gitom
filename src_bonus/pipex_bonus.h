/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:17:08 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/13 16:54:50 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

void	ft_error(int n_exit);
void	free_tab(char **tab);
int		open_files(char *file, int in_or_out);
char	*is_path(char *path, char **env);
char	*get_path(char *cmd, char **env);
void	exec(char *cmd, char **env);
char	*is_here_doc(char **av, int *p_fd);
void	fill_pipe(char *cmd, char **env);
int		main(int ac, char **av, char **env);

#endif