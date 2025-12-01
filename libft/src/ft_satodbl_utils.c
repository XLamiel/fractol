/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_satodbl_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlamiel- <xlamiel-@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:17:55 by xlamiel-          #+#    #+#             */
/*   Updated: 2025/11/28 15:02:04 by xlamiel-         ###   ########.fr       */
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

size_t	dbl_skip_spaces(const char *str)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

long	dbl_process_sign(const char *str, size_t *i)
{
	long	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

t_satodbl	dbl_init_satodbl(double value, int error_code)
{
	t_satodbl	r;

	r.value = value;
	r.error = error_code;
	return (r);
}
