/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlamiel- <xlamiel-@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 01:03:10 by xlamiel-          #+#    #+#             */
/*   Updated: 2025/11/25 02:10:59 by xlamiel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*

	[0..799] -> [-2..+2]

*/
double	map(double unscaled_num, t_range new, t_range old)
{
	return ((new.max - new.min) * (unscaled_num - old.min)
		/ (old.max - old.min) + new.min);
}

/*

	SUM complex
		fairly easy is vector addition

*/
t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.x = z1.x + z2.x;
	result.y = z1.y + z2.y;
	return (result);
}

/*

	SQUARE is trickier

		real = (x2 - y^2)
		i = 2*x*y
*/
t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.x = (z.x * z.x) - (z.y * z.y);
	result.y = 2 * z.x * z.y;
	return (result);
}
