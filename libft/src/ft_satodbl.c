/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_satodbl_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlamiel- <xlamiel-@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:23:15 by xlamiel-          #+#    #+#             */
/*   Updated: 2025/11/27 21:52:43 by xlamiel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* libft.h

// Error codes
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

// Validate trailing chars
static t_satodbl	dbl_validate_trailing_chars_dbl(const char *str, size_t i,
		t_satodbl result)
{
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
		return (dbl_init_satodbl(0.0, SATODBL_INVALID_CHAR));
	return (result);
}

// Pral
t_satodbl	ft_satodbl(const char *str)
{
	t_satodbl	result;
	size_t		i;
	long		sign;

	if (!str)
		return (dbl_init_satodbl(0.0, SATODBL_EMPTY_STRING));
	if (str[0] == '\0')
		return (dbl_init_satodbl(0.0, SATODBL_EMPTY_STRING));
	i = dbl_skip_spaces(str);
	sign = dbl_process_sign(str, &i);
	result = (dbl_parse_double_digits(str, &i, sign));
	if (result.error != SATODBL_SUCCESS)
		return (result);
	return (dbl_validate_trailing_chars_dbl(str, i, result));
}
