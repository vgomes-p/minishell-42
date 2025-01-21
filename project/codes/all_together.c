#include "../includes/minishell.h"
#include "../includes/libft/libft.h"
#include <stdbool.h>

/* LIBMS */

void	lms_putchar(char ch)
{
	write(1, &ch, 1);
}


void	lms_putstr(char *str)
{
	if (str)
	{
		while (*str)
		{
			write(1, str, 1);
			str++;
		}
	}
}

int	lms_strcmp(const char *s1, const char *s2)
{
	return (ft_strncmp(s1, s2, 1000000));
}

void	*lms_realloc(void *ptr, size_t nwsize)
{
	void	*nwptr;
	size_t	oldsz;

	if (!ptr)
		return (malloc(nwsize));
	oldsz = malloc_usable_size(ptr);
	if (nwsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	nwptr = malloc(nwsize);
	if (!nwptr)
	{
		free(ptr);
		return (NULL);
	}
	if (oldsz < nwsize)
		ft_memcpy(nwptr, ptr, oldsz);
	else
		ft_memcpy(nwptr, ptr, nwsize);
	free(ptr);
	return (nwptr);
}

int	lms_putenv(char ***env, char *str)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	if (!env || !str)
		return (-1);
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return (-1);
	*equal_sign = '\0';
	name = str;
	value = equal_sign + 1;
	return (lms_setenv(env, name, value, 1));
}

static int	create_env_string(const char *name,
							const char *value, char **result)
{
	char	*env_in;

	if (!name || !value || !result)
		return (-1);
	env_in = ft_strjoin(name, "=");
	if (!env_in)
		return (-1);
	*result = ft_strjoin(env_in, value);
	free(env_in);
	if (!(*result))
		return (-1);
	return (0);
}

static int	update_existing_env(char **env, const char *name,
							char *env_in, int overwrite)
{
	int	index;

	index = 0;
	while (env[index])
	{
		if (ft_strncmp(env[index], name, ft_strlen(name)) == 0
			&& env[index][ft_strlen(name)] == '=')
		{
			if (overwrite)
			{
				free(env[index]);
				env[index] = env_in;
			}
			else
				free(env_in);
			return (1);
		}
		index++;
	}
	return (0);
}

static int	add_new_env(char ***env, char *env_in, int env_size)
{
	*env = lms_realloc(*env, sizeof(char *) * (env_size + 2));
	if (!(*env))
	{
		free(env_in);
		return (-1);
	}
	(*env)[env_size] = env_in;
	(*env)[env_size + 1] = NULL;
	return (0);
}

int	lms_setenv(char ***env, const char *name, const char *value, int overwrite)
{
	char	*env_in;
	int		env_size;

	if (create_env_string(name, value, &env_in) == -1)
		return (-1);
	if (!env || !*env)
	{
		free(env_in);
		return (-1);
	}
	if (update_existing_env(*env, name, env_in, overwrite))
		return (0);
	env_size = 0;
	while ((*env)[env_size])
		env_size++;
	return (add_new_env(env, env_in, env_size));
}

static int	find_env_var(char **env, const char *name)
{
	int	index;

	index = 0;
	while (env[index])
	{
		if (ft_strncmp(env[index], name, ft_strlen(name)) == 0
			&& env[index][ft_strlen(name)] == '=')
			return (index);
		index++;
	}
	return (-1);
}

static void	shift_env_vars(char **env, int start_index)
{
	while (env[start_index + 1])
	{
		env[start_index] = env[start_index + 1];
		start_index++;
	}
	env[start_index] = NULL;
}

int	lms_unsetenv(char ***env, const char *name)
{
	int	index;

	if (!env || !name || !(*env))
		return (-1);
	index = find_env_var(*env, name);
	if (index == -1)
		return (0);
	free((*env)[index]);
	shift_env_vars(*env, index);
	return (0);
}
/*NOVAAAAAS*/

