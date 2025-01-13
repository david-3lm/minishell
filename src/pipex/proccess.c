/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:45:46 by cde-migu          #+#    #+#             */
/*   Updated: 2025/01/13 13:00:09 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipex(char **argv, int argc)
{
	int	i;
	int	output;
	int	last_output;

	i = 0;
	output = 0;
	while (i < argc - 1)
	{
		output = pipex_proccess(argv[i]);
		i++;
	}
	last_output = last_child(argv, argc);
	if (last_output && output != last_output)
		output = last_output;
	return (output);
}