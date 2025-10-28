/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:57:16 by kaidda-s          #+#    #+#             */
/*   Updated: 2025/10/28 16:33:13 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int is_valid_token(const char *s)
{
	int	i;
	
	if (s == NULL)
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i = 1;
	if (s[i] == '\0')
		return 0;
	while (s[i] != '\0')
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

