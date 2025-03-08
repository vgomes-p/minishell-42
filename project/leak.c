#include "../../includes/minishell.h"

t_token	*mktoken(char *value, t_token_tp type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token->value);
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*create_token_list(char **split, t_token *head)
{
	t_token	*current;
	t_token	*nwtoken;
	int		pos;

	current = NULL;
	pos = 0;
	while (split[pos])
	{
		nwtoken = mktoken(split[pos],
				get_token_type(split[pos], current, pos == 0));
		if (!nwtoken)
		{
			sfree(split);
			free_tokens(head);
			return (NULL);
		}
		if (!head)
			head = nwtoken;
		else
			current->next = nwtoken;
		current = nwtoken;
		pos++;
	}
	sfree(split);
	return (head);
}

t_token	*tokening(char *input)
{
	char	**split;
	t_token	*head;

	split = ms_split_quotes(input);
	if (!split)
		return (NULL);
	head = create_token_list(split, NULL);
	if (!head)
	{
		sfree(split);
		// sfree(head);
		return (NULL);
	}
	sfree(split);
	return (head);
}

static void	process_command(char *input, t_minishell *shell)
{
	shell->tokens = tokening(input);
	if (!shell->tokens)
	{
		ft_putstr_fd(RED "Error: Tokenination has failed\n" RESET, 2);
		free(input);
		// free(shell->tokens);
		return ;
	}
	if (!valid_syntax(shell->tokens))
	{
		ft_putstr_fd(RED "Syntax error\n" RESET, 2);
		free_tokens(shell->tokens);
		shell->tokens = NULL;
		free(input);
		return ;
	}
	exec_cmd(shell);
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	free(input);
}

void	ms_prompt(t_minishell *shell)
{
	char	*input;

	handle_input(shell, &input);
	if (input)
		process_command(input, shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.env = dup_env(envp, &shell.env_size);
	shell.prompt = NULL;
	shell.exit_stt = 0;
	g_shell = &shell;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	welcome();
	while (1)
	{
		ms_prompt(&shell);
	}
	free_env(shell.env);
	return (0);
}

char	**tokens_matrix(t_token *token)
{
	int		cnt;
	int		pos;
	char	**ret;

	if (!token)
		return (NULL);
	cnt = count_tokens(token);
	ret = ft_calloc((cnt + 1), sizeof(char *));
	if (!ret)
	{
		// free(ret);
		return (NULL);
	}
	pos = 0;
	while (pos < cnt)
	{
		ret[pos] = ft_strdup(token->value);
		if (!ret[pos])
		{
			while (--pos >= 0)
				free(ret[pos]);
			free(ret);
			return (NULL);
		}
		token = token->next;
		pos++;
	}
	ret[pos] = NULL;
	return (ret);
}

t_token	*cpy_token_ls(t_token *tokens)
{
	t_token	*new_list;
	t_token	*current;
	t_token	*new_token;

	if (!tokens)
		return (NULL);
	new_list = NULL;
	current = tokens;
	while (current)
	{
		new_token = mktoken(current->value, current->type);
		if (!new_token)
		{
			free_tokens(new_list);
			return (NULL);
		}
		if (!new_list)
			new_list = new_token;
		else
			addtoken_ls(new_list, new_token);
		current = current->next;
	}
	return (new_list);
}
t_exec	init_exec(t_minishell *shell, t_token *tokens)
{
	t_exec	exec;
	int		pos;

	(void)shell;
	exec.tokens_head = tokens;
	exec.temp = tokens;
	exec.pid = NULL;
	exec.stts = 0;
	exec.nbr_pros = 1;
	exec.cmd = tokens_matrix(exec.temp);
	while (exec.temp)
	{
		if (exec.temp->type == PIPE)
			exec.nbr_pros++;
		exec.temp = exec.temp->next;
	}
	if (exec.nbr_pros <= 0)
	{
		free_matrix(&exec.cmd);
		exec.fd = NULL;
		return (exec);
	}
	exec.fd = ft_calloc(exec.nbr_pros, sizeof(int *));
	if (!exec.fd)
	{
		free_matrix(&exec.cmd);
		return (exec);
	}
	pos = -1;
	while (++pos < (exec.nbr_pros - 1))
	{
		exec.fd[pos] = ft_calloc(2, sizeof(int));
		if (!exec.fd[pos])
		{
			while (--pos >= 0)
				free(exec.fd[pos]);
			free(exec.fd);
			free_matrix(&exec.cmd);
			return (exec);
		}
	}
	pos = -1;
	while (++pos < exec.nbr_pros - 1)
		pipe(exec.fd[pos]);
	exec.temp = exec.tokens_head;
	return (exec);
}

void	exec_cmd(t_minishell *shell)
{
	int		cmd_pos;
	t_exec	exec;
	t_token	*tokens_copy;

	if (!shell->tokens || !shell->tokens->value || !*shell->tokens->value)
		return ;
	tokens_copy = cpy_token_ls(shell->tokens);
	exec = init_exec(shell, tokens_copy);
	if (!exec.fd)
	{
		free_matrix(&exec.cmd);
		free_tokens(tokens_copy);
		return ;
	}
	if (is_buildin(exec.cmd[0]))
	{
		exec_builtin(shell->tokens, shell);
		free_matrix(&exec.cmd);
		sfree_int(exec.fd);
		free_tokens(tokens_copy);
		return;
	}
	cmd_pos = exec_parent(shell, exec.nbr_pros, exec.cmd, exec.fd);
	if (cmd_pos > 0)
		free_matrix(&exec.cmd);
	if (cmd_pos == 0)
	{
		free_matrix(&exec.cmd);
		sfree_int(exec.fd);
		free_tokens(tokens_copy);
		return;
	}
	exec_child(shell, &exec, cmd_pos);
	cleanup_processes(&exec, shell, cmd_pos);
	free_matrix(&exec.cmd);
	sfree_int(exec.fd);
	free(exec.pid);
	free_tokens(tokens_copy);
}

char	**prepare_args(t_token *tokens)
{
	char	**args;
	int		arg_pos;
	t_token	*current;

	if (!tokens)
		return (NULL);
	args = malloc(sizeof(char *) * (count_tokens(tokens) + 1));
	if (!args)
	{
		// sfree(args);
		return (NULL);
	}
	current = tokens;
	arg_pos = 0;
	while (current)
	{
		args[arg_pos] = ft_strdup(current->value);
		if (!args[arg_pos])
		{
			free_matrix(&args);
			return (NULL);
		}
		arg_pos++;
		current = current->next;
	}
	args[arg_pos] = NULL;
	return (args);
}

int	exec_builtin(t_token *tokens, t_minishell *shell)
{
	char	**args;
	int		ret;

	args = prepare_args(tokens);
	if (!args)
	{
		// sfree(args);
		return (-1);
	}
	ret = check_builtin_type(args, shell, &ret);
	free_matrix(&args);
	return (ret);
}