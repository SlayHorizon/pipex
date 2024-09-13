#include "pipex.h"

int	is_empty_string(const char *str)
{
	if (str == NULL)
		return (1);
	while (*str)
	{
		if (*str != ' ' || *str != '\n')
			return (0);
		str++;
	}
	return (1);
}

int	is_absolue_path(const char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len > 2)
		if (path[0] == '.' && path[1] == '/')
			return (1);
	if (path[0] == '/')
		return (1);
	while (*path)
	{
		if (*path == '/')
			return (1);
		path++;
	}
	return (0);
}

int	get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*path;
	char	*part_path;

	i = get_path(envp);
	if (i == -1)
		return (0);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(paths);
	return (0);
}
