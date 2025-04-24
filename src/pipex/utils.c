/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:50:13 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/24 12:30:14 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_value(void *token)
{
	return (((t_tok *)token)->value);
}

char	**get_cmd(t_list *origin)
{
	char *full_cmd;
	char *temp;
	t_list	*aux;
	int	size;
	int	i;

	size = ft_lstsize(origin);
	// printf("lst size ---> %d \n", size);
	i = 1;
	aux = origin;
	// full_cmd = ((t_tok *)aux->content)->value;
	full_cmd = get_value(aux->content);
	while (i < size)
	{
		aux = aux->next;
		printf("content --> %s \n", get_value(aux->content));
		
		temp = ft_strjoin(full_cmd, " ");
		full_cmd = ft_strjoin(temp, get_value(aux->content));
		free(temp);
		i++;
	}
		// printf("full cmd --> %s \n ", full_cmd);
	return (ft_split(full_cmd, ' '));
}

char	**get_paths()
{
	char	*env_paths;
	char	**my_paths;

	my_paths = NULL;
	env_paths = getenv("PATH");
	if (env_paths != NULL)
		my_paths = ft_split(env_paths, ':');
	return (my_paths);
}

void	path_exec(t_cmd *cmd, t_cmd_table *table)
{
	int		i;
	char	**full_cmd;
	char	**mypaths;
	char	*temp;
	char	*executable;

	i = 0;
	// ft_putendl_fd("Tokens: %s\n", ((t_tok *)cmd->tokens->content)->value, 2);
	full_cmd = get_cmd(cmd->tokens);
	mypaths = get_paths();
	while (mypaths[++i])
	{
		temp = ft_strjoin(mypaths[i], "/");
		executable = ft_strjoin(temp, full_cmd[0]);
		free(temp);
		if (access(executable, X_OK) == 0)
			execve(executable, full_cmd, mypaths);
		free(executable);
		table->error_code = PATH_ERROR;
	}
	free_all(mypaths);
	free_all(full_cmd);
	table->error_code = WRONG_CMD_ERROR;
	error_handler(table->error_code);
	exit(WRONG_CMD_ERROR);
}

void	free_all(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
