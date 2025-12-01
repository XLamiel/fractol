/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlamiel- <xlamiel-@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:11:11 by xlamiel-          #+#    #+#             */
/*   Updated: 2025/11/28 19:18:26 by xlamiel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
	./fractol maldenbrot
	./fractol julia <real> <i>

	main funtion Too Long; Didn't Read

	cc -I./include -I./minilibx-linux *.c -L./minilibx-linux -lmlx 
	-lXext -lX11 -lm -o fractol

*/

void	error_message(void)
{
	putstr_fd(ERROR_MESSAGE1, STDERR_FILENO);
	putstr_fd(ERROR_MESSAGE2, STDERR_FILENO);
	putstr_fd(ERROR_MESSAGE3, STDERR_FILENO);
}

static void	handle_julia_args(t_fractal *fractal, char *argv[])
{
	t_satodbl	res_x;
	t_satodbl	res_y;

	res_x = ft_satodbl(argv[2]);
	res_y = ft_satodbl(argv[3]);
	if (res_x.error != SATODBL_SUCCESS || res_y.error != SATODBL_SUCCESS)
	{
		putstr_fd(ERROR_ARG_JULIA, STDERR_FILENO);
		error_message();
		close_handler(fractal);
	}
	fractal->julia_x = res_x.value;
	fractal->julia_y = res_y.value;
}

int	main(int argc, char *argv[])
{
	t_fractal	fractal;

	if ((argc == 2 && (ft_strncmp(argv[1], "mandelbrot", 11) == 0))
		|| (argc == 4 && (ft_strncmp(argv[1], "julia", 6) == 0)))
	{
		fractal.name = argv[1];
		fractal_init(&fractal);
		if (ft_strncmp(argv[1], "julia", 6) == 0)
		{
			handle_julia_args(&fractal, argv);
		}
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else
	{
		error_message();
		exit(EXIT_FAILURE);
	}
}