char	*lms_strncpy(char *dest, const char *src, size_t n)
{
	size_t cnt;

	cnt = 0;
	while (cnt < n && src[cnt] != '\0')
	{
		dest[cnt] = src[cnt];
		cnt++;
	}
	while (cnt < n)
	{
		dest[cnt] = '\0';
		cnt++;
	}
	return (dest);
}

char *lms_strndup(const char *str, size_t n)
{
	char *dup;

	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	lms_strncpy(dup, str, n);
	dup[n] = '\0';
	return (dup);
}

/* ************************** */
/*      MINISHELL  CODES      */
/* ************************** */

/* ******* */
/* utils 0 */
/* ******* */

void	ms_error(const char *msg, t_minishell *shell)
{
	if (shell)
		shell->error_message = ft_strdup(msg);
	ft_putstr_fd("Error!\n", 2);
}

/* ********* */
/* parsing 1 */
/* ********* */
int	ms_quotes(const char *input, int start, char **output)
{
	int		pos;
	char	quote;

	pos = start;
	quote = input[start - 1];
	while (input[pos] != '\0')
	{
		if (input[pos] == quote)
		{
			*output = (char *)malloc(pos - start);
			if (!(*output))
				return (-1);
			lms_strncpy(*output, input + start, pos - start);
			(*output)[pos - start] = '\0';
			return (1);
		}
		pos++;
	}
	return (-1);
}


extern char	**environ;

/* *********** */
/* build-ins 1 */
/* *********** */
void	ms_cd(char **args)
{
	char	*home;

	if (!args[1])
	{
		home = getenv("HOME");
		if (home)
			chdir(home);
		else
			ft_putstr_fd("cd: \033[1;33mHOME not set\033[0m\n", 2);
	}
	else
	{
		if (chdir(args[1]) == -1)
			perror("cd");
	}
}

/* *********** */
/* build-ins 2 */
/* *********** */

void	ms_echo(char **args)
{
	int	index;
	int	nwline;

	index = 1;
	nwline = 1;
	if (args[1] && lms_strcmp(args[1], "-n") == 0)
	{
		nwline = 0;
		index++;
	}
	while (args[index])
	{
		lms_putstr(args[index]);
		if (args[index + 1])
			lms_putstr(" ");
		index++;
	}
	if (nwline)
		lms_putstr("\n");
}

/* *********** */
/* build-ins 3 */
/* *********** */

void	ms_exit(char **args, t_minishell *shell)
{
	int	stat;

	stat = 0;
	if (args[1])
		stat = ft_atoi(args[1]);
	shell->exit_stt = stat;
	free(shell->prompt);
	exit(stat);
}

/* *********** */
/* build-ins 4 */
/* *********** */

void	ms_env(void)
{
	int	index;

	index = 0;
	while (environ[index])
	{
		lms_putstr(environ[index]);
		lms_putstr("\n");
		index++;
	}
}

/* *********** */
/* build-ins 5 */
/* *********** */

static void	display_environment(char **env)
{
	int	index;

	index = 0;
	while (env[index])
	{
		lms_putstr(env[index]);
		lms_putstr("\n");
		index++;
	}
}

static int	handle_variable_assignment(char ***env, char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (0);
	*equal_sign = '\0';
	if (lms_setenv(env, arg, equal_sign + 1, 1) == -1)
	{
		ft_putstr_fd("export: \033[1;31merror setting variable\033[0m\n", 2);
		*equal_sign = '=';
		return (-1);
	}
	*equal_sign = '=';
	return (1);
}

void	ms_export(char ***env, char **args)
{
	if (!args[1])
	{
		ft_putstr_fd("export: not enough args\nusage: export VAR=VALUE\n", 2);
		return ;
	}
	if (handle_variable_assignment(env, args[1]) == 0)
		display_environment(*env);
}

/* *********** */
/* build-ins 6 */
/* *********** */

