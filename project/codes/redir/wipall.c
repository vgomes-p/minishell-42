#include "../../includes/minishell.h"

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*joined;

	joined = lms_strjoin_free(s1, s2); // Usa sua função lms_strjoin_free
	s2 = free_ptr(s2); // Libera s2, se necessário
	return (joined);
}

static char	*exit_status(t_minishell *shell, char *f, char *cmd)
{
	char	*ret;

	ret = NULL;
	if (!*cmd)
	{
		f = free_ptr(f);
		return (ft_strdup("$"));
	}
	if (cmd && cmd[0])
		ret = ft_strdup(++cmd);
	f = free_ptr(f);
	return (lms_strjoin_free(ft_itoa(shell->error), ret)); // Usa lms_strjoin_free
}

char	*get_envp(t_minishell *shell, char *cmd, char **envp)
{
	char	*ret;
	int		len;
	int		var_len;

	ret = cmd;
	cmd++;
	if (*cmd == '{')
		len = ft_strlen(++cmd);
	else
		len = ft_strlen(cmd);
	if (*cmd == '?' || len == 0)
		return (exit_status(shell, ret, cmd));
	while (*envp)
	{
		var_len = ft_findchr(*envp, '=');
		if (!ft_strncmp(cmd, *envp, var_len))
		{
			ret = free_ptr(ret); // Usa free_ptr
			return (ft_strdup(*envp + len + 1));
		}
		envp++;
	}
	ret = free_ptr(ret); // Usa free_ptr
	return (ft_strdup(""));
}

static t_expand	init_expantion(t_minishell *shell, char *cmd, char **envp, t_expand exp)
{
	while (cmd[++exp.end])
	{
		exp.quotes = check_quotes(cmd[exp.end], exp.quotes);
		if (cmd[exp.end] == '$' && exp.quotes != 2)
		{
			exp.hold_str[exp.ex++] = ft_substr(cmd, exp.start, exp.end - \
			exp.start);
			exp.start = exp.end;
		}
		else if (cmd[exp.start] == '$' && cmd[exp.end] != '{' && \
		!ft_isalnum(cmd[exp.end]) && cmd[exp.end] != '?' \
		&& cmd[exp.end] != '_')
		{
			exp.hold_str[exp.ex++] = get_envp(ms, ft_substr(cmd, exp.start, \
			exp.end - exp.start), envp);
			if (cmd[exp.end] == '}' && cmd[exp.start + 1] == '{' \
			&& cmd[exp.end + 1])
				exp.end++;
			exp.start = exp.end;
		}
	}
	return (exp);
}

static char	*expand_quotes(char *cmd)
{
	int		i;
	int		quotes;
	char	**ret;

	i = -1;
	quotes = 0;
	while (cmd[++i])
	{
		quotes = check_quotes(cmd[i], quotes);
		if ((cmd[i] == '\'' || cmd[i] == '\"') && !quotes)
			cmd[i] = SEP;
		else if ((cmd[i] == '\'' && quotes == 2) || \
		(cmd[i] == '\"' && quotes == 1))
			cmd[i] = SEP;
	}
	ret = ft_split(cmd, SEP);
	if (!*ret)
	{
		sfree(ret); // Usa sfree
		return (ft_strdup(""));
	}
	return (ft_mattstr_copy(ret));
}

int	is_env_directory(t_minishell *shell, char *cmd, char **envp)
{
	char			*ret;
	struct stat		file_info;
	char			*temp;

	temp = ft_strdup(cmd);
	ret = get_envp(shell, temp, envp);
	stat(ret, &file_info);
	if (S_ISDIR(file_info.st_mode) == 1)
	{
		ret = free_ptr(ret); // Usa free_ptr
		return (1);
	}
	ret = free_ptr(ret); // Usa free_ptr
	return (0);
}

char	*expand(t_minishell *shell, char *cmd, char **envp)
{
	t_expand	exp;

	ft_bzero(&exp, sizeof(t_expand));
	while (cmd[exp.i])
		exp.ex_n += 1 * (cmd[exp.i++] == '$');
	exp.ex = (exp.ex_n * 2) + 2;
	exp.hold_str = ft_calloc(exp.ex, sizeof(char *));
	if (!exp.hold_str)
		return (NULL);
	exp.ex = 0;
	exp.end = -1;
	exp = init_expantion(ms, cmd, envp, exp);
	if (cmd[exp.start] == '$')
		exp.hold_str[exp.ex++] = get_envp(ms, ft_substr(cmd, exp.start, \
		exp.end - exp.start), envp);
	else
		exp.hold_str[exp.ex++] = ft_substr(cmd, exp.start, exp.end - exp.start);
	return (ft_mattstr_copy(exp.hold_str));
}

