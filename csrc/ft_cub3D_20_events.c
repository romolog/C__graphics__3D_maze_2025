/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3D_20_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:58:59 by rponomar          #+#    #+#             */
/*   Updated: 2025/04/24 17:18:39 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3D.h"
#include "ft_math.h"
#include "ft_mlx.h"
#include "mlx.h"
#include <assert.h>
#include <sys/time.h>

int	ft_event_red_button(t_tr *t)
{
	t->exit = 1;
	ft_cleanup(t);
	return (0);
}

static void	ft_update_move(int key, t_tr *t)
{
	if (key == MLX_W || key == MLX_S || key == MLX_A || key == MLX_D)
	{
		t->p->move_x = t->p->mxa + t->p->mxd + t->p->mxs + t->p->mxw;
		t->p->move_y = t->p->mya + t->p->myd + t->p->mys + t->p->myw;
	}
}

static void	ft_move_wsad_lr(int key, t_tr *t)
{
	if (key == MLX_W)
	{
		t->p->mxw = t->p->step * cos(t->p->d);
		t->p->myw = t->p->step * sin(t->p->d);
	}
	else if (key == MLX_S)
	{
		t->p->mxs = -t->p->step * cos(t->p->d);
		t->p->mys = -t->p->step * sin(t->p->d);
	}
	else if (key == MLX_A)
	{
		t->p->mxa = t->p->step * cos(t->p->d + M_PI_2);
		t->p->mya = t->p->step * sin(t->p->d + M_PI_2);
	}
	else if (key == MLX_D)
	{
		t->p->mxd = t->p->step * cos(t->p->d - M_PI_2);
		t->p->myd = t->p->step * sin(t->p->d - M_PI_2);
	}
	else if (key == MLX_LEFT)
		t->p->rotate = -t->p->rad;
	else if (key == MLX_RIGHT)
		t->p->rotate = t->p->rad;
}

int	ft_event_key_press(int key, t_tr *t)
{
	if (key == MLX_ESC)
	{
		t->exit = 1;
		ft_cleanup(t);
	}
	ft_move_wsad_lr(key, t);
	ft_update_move(key, t);
	return (0);
}

int	ft_event_key_release(int key, t_tr *t)
{
	if (key == MLX_W)
	{
		t->p->mxw = 0;
		t->p->myw = 0;
	}
	else if (key == MLX_S)
	{
		t->p->mxs = 0;
		t->p->mys = 0;
	}
	else if (key == MLX_A)
	{
		t->p->mxa = 0;
		t->p->mya = 0;
	}
	else if (key == MLX_D)
	{
		t->p->mxd = 0;
		t->p->myd = 0;
	}
	else if (key == MLX_LEFT || key == MLX_RIGHT)
		t->p->rotate = 0.0;
	ft_update_move(key, t);
	return (0);
}