void	ms_unset(char ***env, char **args)
{
	if (args[1])
	{
		if (lms_unsetenv(env, args[1]) == -1)
			ft_putstr_fd("unset: \033[1;31merror unsetting variable\033[0m\n", 2);
	}
	else
		ft_putstr_fd("unset: not enough args\nusage: unset VAR\n", 2);
}

/* *********** */
/* build-ins 7 */
/* *********** */

void	ms_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		lms_putstr(cwd);
		lms_putstr("\n");
		free(cwd);
	}
	else
		ft_putstr_fd("pwd: \033[1;31merror\033[0m\n", 2);
}


/* *********** */
/* build-ins 8 */
/* *********** */

static void	handle_quotes(char *input, int *pos, int *tokencnt, char ***tokens, t_minishell *shell)
{
	char	*quote_content;
	int		finalquote;

	quote_content = NULL;
	finalquote = ms_quotes(input, *pos + 1, &quote_content);
	if (finalquote == -1)
	{
		ms_error("unmatched quotes detected", shell);
		return ;
	}
	(*tokencnt)++;
	*tokens = lms_realloc(*tokens, sizeof(char *) * ((*tokencnt) + 1));
	(*tokens)[*tokencnt - 1] = quote_content;
	(*tokens)[*tokencnt] = NULL;
	*pos += ft_strlen(quote_content) + 2;
}

static void	handle_non_quotes(char *input, int *pos, int *tokencnt, char ***tokens)
{
	int		start;
	char	*tokenstt;

	start = *pos;
	while (input[*pos] && input[*pos] != ' ' && input[*pos] != '\'' && input[*pos] != '\"')
	{
		(*pos)++;
	}
	tokenstt = lms_strndup(input + start, *pos - start);
	(*tokencnt)++;
	*tokens = lms_realloc(*tokens, sizeof(char *) * ((*tokencnt) + 1));
	(*tokens)[*tokencnt - 1] = tokenstt;
	(*tokens)[*tokencnt] = NULL;
}

static void	process_input(char *input, char ***tokens, t_minishell *shell)
{
	int	pos;
	int	tokencnt;

	pos = 0;
	tokencnt = 0;
	*tokens = NULL;
	while (input[pos])
	{
		if (input[pos] == ' ')
		{
			pos++;
			continue;
		}
		if (input[pos] == '\'' || input[pos] == '\"')
			handle_quotes(input, &pos, &tokencnt, tokens, shell);
		else
			handle_non_quotes(input, &pos, &tokencnt, tokens);
		if (!*tokens)
			return ;
	}
}

void	ms_tokenize_input(char *input, char ***tokens, t_minishell *shell)
{
	process_input(input, tokens, shell);
}

/* ********* */
/* build-ins */
/* ********* */
static void	execute_builtin_command(char **tokens, t_minishell *shell)
{
	if (lms_strcmp(tokens[0], "echo") == 0)
		ms_echo(tokens);
	else if (lms_strcmp(tokens[0], "env") == 0)
		ms_env();
	else if (lms_strcmp(tokens[0], "unset") == 0)
		ms_unset(&(shell->env), tokens);
	else if (lms_strcmp(tokens[0], "export") == 0)
		ms_export(&(shell->env), tokens);
	else if (lms_strcmp(tokens[0], "pwd") == 0)
		ms_pwd();
	else if (lms_strcmp(tokens[0], "cd") == 0)
		ms_cd(tokens);
	else
		ms_error("\033[1;31mcommand not found!\n\033[0m", shell);
}

static void	cleanup_tokens(char **tokens)
{
	int	index;

	index = 0;
	while (tokens && tokens[index])
	{
		free(tokens[index]);
		index++;
	}
	free(tokens);
}

void	ms_process_buildin(char *input, t_minishell *shell)
{
	char	**tokens;

	ms_tokenize_input(input, &tokens, shell);
	if (tokens && tokens[0])
		execute_builtin_command(tokens, shell);
		
	cleanup_tokens(tokens);
}
// void	ms_process_buildin(char *input, t_minishell *shell)
// {
// 	char	**tokens;
// 	int		start;
// 	int		pos;
// 	char	*quote_content;
// 	int		finalquote;
// 	int		tokencnt;
// 	char	*tokenstt;
// 	int		index1;

