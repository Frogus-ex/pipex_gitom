/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:17:08 by tlorette          #+#    #+#             */
/*   Updated: 2025/08/12 16:24:20 by tlorette         ###   ########.fr       */
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

int		main(int ac, char **av, char **env);
int		open_files(char *file, int in_or_out);
void	ft_error(int n_exit);
void	free_tab(char **tab);
char	*is_path(char *path, char **env);
char	*get_path(char *cmd, char **env);

#endif