/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:30:33 by kaidda-s          #+#    #+#             */
/*   Updated: 2025/10/28 15:30:36 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/* declarar a função que implementamos */
int is_valid_token(const char *s);

static void test(const char *s)
{
    printf("\"%s\" -> %s\n", s, is_valid_token(s) ? "VALID" : "INVALID");
}

int main(void)
{
    test("123");
    test("+123");
    test("-0");
    test("");
    test("+");
    test("-");
    test("12a3");
    test(" 123");   /* token com espaço: deve ser INVALID (pré-trim required) */
    test("007");
    return 0;
}