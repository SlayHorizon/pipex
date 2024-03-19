/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atreus <atreus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:22:00 by atreus            #+#    #+#             */
/*   Updated: 2024/03/19 23:27:47 by atreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

	//write(2, RED_COLOR, ft_strlen(RED_COLOR));
	//write(2, "Error\n", 7);
void	exit_on_error(char *error_message, int exit_code)
{
	write(2, error_message, ft_strlen(error_message));
	exit(exit_code);
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*path;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
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

void	execute(char *argv, char **envp)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		return ;
	if (access(cmd[0], F_OK | X_OK) != 0)
	{
		path = find_path(cmd[0], envp);
		if (!path)
		{
			free_split(cmd);
			exit_on_error(COMD_ERROR, NOT_FOUND_CODE);
		}
	}
	else
		path = cmd[0];
	if (execve(path, cmd, envp) == -1)
		exit_on_error(EXEC_ERROR, EXIT_FAILURE);
	free(path);
	free_split(cmd);
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}