// 	tokens = NULL;
// 	pos = 0;
// 	tokencnt = 0;
// 	tokenstt = NULL;
// 	while (input[pos])
// 	{
// 		if (input[pos] == ' ')
// 		{
// 			pos++;
// 			continue ;
// 		}
// 		if (input[pos] == '\'' || input[pos] == '\"')
// 		{
// 			quote_content = NULL;
// 			finalquote = ms_quotes(input, pos + 1, &quote_content);
// 			if (finalquote == -1)
// 			{
// 				ms_error("unmatched quotes detected", shell);
// 				return ;
// 			}
// 			tokencnt++;
// 			tokens = lms_realloc(tokens, sizeof(char *) * (tokencnt + 1));
// 			tokens[tokencnt -1 ] = quote_content;
// 			tokens[tokencnt] = NULL;
// 			pos += ft_strlen(quote_content) + 2;
// 		}
// 		else
// 		{
// 			start = pos;
// 			while (input[pos] && input[pos] != ' ' && input[pos] != '\'' && input[pos] != '\"')
// 				pos++;
// 			tokenstt = lms_strndup(input + start, pos - start);
// 			tokencnt++;
// 			tokens = lms_realloc(tokens, sizeof(char *) * (tokencnt + 1));
// 			tokens[tokencnt - 1] = tokenstt;
// 			tokens[tokencnt] = NULL;
// 		}
// 	}
// 	if (tokens && tokens[0])
// 	{
// 		if (lms_strcmp(tokens[0], "echo") == 0)
// 			ms_echo(tokens);
// 		else if (lms_strcmp(tokens[0], "env") == 0)
// 			ms_env();
// 		else if (lms_strcmp(tokens[0], "unset") == 0)
// 			ms_unset(&(shell->env), tokens);
// 		else if (lms_strcmp(tokens[0], "export") == 0)
// 			ms_export(&(shell->env), tokens);
// 		else if (lms_strcmp(tokens[0], "pwd") == 0)
// 			ms_pwd();
// 		else if (lms_strcmp(tokens[0], "cd") == 0)
// 			ms_cd(tokens);
// 		else
// 			ms_error("\033[1;31mcommand not found!\n\033[0m", shell);
// 	}
// 	index1 = 0;
// 	while (index1 < tokencnt)
// 	{
// 		free(tokens[index1]);
// 		index1++;
// 	}
// 	free(tokens);
// }

/* ******** */
/* interact */
/* ******** */

void	ms_inishell(t_minishell *shell)
{
	shell->prompt = ft_strdup("\033[1;36mminishell$ > \033[0m");
	if (!shell->prompt)
	{
		perror("\033[1;31mError initializing prompt\033[0m");
		exit (1);
	}
	lms_putstr("                         \033[1;7;36m");
	lms_putstr("{Made by vgomes-p & sthrodri\033[0m\n\n");
	lms_putstr("\n\033[1;36m╔═════════════════════════════════════");
	lms_putstr("═════════════════════════════════════════╗\n");
	lms_putstr("║                            WELCOME T");
	lms_putstr("O MINISHELL                              ║\n");
	lms_putstr("╚══════════════════════════════════════");
	lms_putstr("════════════════════════════════════════╝\033[0m\n");
}

void	ms_interact0(t_minishell *shell)
{
	char	*input;

	while (1)
	{
		input = readline(shell->prompt);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		ms_process_buildin(input, shell);
		free(input);
	}
	rl_clear_history();
}

/* ********* */
/* minishell */
/* ********* */

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.env = envp;
	ms_inishell(&shell);
	ms_interact0(&shell);
	free(shell.prompt);
	return (0);
}
