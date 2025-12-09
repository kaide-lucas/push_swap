/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_5_simple_cases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:18:45 by kaidda-s          #+#    #+#             */
/*   Updated: 2025/12/09 15:24:40 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_stack **stack_a)
{
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a);
}

void	sort_three(t_stack **stack_a)
{
	int	a;
	int	b;
	int	c;

	a = (*stack_a)->value;
	b = (*stack_a)->next->value;
	c = (*stack_a)->next->next->value;
	if (a > b && b < c && a < c)
		sa(stack_a);
	else if (a > b && b > c)
	{
		sa(stack_a);
		rra(stack_a);
	}
	else if (a > b && b < c && a > c)
		ra(stack_a);
	else if (a < b && b > c && a < c)
	{
		sa(stack_a);
		ra(stack_a);
	}
	else if (a < b && b > c && a > c)
		rra(stack_a);
}

static int	find_min_index(t_stack *stack)
{
	int	min;
	int	min_index;
	int	current_index;

	min = stack->value;
	min_index = 0;
	current_index = 0;
	while (stack)
	{
		if (stack->value < min)
		{
			min = stack->value;
			min_index = current_index;
		}
		stack = stack->next;
		current_index++;
	}
	return (min_index);
}

void	sort_four(t_stack **stack_a, t_stack **stack_b)
{
	int	min_pos;

	min_pos = find_min_index(*stack_a);
	if (min_pos == 1)
		ra(stack_a);
	else if (min_pos == 2)
	{
		ra(stack_a);
		ra(stack_a);
	}
	else if (min_pos == 3)
		rra(stack_a);
	pb(stack_a, stack_b);
	sort_three(stack_a);
	pa(stack_a, stack_b);
}

void	sort_five(t_stack **stack_a, t_stack **stack_b)
{
	int	min_pos;

	min_pos = find_min_index(*stack_a);
	if (min_pos <= 2)
		while (min_pos-- > 0)
			ra(stack_a);
	else
		while (min_pos++ < 5)
			rra(stack_a);
	pb(stack_a, stack_b);
	sort_four(stack_a, stack_b);
	pa(stack_a, stack_b);
}
