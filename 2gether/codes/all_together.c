/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_together.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:24:28 by vgomes-p          #+#    #+#             */
/*   Updated: 2025/01/15 14:04:28 by vgomes-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_cd(char **args)
{
	char	*home;

	if (!args[1])
	{
		home = getenv("HOME");
		if (home)
			chdir(home);
		else
			ft_putstr_fd("cd: HOME not set\n", 2);
	}
	else
	{
		if (chdir(args[1]) == -1)
			perror("cd");
	}
}

void	ms_echo(char **args)
{
	int	index;
	int	nwline;

	index = 1;
	nwline = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		nwline = 0;
		index++;
	}
	while (args[index])
	{
		ft_putstr(args[index]);
		if (args[index + 1])
			ft_putstr(" ");
		index++;
	}
	if (nwline)
		ft_putstr("\n");
}

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

extern char	**environ;

void	ms_env(void)
{
	int	index;

	index = 0;
	while (environ[index])
	{
		ft_putstr(environ[index]);
		ft_putstr("\n");
		index++;
	}
}

extern char	**environ;

void	ms_export(char **args)
{
	char	*equal_sign;
	int		index;

	if (args[1])
	{
		equal_sign = ft_strchr(args[1], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			setenv(args[1], equal_sign + 1, 1);
		}
		else
		{
			index = 0;
			while (environ[index])
			{
				ft_putstr(environ[index]);
				ft_putstr("\n");
				index++;
			}
		}
	}
	else
		ft_putstr_fd("export: usage: export VAR+VALUE\n", 2);
}

void	ms_unset(char **args)
{
	if (args[1])
	{
		unsetenv(args[1]);
	}
	else
		ft_putstr_fd("unset: usage: unset VAR\n", 2);
}

void	ms_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr(cwd);
		ft_putstr("\n");
		free(cwd);
	}
	else
		ft_putstr_fd("pwd: error\n", 2);
}

void	ms_exec_builtin(char **tokens, t_minishell *shell)
{
	if (ft_strcmp(tokens[0], "cd") == 0)
		ms_cd(tokens);
	else if (ft_strcmp(tokens[0], "echo") == 0)
		ms_echo(tokens);
	else if (ft_strcmp(tokens[0], "exit") == 0)
		ms_exit(tokens, shell);
	else if (ft_strcmp(tokens[0], "env") == 0)
		ms_env();
	else if (ft_strcmp(tokens[0], "export") == 0)
		ms_export(tokens);
	else if (ft_strcmp(tokens[0], "unset") == 0)
		ms_unset(tokens);
	else if (ft_strcmp(tokens[0], "pwd") == 0)
		ms_pwd();
	else
		ft_putstr_fd("command not found\n", 2);
}

void	ms_process_buildin(char *input, t_minishell *shell)
{
	char	**tokens;
	int		index;

	tokens = ft_split(input, ' ');
	if (!tokens || !tokens[0])
	{
		free(tokens);
		return ;
	}
	ms_exec_builtin(tokens, shell);
	index = 0;
	while (tokens[index])
	{
		free(tokens[index]);
		index++;
	}
	free(tokens);
}

void	ms_inishell(t_minishell *shell)
{
	shell->prompt = ft_strdup("\033[1;36mminishell$ > \033[0m");
	if (!shell->prompt)
	{
		perror("Error initializing prompt");
		exit (1);
	}
	ft_putstr("                         \033[1;7;36m");
	ft_putstr("{Made by vgomes-p & sthrodri\033[0m\n\n");
	ft_putstr("\n\033[1;36m╔═════════════════════════════════════");
	ft_putstr("═════════════════════════════════════════╗\n");
	ft_putstr("║                            WELCOME T");
	ft_putstr("O MINISHELL                              ║\n");
	ft_putstr("╚══════════════════════════════════════");
	ft_putstr("════════════════════════════════════════╝\033[0m\n");
}

void	ms_interact1(t_minishell *shell)
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

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	(void)envp;
	ms_inishell(&shell);
	ms_interact1(&shell);
	free(shell.prompt);
	return (0);
}
