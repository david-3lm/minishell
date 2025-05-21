
#include "../inc/minishell.h"

void	skip_spaces(const char *input, int *curr_pos)
{
	while (input[*curr_pos] && ft_isspace(input[*curr_pos]))
		(*curr_pos)++;
}

char	*ft_strncpy(char *dest, char *src, size_t n)
{
	char	*sav_dest;
	char	*sav_src;

	sav_dest = dest;
	sav_src = src;
	if (n != 0)
	{
		while (1)
		{
			*sav_dest = *sav_src++;
			if (*sav_dest++ == 0)
			{
				while (--n != 0)
					*sav_dest++ = 0;
				break ;
			}
			if (--n == 0)
				break ;
		}
	}
	return (dest);
}

int	is_cmd_delimiter(char c)
{
	int	check;

	if (c == ';')
		check = 1;
	else if (c == '|')
		check = 1;
	else if (c == '&')
		check = 1;
	else
		check = 0;
	return (check);
}

int	is_token_delimiter(char c)
{
	int	check;

	if (ft_strchr(WHITE_SPACE, c) != 0)
		check = 1;
	else if (c == ';')
		check = 1;
	else if (c == '|')
		check = 1;
	else if (c == '&')
		check = 1;
	else if (c == '<')
		check = 1;
	else if (c == '>')
		check = 1;
	else
		check = 0;
	return (check);
}

void	skip_quotes(const char *input, int *curr_pos)
{
	int		has_double_quotes_open;
	int		has_single_quotes_open;

	has_double_quotes_open = 0;
	has_single_quotes_open = 0;
	while (input[*curr_pos])
	{
		if (input[*curr_pos] == '"' && has_single_quotes_open == 0)
			has_double_quotes_open = !has_double_quotes_open;
		else if (input[*curr_pos] == '\'' && has_double_quotes_open == 0)
			has_single_quotes_open = !has_single_quotes_open;
		(*curr_pos)++;
		if (!has_double_quotes_open && !has_single_quotes_open)
			break ;
	}
}

char	*get_token(const char *input, int *curr_pos)
{
	char	*token;
	int		saved_pos;

	saved_pos = *curr_pos;
	while (input[*curr_pos] && !is_token_delimiter(input[*curr_pos]))
	{
		if (is_quote(input[*curr_pos]))
			skip_quotes(input, curr_pos);
		else if (input[*curr_pos])
			(*curr_pos)++;
	}
	token = ft_substr(input, saved_pos, *curr_pos - saved_pos);
	// if (!token)
		// quit_program(EXIT_FAILURE);
	printf("TOKEN  => %s\n", token);
	return (token);
}

t_redir	*get_redir(const char *input, int *curr_pos)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	// if (!redir)
		// quit_program(EXIT_FAILURE);
	if (input[*curr_pos] == '<')
		(*redir).type = input[(*curr_pos)++];
	else if (!ft_strncmp(&input[*curr_pos], ">>", 2))
	{
		ft_strncpy((char *)redir->type, (char *)&input[*curr_pos], 2);
		*curr_pos += 2;
	}
	else if (input[*curr_pos] == '>')
		(*redir).type = input[(*curr_pos)++];
	skip_spaces(input, curr_pos);
	redir->direction = get_token(input, curr_pos);
	return (redir);
}

t_cmd	*get_cmds(const char *input, int *curr_pos)
{
	t_cmd	*cmd;
	t_list	*new_node;

	cmd = ft_calloc(1, sizeof(t_cmd));
	// if (!cmd)
		// quit_program(EXIT_FAILURE);
	while (input[*curr_pos] && !is_cmd_delimiter(input[*curr_pos]))
	{
		if (input[*curr_pos] != '>' && input[*curr_pos] != '<')
		{
			new_node = ft_lstnew((void *)get_token(input, curr_pos));
			// if (!new_node)
				// quit_program(EXIT_FAILURE);
			ft_lstadd_back(&cmd->tokens, new_node);
		}
		else if (input[*curr_pos] == '>' || input[*curr_pos] == '<')
		{
			new_node = ft_lstnew((void *)get_redir(input, curr_pos));
			// if (!new_node)
				// quit_program(EXIT_FAILURE);
			ft_lstadd_back(&cmd->redirs, new_node);
		}
		skip_spaces(input, curr_pos);
	}
	return (cmd);
}

t_cmd_table	*get_cmd_table(const char *input, int *curr_pos)
{
	t_cmd_table	*cmd_table;
	t_list		*cmd;

	cmd_table = ft_calloc(1, sizeof(t_cmd_table));
	// if (!cmd_table)
		// quit_program(EXIT_FAILURE);
	while (input[*curr_pos])
	{
		skip_spaces(input, curr_pos);
		cmd = ft_lstnew((void *)get_cmds(input, curr_pos));
		// if (!cmd)
			// quit_program(EXIT_FAILURE);
		ft_lstadd_back(&cmd_table->cmds, cmd);
		if (input[*curr_pos] == '|' && input[*curr_pos + 1] != '|')
			(*curr_pos)++;
	}
	return (cmd_table);
}
