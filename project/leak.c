void	*ft_calloc(size_t num_el, size_t numby)
{
	void	*memaloc;
	size_t	finsize;

	memaloc = NULL;
	finsize = num_el * numby;
	if (num_el == 0 || numby == 0 || finsize / num_el != numby)
		return (NULL);
	memaloc = malloc(finsize);
	if (memaloc)
		ft_bzero(memaloc, finsize);
	return (memaloc);
}

char	*ft_strdup(const char *str0)
{
	int		cnt;
	char	*str1;

	cnt = 0;
	str1 = malloc(ft_strlen(str0) + 1);
	if (!str1)
		return (NULL);
	while (*str0)
		str1[cnt++] = *str0++;
	str1[cnt] = '\0';
	return (str1);
}

char	**dup_env(char **envp, size_t *envsz)
{
	char	**nwenv;
	int		cnt;
	int		pos;

	cnt = 0;
	if (envp)
		while (envp[cnt])
			cnt++;
	*envsz = cnt;
	nwenv = ft_calloc(cnt + 1, sizeof(char *));
	if (!nwenv)
		return (NULL);
	pos = -1;
	while (++pos < cnt)
	{
		nwenv[pos] = ft_strdup(envp[pos]);
		if (!nwenv[pos])
		{
			while (--pos >= 0)
				free(nwenv[pos]);
			free(nwenv);
			return (NULL);
		}
	}
	return (nwenv);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.env = dup_env(envp, &shell.env_size);
	shell.prompt = NULL;
	shell.exit_stt = 0;
	welcome();
	while (1)
	{
		ms_prompt(&shell);
	}
	free_env(shell.env);
	return (0);
}