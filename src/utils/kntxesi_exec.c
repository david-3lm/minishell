/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kntxesi_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:32:59 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/22 14:50:29 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_kntxesi(t_cmd cmd)
{
	char	*token;
	t_list	*token_list;

	token_list = cmd.tokens;
	token = (char *)token_list->content;
	if (ft_strcmp(token, "./minishell") == 0)
		return (true);
	return (false);
}

bool	is_inside_kntxesi(int argc, char **argv)
{
	if (argc == 3 && (ft_strcmp(argv[2], "true") == 0))
		return (true);
	return (false);
}

char	*ft_getenv_value(t_cmd_table *table, char *str)
{
	t_list	*env_list;
	t_env	*current;
	char	*result;

	env_list = *(table->envv);
	if (env_list)
	{
		while (env_list->next)
		{
			if (!env_list->content)
				return (NULL);
			current = (t_env *)env_list->content;
			if (ft_strncmp(current->key, str, ft_strlen(str)) == 0)
			{
				result = ft_calloc(ft_strlen(current->value) + 1, sizeof(char));
				ft_strlcpy(result, current->value, ft_strlen(current->value) + 1);
				return (result);
			}
			env_list = env_list->next;
		}
	}
	return (NULL);
}

static int	ft_exec(t_cmd_table *table, char *const *envp, char *shlvl)
{
	char *const	command[] = {"./minishell", shlvl, "true", NULL};

	if (access("./minishell", F_OK) == 0)
	{
		execve("./minishell", command, envp);
		ft_wrong_access_error(table, command[0], PERMISSION_ERROR);
		return (table->error_code);
	}
	return (NO_ERROR);
}

int	execute_kntxesi(t_cmd_table *table)
{
	pid_t	pid;
	int		value;
	int 	i = 0;
	char	**mypaths;

	check_error(pipe((table)->pipe_fd), CHECK_PIPE, table);
	pid = fork();
	check_error(pid, CHECK_FORK, table);
	if (pid == 0)
	{
		i++;
		close((table)->pipe_fd[READ_E]);
		mypaths = get_paths(table, "./minishell");
		ft_putstr_fd("exec kontxesi --->", 2);
		ft_putendl_fd(ft_itoa(i), 2);
		ft_exec(table, mypaths, ft_getenv_value(table, "SHLVL"));
	}
	else
	{
		close((table)->pipe_fd[WRITE_E]);
		value = dup2((table)->pipe_fd[READ_E], STDIN_FILENO);
		check_error(value, CHECK_DUP, table);
		close((table)->pipe_fd[READ_E]);
	}
	return (table->error_code);
}
