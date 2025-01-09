/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:50:13 by cde-migu          #+#    #+#             */
/*   Updated: 2025/01/09 19:19:49 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* void	command_path(char **cmd, char **envp)
{
	char	*temp;

	temp = ft_strdup(cmd[0]);
	if (access(temp, 0) == 0)
	{
		execve(temp, cmd, envp);
		free(temp);
		perror("Error: failed execution");
		exit(EXIT_FAILURE);
	}
	else
	{
		free(temp);
		perror("Error command not found");
		exit(EXIT_FAILURE);
	}
} */

char	**get_cmd(t_list *origin)
{
	char *full_cmd;
	char *temp;
	t_list	*aux;
	int	size;
	int	i;

	size = ft_lstsize(origin);
	i = 0;
	aux = origin;
	full_cmd = (char *)aux->content;
	while (i < size)
	{
		aux = aux->next;
		full_cmd = ft_strjoin(full_cmd, " ");
		full_cmd = ft_strjoin(full_cmd, aux->content);
		i++;
	}
	return (full_cmd);
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

void	path_exec(t_cmd *cmd)
{
	int		i;
	t_list	*token;
	char	**mypaths;
	char	*temp;
	char	*executable;

	i = 0;
	token = cmd->tokens;
	mypaths = get_paths();
	while (mypaths[++i])
	{
		temp = ft_strjoin(mypaths[i], "/");
		executable = ft_strjoin(temp, token->content);
		free(temp);
		if (access(executable, X_OK) == 0)
			execve(executable, cmd, mypaths);
		free(executable);
	}
	perror("Error: ");
	free_all(mypaths);
	free_all(cmd);
	exit(EXIT_FAILURE);
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

void	ft_usage(void)
{
	ft_printf("\033[31mError: Bad argument\n\e[0m");
	ft_printf("Ex: ./pipex_bonus <file1> <cmd1> <cmd2> <...> <file2>\n");
	ft_printf("\t./pipex_bonus \"here_doc\" <LIMITER> <cmd> \
					<cmd1> <...> <file>\n");
	exit(EXIT_SUCCESS);
}
