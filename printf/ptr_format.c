/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:05:19 by tlorette          #+#    #+#             */
/*   Updated: 2025/05/19 13:35:31 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ptr_format(char c)
{
	int		i;
	char	*format;

	i = 0;
	format = "cspdiuxX%";
	while (format[i])
	{
		if (format[i] == c)
			return (1);
		else
			i++;
	}
	return (-1);
}
