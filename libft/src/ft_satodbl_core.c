/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_satodbl_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlamiel- <xlamiel-@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:20:55 by xlamiel-          #+#    #+#             */
/*   Updated: 2025/11/28 15:58:48 by xlamiel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* libft.h

// Definición de códigos de error
#define SATODBL_SUCCESS 0
#define SATODBL_OVERFLOW 1
#define SATODBL_INVALID_CHAR 2
#define SATODBL_NO_DIGITS 3
#define SATODBL_EMPTY_STRING 4

// error 0, success 1
typedef struct	s_satodbl
{
	double	value;
	int		error;
} t_satodbl;

*/

static double	get_max_finite(void)
{
	static double	max_finite;
	static int		initialized;

	if (initialized == 0)
	{
		max_finite = nextafter(HUGE_VAL, 0.0);
		initialized = 1;
	}
	return (max_finite);
}

/*
	Overflow check BEFORE adding the next digit:
	If val > (DBL_MAX - digit) / 10 → overflow
*/
static int	dbl_will_overflow(double current, int digit)
{
	if (current > ((get_max_finite()) - digit) / 10.0)
		return (1);
	return (0);
}

t_satodbl	dbl_parse_integer_part(const char *str, size_t *i, long sign)
{
	t_satodbl	result;
	int			d;

	result = dbl_init_satodbl(0.0, SATODBL_SUCCESS);
	while (ft_isdigit(str[*i]))
	{
		d = str[*i] - '0';
		if (dbl_will_overflow(result.value, d))
		{
			result.error = SATODBL_OVERFLOW;
			if (sign == 1)
				result.value = (get_max_finite());
			else
				result.value = -(get_max_finite());
			while (ft_isdigit(str[*i]))
				(*i)++;
			return (result);
		}
		result.value = result.value * 10.0 + d;
		(*i)++;
	}
	return (result);
}

int	dbl_parse_fraction_part(const char *str, size_t *i, double *value)
{
	double	power;
	int		parsed;
	int		d;

	power = 1.0;
	parsed = 0;
	if (str[*i] == '.')
	{
		(*i)++;
		while (ft_isdigit(str[*i]))
		{
			parsed = 1;
			d = str[*i] - '0';
			power *= 0.1;
			*value += d * power;
			(*i)++;
		}
	}
	return (parsed);
}

t_satodbl	dbl_parse_double_digits(const char *str, size_t *i, long sign)
{
	size_t		start;
	int			fraction_digits;
	t_satodbl	r;

	start = *i;
	r = dbl_parse_integer_part(str, i, sign);
	if (r.error != SATODBL_SUCCESS)
		return (r);
	fraction_digits = dbl_parse_fraction_part(str, i, &r.value);
	if (*i == start && !fraction_digits)
		return (dbl_init_satodbl(0.0, SATODBL_NO_DIGITS));
	r.value *= sign;
	return (r);
}
