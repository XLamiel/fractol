/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlamiel- <xlamiel-@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 02:40:57 by xlamiel-          #+#    #+#             */
/*   Updated: 2025/11/25 03:15:45 by xlamiel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	if (n <= 0)
		return (0);
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (-1);
	else if (!s2)
		return (1);
	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	putstr_fd(char *s, int fd)
{
	if (s == NULL || fd < 0)
		return ;
	if (*s != '\0')
	{
		write(fd, s, 1);
		putstr_fd(s + 1, fd);
	}
	return ;
}

static int	skip_whitespace_and_sign(char **s)
{
	int	sign;

	sign = 1;
	while ((**s > 9 && **s <= 13) || **s == 32)
		(*s)++;
	while (**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -sign;
		(*s)++;
	}
	return (sign);
}

double	atodbl(char *s)
{
	long	integer_part;
	double	fractional_part;
	double	pow;
	int		sign;

	integer_part = 0;
	fractional_part = 0.0;
	pow = 1.0;
	sign = 1;
	if (!s)
		return (0.0);
	sign = skip_whitespace_and_sign(&s);
	while (*s && *s != '.')
		integer_part = (integer_part * 10) + (*s++ - '0');
	if (*s == '.')
		s++;
	while (*s)
	{
		pow /= 10.0;
		fractional_part += (*s++ - '0') * pow;
	}
	return ((integer_part + fractional_part) * sign);
}
