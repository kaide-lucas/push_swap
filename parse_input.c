/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:30:33 by kaidda-s          #+#    #+#             */
/*   Updated: 2025/11/04 14:20:46 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack *error_exit(t_stack **stack)
{
    if (*stack)
        stack_clear(stack);
    return (NULL);
}

t_stack *parse_arguments(int argc, char **argv)
{
    t_stack *stack_a;
    t_stack *node;
    int     num;
    int     i;

    stack_a = NULL;
    i = 1;
    while (i < argc)
    {
        if (!safe_atoi(argv[i], &num))
            return (error_exit(&stack_a));
        node = stack_new(num);
        if (!node)
            return (error_exit(&stack_a));
        stack_add_back(&stack_a, node);
        i++;
    }
    if (has_duplicates(stack_a))
        return (error_exit(&stack_a));
    normalize_values(stack_a);
        return (stack_a);
}
