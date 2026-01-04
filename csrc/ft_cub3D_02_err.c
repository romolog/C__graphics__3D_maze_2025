/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_02_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:08:04 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/26 14:16:38 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell_colors.h"
#include "libft.h"
#include "ft_cub3D.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_check_args(int argc, char **argv, t_tr *t)
{
	int		i;
	char	*ptr;
	char	*msg;

	if (argc == 2)
	{
		i = 0;
		ptr = ft_strrchr(argv[1], '/');
		if (ptr)
		{
			ptr++;
			i = ft_strlen(ptr) - 4;
		}
		if (i > 0 && !ft_strncmp((ptr + i), ".cub", 5))
			return ;
	}
	ft_write(2, "Error\n", 6);
	ft_write(2, YELLOW_BOLD_HIGH, ft_strlen(YELLOW_BOLD_HIGH));
	ft_write(2, t->prog, ft_strlen(t->prog));
	ft_write(2, ": ", 2);
	ft_write(2, YELLOW_NORM, ft_strlen(YELLOW_NORM));
	msg = "error arg: requires one arg: map file *?.cub\n";
	ft_write(2, msg, ft_strlen(msg));
	ft_write(2, DEFAULT_COLOR, ft_strlen(DEFAULT_COLOR));
	exit(EXIT_FAILURE);
}

void	ft_err(int condition, t_tr *t, char *file_name, int line)
{
	if (!condition)
	{
		t->err = NULL;
		return ;
	}
	ft_write(2, "Error\n", 6);
	if (DEBUG_MODE)
	{
		ft_write(2, YELLOW_NORM, ft_strlen(YELLOW_NORM));
		(void) ft_printf("%s : line %d : errno %d : ", file_name, line, errno);
	}
	ft_write(2, YELLOW_BOLD_HIGH, ft_strlen(YELLOW_BOLD_HIGH));
	ft_write(2, t->prog, ft_strlen(t->prog));
	ft_write(2, ": ", 2);
	ft_write(2, YELLOW_NORM, ft_strlen(YELLOW_NORM));
	ft_write(2, t->err, ft_strlen(t->err));
	if (!t->err)
	{
		ft_write(2, strerror(errno), ft_strlen(strerror(errno)));
		ft_write(2, "\n", 1);
	}
	ft_write(2, DEFAULT_COLOR, ft_strlen(DEFAULT_COLOR));
	t->exit = 1;
	t->exit_status = EXIT_FAILURE;
	ft_cleanup(t);
}