void	expander(t_minishell *shell, t_token **head, char **envp)
{
	char	*temp;
	t_token	*token;

	token = *head;
	if (is_env_directory(shell, token->cmd, envp) == 1)
		return ;
	while (token)
	{
		if (ft_strchr(token->cmd, '$'))
		{
			temp = token->cmd;
			token->cmd = expand(shell, token->cmd, envp);
			if (token->cmd == NULL)
				token->cmd = temp;
			else
				temp = free_ptr(temp); // Usa free_ptr
		}
		if (!token->prev || (token->prev && token->prev->type != HEREDOC))
		{
			temp = token->cmd;
			token->cmd = expand_quotes(token->cmd);
			temp = free_ptr(temp); // Usa free_ptr
		}
		token = token->next;
	}
}


/*---------------------------------------------------------------*/
int	heredoc(t_minishell *shell, const char *file_end, char **envp)
{
	char	*input;
	int		heredoc_file;

	input = NULL;
	heredoc_file = open("__heredoc", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (heredoc_file == -1)
		return (-1);
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strncmp(file_end, input, ft_strlen(file_end) + 1))
		{
			input = free_ptr(input);
			break ;
		}
		if (*file_end != '\'' && *file_end != '\"' && ft_strchr(input, '$'))
			input = expand(shell, input, envp);
		write(heredoc_file, input, ft_strlen(input));
		write(heredoc_file, "\n", 1);
		input = free_ptr(input);
	}
	close(heredoc_file);
	heredoc_file = open("__heredoc", O_RDONLY);
	return (heredoc_file);
}
/*---------------------------------------------------------------*/

static int	is_redir_in(t_minishell *shell, char **cmd, int pos, char **envp)
{
	static int	in_file = -1;

	if (!ft_strncmp(cmd[pos], "<", 2))
	{
		in_file = open(cmd[pos + 1], O_RDONLY);
		if (in_file == -1)
		{
			perror("minishell"); // Usa perror para mostrar o erro
			return (-5);
		}
	}
	else if (!ft_strncmp(cmd[pos], "<<", 3))
		in_file = heredoc(shell, cmd[pos + 1], envp);
	return (in_file);
}

static int	is_redir_out(char **cmd, int pos)
{
	static int	out_file = -1;

	if (!ft_strncmp(cmd[pos], ">", 2))
	{
		out_file = open(cmd[pos + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_file == -1)
		{
			perror("minishell");
			return (-5);
		}
	}
	else if (!ft_strncmp(cmd[pos], ">>", 3))
	{
		out_file = open(cmd[pos + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (out_file == -1)
		{
			perror("minishell");
			return (-5);
		}
	}
	return (out_file);
}

static int	is_redir(char *cmd)
{
	if (!ft_strncmp(cmd, ">", 2) || !ft_strncmp(cmd, ">>", 3) ||
		!ft_strncmp(cmd, "<", 2) || !ft_strncmp(cmd, "<<", 3))
		return (1);
	return (0);
}

void	process_redirect(t_minishell *shell, char **cmd, int *fd, char **ret)
{
	int	pos;
	int	cnt;

	pos = 0;
	cnt = 0;
	while (cmd[pos])
	{
		if (is_redir(cmd[pos]))
		{
			fd[0] = is_redir_in(shell, cmd, pos, shell->env);
			fd[1] = is_redir_out(cmd, pos);
			pos += 2;
			if (fd[0] == -5 || fd[1] == -5)
				break ;
		}
		else
			ret[cnt++] = ft_strdup(cmd[pos++]);
	}
	if (cmd)
	{
		sfree(cmd);
		cmd = NULL;
	}
}

static void	ms_open_fd(int *fd)
{
	fd[0] = -1;
	fd[1] = -1;
}

char	**redirect(t_minishell *shell, char **cmd, int *out, int *in)
{
	int		fd[2];
	char	**ret;
	int		pos;

	ms_open_fd(fd);
	pos = 0;
	while (cmd[pos])
		pos++;
	ret = ft_calloc(pos + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	process_redirect(shell, cmd, fd, ret);
	if (fd[0] == -5 || fd[1] == -5)
	{
		sfree(ret);
		return (NULL);
	}
	if (fd[0] != -1)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		*in = 1;
	}
	if (fd[1] != -1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		*out = 1;
	}
	return (ret);
}


/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/
/*---------------------------------------------------------------*/

