/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlamiel- <xlamiel-@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 02:12:11 by xlamiel-          #+#    #+#             */
/*   Updated: 2025/11/28 23:36:13 by xlamiel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
	Put a pixel in my image buffer
*/
static void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * img->bpp / 8);
	*(unsigned int *)(img->pixels_ptr + offset) = color;
	return ;
}

/*
static void	mandel_vs_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}
*/

/*
 *		800
 *		-------------
 *		|			|
 *		|			|
 *	800	|			|
 *		|			|
 *		|			|
 *		-------------

 *		-2			+2
 *		-------------
 *		|			|
 *		|			|
 *	800	|			|
 *		|			|
 *		|			|
 *		-------------

	MANDELBROT
	z = z^2 + c
	z initially is (0, 0)
	c is the actual point

	z = z^2 + c -> z1 = c + c
	
	JULIA
	./fractol julia <real> <>
	z = pixel_point + constant
*/

static t_complex	get_complex_coord(int x, int y, t_fractal *fractal)
{
	t_complex	coord;

	coord.x = map(x, (t_range){-2.0, +2.0}, (t_range){0.0, WIDTH})
		* fractal->zoom + fractal->shift_x;
	coord.y = map(y, (t_range){+2.0, -2.0}, (t_range){0.0, HEIGHT})
		* fractal->zoom + fractal->shift_y;
	return (coord);
}

static int	iterate_fractal(t_complex z, t_complex c, t_fractal *fractal)
{
	int	i;

	i = 0;
	while (i < fractal->iterations_definition)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escaped_value)
			return (i);
		i++;
	}
	return (i);
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			iter;
	int			color;

	z = get_complex_coord(x, y, fractal);
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c.x = fractal->julia_x;
		c.y = fractal->julia_y;
	}
	else
	{
		c.x = z.x;
		c.y = z.y;
	}
	iter = iterate_fractal(z, c, fractal);
	if (iter < fractal->iterations_definition)
		color = get_color(iter, fractal);
	else
		color = WHITE;
	my_pixel_put(x, y, &fractal->img, color);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_connection,
		fractal->mlx_window,
		fractal->img.img_ptr,
		0, 0);
}
