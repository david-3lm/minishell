/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:23:27 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/11/14 21:43:21 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
    char *rl;
    char **res;
    int i = 0;

    rl = readline("Prompt > ");
    res = lexer(rl);
    while (res[i])
    {
        ft_printf("%s\n", res[i]);
        i++;
    }
    
    
    return (0);
}
