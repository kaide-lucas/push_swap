/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:30:14 by kaidda-s          #+#    #+#             */
/*   Updated: 2025/11/15 21:01:22 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

// Estrutura da pilha
typedef struct s_stack
{
	int value;
	int index;
	struct s_stack *next;
} t_stack;

// Protótipos - Parsing
t_stack *parse_arguments(int argc, char **argv);
int is_valid_input(const char *s);
int safe_atoi(const char *s, int *out);

// Protótipos - Stack utils
t_stack *stack_new(int value);
void stack_add_back(t_stack **stack, t_stack *new);
void stack_clear(t_stack **stack);
int stack_size(t_stack *stack);
int is_sorted(t_stack *stack);

// Protótipos - Checagens
int has_duplicates(t_stack *stack);
void normalize_values(t_stack *stack);

// Protótipos - Operações de swap
void swap(t_stack **stack);
void sa(t_stack **stack_a);
void sb(t_stack **stack_b);
void ss(t_stack **stack_a, t_stack **stack_b);

// Protótipos - Operações de push
void push(t_stack **src, t_stack **dst);
void pa(t_stack **stack_a, t_stack **stack_b);
void pb(t_stack **stack_a, t_stack **stack_b);

// Protótipos - Operações de rotate
void rotate(t_stack **stack);
void ra(t_stack **stack_a);
void rb(t_stack **stack_b);
void rr(t_stack **stack_a, t_stack **stack_b);

// Protótipos - Operações de reverse rotate
void reverse_rotate(t_stack **stack);
void rra(t_stack **stack_a);
void rrb(t_stack **stack_b);
void rrr(t_stack **stack_a, t_stack **stack_b);

// Protótipos - Algoritmo
int get_max_bits(t_stack *stack);
void radix_sort(t_stack **stack_a, t_stack **stack_b);
void push_swap(t_stack **stack_a, t_stack **stack_b);

#endif