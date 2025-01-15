#include "libft.h"

void	*ft_realloc(void *ptr, size_t nwsize)
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

int	ft_putenv(char ***env, char *str)
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
	return (ft_setenv(env, name, value, 1));
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
	*env = ft_realloc(*env, sizeof(char *) * (env_size + 2));
	if (!(*env))
	{
		free(env_in);
		return (-1);
	}
	(*env)[env_size] = env_in;
	(*env)[env_size + 1] = NULL;
	return (0);
}

int	ft_setenv(char ***env, const char *name, const char *value, int overwrite)
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

int	ft_unsetenv(char ***env, const char *name)
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