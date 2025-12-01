/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlamiel- <xlamiel-@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 03:17:43 by xlamiel-          #+#    #+#             */
/*   Updated: 2025/11/29 02:48:49 by xlamiel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h> // perror
# include <stdlib.h> // mallo free
# include <unistd.h> // write, STDERR_FILENO
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "mlx.h"

# include "libft.h"

# define ERROR_MESSAGE1 "Please enter\n"
# define ERROR_MESSAGE2 "\t\"./fractol mandelbrot\" or\n"
# define ERROR_MESSAGE3 "\t\"./fractol julia <value_1> <value_2>\"\n"
# define ERROR_ARG_JULIA "Error: Invalid or non-numeric arguments for Julia.\n"
/*
 * We use a square to
 * keep the rendering math simple
*/
# define WIDTH	800
# define HEIGHT	800

/*
 *COLORS
*/
// Basic RGB color defines (0–255 range)
# define BLACK		0x000000 // RGB (0, 0, 0)
# define WHITE		0xFFFFFF // RGB (255, 255, 255)
# define RED		0xFF0000 // RGB (255, 0, 0)
# define GREEN		0x00FF00 // RGB (0, 255, 0)
# define BLUE		0x0000FF // RGB (0, 0, 255)
# define YELLOW		0xFFFF00 // RGB (255, 255, 0)
# define CYAN		0x00FFFF // RGB (0, 255, 255)
# define MAGENTA	0xFF00FF // RGB (255, 0, 255)
# define GRAY		0x808080 // RGB (128, 128, 128)
// Psychedelic colors
# define NEON_PINK		0xFF1493 // RGB (255, 20, 147)
# define ELECTRIC_LIME	0xCCFF00 // RGB (204, 255, 0)
# define ACID_GREEN		0xB0BF1A // RGB (176, 191, 26)
# define HOT_MAGENTA	0xFF00CC // RGB (255, 0, 204)
# define CYAN_NEON		0x00FFFF // RGB (0, 255, 255)
# define ULTRA_VIOLET	0x8A2BE2 // RGB (138, 43, 226)
# define ELECTRIC_BLUE	0x7DF9FF // RGB (125, 249, 255)
# define LAVA_ORANGE	0xFF4500 // RGB (255, 69, 0)
# define SHOCKING_PINK	0xFC0FC0 // RGB (252, 15, 192)
# define RADIOACTIVE_YELLOW	0xF5FF00 // RGB (245, 255, 0)
# define TRIPPY_PURPLE	0xBF00FF // RGB (191, 0, 255)
# define PSY_RED		0xFF003F // RGB (255, 0, 63)

/*
COMPLEX value
		x real
		y imaginary
*/
typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

/*
IMAGE
	This is basically a pixels buffer
	values from mix_get_data_addr()
*/
typedef struct s_img
{
	void	*img_ptr;	//pinter to image struct
	char	*pixels_ptr;	// points to the actual pixels
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

/*
FRACTAL_ID
	MLX stuff
	Image
	Hooks values
*/
typedef struct s_fractal
{
	char	*name;
	void	*mlx_connection;	// mlx_init()
	void	*mlx_window;		// mlx_new_window()
	t_img	img;
	double	escaped_value; // hypotenuse
	int		iterations_definition; // image quality and render speed
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
	int		needs_redraw;
	int		color_i;
}	t_fractal;

/*
Range
	to use in map funtion
*/
typedef struct s_range
{
	double	min;
	double	max;
}	t_range;

// string utils
int			ft_strncmp(const char *s1, const char *s2, int n);
void		putstr_fd(char *s, int fd);
double		atodbl(char *s);

// init
void		fractal_init(t_fractal *fractal);

// render
void		fractal_render(t_fractal *fractal);

// aux
int			get_color(int iter, t_fractal *fractal);
void		change_color(t_fractal *fractal);
void		up_iterations_definition(t_fractal *fractal);
void		down_iterations_definition(t_fractal *fractal);
void		zoom_limits(t_fractal *fractal, double zoom_factor);

// maths_utils
double		map(double unscaled_num,
				t_range new,
				t_range old);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);

// hook_events
int			key_handler(int keysym, t_fractal *fractal);
int			mouse_handler(int button,
				int x,
				int y,
				t_fractal *fractal);
int			render_loop(t_fractal *fractal);

// clean_up
int			close_handler(t_fractal *fractal);
//int			julia_track(int x, int y, t_fractal *fractal);

#endif
