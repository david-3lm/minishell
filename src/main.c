/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:23:27 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/11/18 10:58:48 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
    char *rl;
    char **res;

    rl = readline("\033[1;32m🎅 Concepción > \033[0m");
    while (rl != NULL)
    {
        res = lexer(rl);
        ft_printf("Hemo hecho un lexeo: %s\n", res[0]);
        rl = readline("\033[1;32m🎅 Concepción > \033[0m");
    }    
    return (0);
}
