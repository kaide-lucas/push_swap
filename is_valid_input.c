/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:57:16 by kaidda-s          #+#    #+#             */
/*   Updated: 2025/11/11 11:41:41 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int is_valid_input(const char *s)
{
	int	i;
	
	if (s == NULL)
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i = 1;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

static const char *skip_whitespace(const char *s)
{
	while (ft_isspace((unsigned char)*s))
		s++;
	return (s);
}

static int parse_sign_and_advance(const char **s)
{
	int	sign;

	sign = 1;
	if(**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
		if (!**s || !ft_isdigit((unsigned char)**s))
			return (0);
	}
	return (sign);
}
static int str_to_number(const char *s, int sign, int *out)
{
	long long	ac;
	long long	val;

	ac = 0;
	while (*s)
	{
		if (!ft_isdigit((unsigned char)*s))
			return (0);
		ac = ac * 10 + (*s - '0');
		val = ac * sign;
		if (val > 2147483647 || val < -2147483648)
			return (0);
		s++;
	}
	*out = (int)val;
	return (1); 
}

int safe_atoi(const char *s, int *out)
{
	int	n;

	if (!s || !*s)
		return (0);
	s = skip_whitespace(s);
	n = parse_sign_and_advance(&s);
	if (n == 0)
		return (0);
	return (str_to_number(s, n, out));
}
