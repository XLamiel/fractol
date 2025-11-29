/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlamiel- <xlamiel-@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:33:18 by xlamiel-          #+#    #+#             */
/*   Updated: 2025/11/29 02:53:01 by xlamiel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
	ESC or i press the "x" in the window
	int	(*f)(void *param)
*/
int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection,
		fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection,
		fractal->mlx_window);
	mlx_destroy_display(fractal->mlx_connection);
	free(fractal->mlx_connection);
	exit(EXIT_SUCCESS);
}

/*
	Keypress prototype
	int (*f)(int keycode, void *param)
*/
int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	else if (keysym == XK_Left)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysym == XK_Right)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysym == XK_Down)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == XK_plus || keysym == XK_equal || keysym == 161)
		up_iterations_definition(fractal);
	else if (keysym == XK_minus || keysym == 39)
		down_iterations_definition(fractal);
	else if (keysym == XK_c)
		change_color(fractal);
	fractal->needs_redraw = 1;
	return (0);
}

/*

	int (*f)(int button, int x, int y, void *param)

*/
int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	double	mouse_real_before;
	double	mouse_imag_before;
	double	mouse_real_after;
	double	mouse_imag_after;
	double	zoom_factor;

	if (button == Button5)
		zoom_factor = 1.03;
	else if (button == Button4)
		zoom_factor = 0.97;
	else
		return (0);
	mouse_real_before = map(x, (t_range){-2.0, +2.0}, (t_range){0.0, WIDTH})
		* fractal->zoom + fractal->shift_x;
	mouse_imag_before = map(y, (t_range){+2.0, -2.0}, (t_range){0.0, HEIGHT})
		* fractal->zoom + fractal->shift_y;
	zoom_limits(fractal, zoom_factor);
	mouse_real_after = map(x, (t_range){-2.0, +2.0}, (t_range){0.0, WIDTH})
		* fractal->zoom;
	mouse_imag_after = map(y, (t_range){+2.0, -2.0}, (t_range){0.0, HEIGHT})
		* fractal->zoom;
	fractal->shift_x = mouse_real_before - mouse_real_after;
	fractal->shift_y = mouse_imag_before - mouse_imag_after;
	fractal->needs_redraw = 1;
	return (0);
}

/*
	int	(*f)(int x, int y, void *param)

int	julia_track(int x, int y, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		fractal->julia_x = map(x, (t_range){-1.0, +0.6},
				(t_range){0.0, WIDTH});
		fractal->julia_y = map(y, (t_range){+0.6, -1.0},
				(t_range){0.0, HEIGHT});
		fractal->needs_redraw = 1;
	}
	return (0);
}
*/

/*
	Principal function
*/
int	render_loop(t_fractal *fractal)
{
	if (fractal->needs_redraw)
	{
		fractal_render(fractal);
		fractal->needs_redraw = 0;
	}
	return (0);
}
