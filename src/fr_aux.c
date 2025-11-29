/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlamiel- <xlamiel-@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 23:18:38 by xlamiel-          #+#    #+#             */
/*   Updated: 2025/11/29 02:47:37 by xlamiel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_color(int iter, t_fractal *fractal)
{
	int	color;

	color = 0;
	if (fractal->color_i == 0)
		color = map(iter, (t_range){BLACK, WHITE},
				(t_range){0.0, fractal->iterations_definition});
	else if (fractal->color_i == 1)
		color = map(iter, (t_range){BLACK, RED},
				(t_range){0.0, fractal->iterations_definition});
	else if (fractal->color_i == 2)
		color = map(iter, (t_range){NEON_PINK, ELECTRIC_LIME},
				(t_range){0.0, fractal->iterations_definition});
	else if (fractal->color_i == 3)
		color = map(iter, (t_range){TRIPPY_PURPLE, RADIOACTIVE_YELLOW},
				(t_range){0.0, fractal->iterations_definition});
	return (color);
}

void	up_iterations_definition(t_fractal *fractal)
{
	fractal->iterations_definition += 10;
	if (fractal->iterations_definition > 600)
		fractal->iterations_definition = 600;
	return ;
}

void	down_iterations_definition(t_fractal *fractal)
{
	fractal->iterations_definition -= 10;
	if (fractal->iterations_definition < 20)
		fractal->iterations_definition = 20;
	return ;
}

void	zoom_limits(t_fractal *fractal, double zoom_factor)
{
	if ((fractal->zoom * zoom_factor) < 1e-12)
		fractal->zoom = 1e-12;
	else if ((fractal->zoom * zoom_factor) > 20.0)
		fractal->zoom = 20.0;
	else
		fractal->zoom *= zoom_factor;
	return ;
}

void	change_color(t_fractal *fractal)
{
	fractal->color_i++;
	if (fractal->color_i > 3)
		fractal->color_i = 0;
	return ;
}
