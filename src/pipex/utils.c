/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:50:13 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/07 10:56:22 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_value(void *token)
{
	return (((t_tok *)token)->value);
}

char	**get_cmd(t_list *origin, int i)
{
	char	*full_cmd;
	char	*temp;
	t_list	*aux;
	int		size;
	char	**res;

	size = ft_lstsize(origin);
	aux = origin;
	full_cmd = get_value(aux->content);
	while (i < size)
	{
		aux = aux->next;
		temp = ft_strjoin(full_cmd, " ");
		free(full_cmd);
		full_cmd = ft_strjoin(temp, get_value(aux->content));
		free(temp);
		i++;
	}
	res = ft_split(full_cmd, ' ');
	free(full_cmd);
	return (res);
}

char	**get_paths(void)
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
	full_cmd = get_cmd(cmd->tokens, 1);
	mypaths = get_paths();
	try_fullpath(*full_cmd, full_cmd, mypaths);
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
	exit(table->error_code);
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
