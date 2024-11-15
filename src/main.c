/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:23:27 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/11/15 11:47:38 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
    char *rl;
    char **res;
    int i = 0;

    rl = readline("\033[1;32m🎅 Concepción > \033[0m");
    res = lexer(rl);
    while (res[i])
    {
        ft_printf("%s\n", res[i]);
        i++;
    }
    
    
    return (0);
}
