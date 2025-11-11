/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:30:14 by kaidda-s          #+#    #+#             */
/*   Updated: 2025/10/28 16:36:40 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

/* Estrutura da pilha */
typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
} t_stack;

/* Protótipos - Parsing */
t_stack	*parse_arguments(int argc, char **argv);
int		is_valid_input(const char *s);
int		safe_atoi(const char *s, int *out);

/* Protótipos - Stack utils (você vai implementar depois) */
t_stack *stack_new(int value);
void	stack_add_back(t_stack **stack, t_stack *new);
void	stack_clear(t_stack **stack);

/* Protótipos - Checagens (você vai implementar depois) */
int		has_duplicates(t_stack *stack);
void	normalize_values(t_stack *stack);

#endif