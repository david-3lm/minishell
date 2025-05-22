/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:50:13 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/22 12:54:32 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <errno.h>

char	*get_value(void *token)
{
	return (((t_tok *)token)->value);
}

char	**get_cmd(t_list *origin)
{
	char	*full_cmd;
	char	*temp;
	t_list	*aux;
	int		size;
	char	**res;

	size = ft_lstsize(origin);
	aux = origin;
	full_cmd = (char *)aux->content;
	while (size > 0 && aux->next)
	{
		aux = aux->next;
		printf("aux en getcmd en pathexec  --> %s \n", (char *)aux->content);
		temp = ft_strjoin(full_cmd, " ");
		free(full_cmd);
		full_cmd = ft_strjoin(temp, (char *)aux->content);
		free(temp);
		size--;
	}
	printf("fullcmd en getcmd en pathexec  --> %s \n", full_cmd);
	res = ft_split(full_cmd, ' ');
	free(full_cmd);
	return (res);
}

char	**get_paths(t_cmd_table *table, char *cmd)
{
	char	*env_paths;
	char	**my_paths;

	my_paths = NULL;
	env_paths = mini_get_env(table, "PATH")->value;
	if (env_paths != NULL)
		my_paths = ft_split(env_paths, ':');
	else
		ft_error_str(table, cmd);
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
	full_cmd = get_cmd(cmd->tokens);
	mypaths = get_paths(table, full_cmd[0]);
	if (try_fullpath(*full_cmd, full_cmd, mypaths, table) || mypaths == NULL)
		exit(table->error_code);
	while (mypaths[++i])
	{
		temp = ft_strjoin(mypaths[i], "/");
		executable = ft_strjoin(temp, full_cmd[0]);
		free(temp);
		if (access(executable, F_OK) == 0)
			execve(executable, full_cmd, mypaths);
		free(executable);
		table->error_code = PATH_ERROR;
	}
	free_all(mypaths);
	ft_wrong_access_error(table, full_cmd[0], WRONG_CMD_ERROR);
	free_all(full_cmd);
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
