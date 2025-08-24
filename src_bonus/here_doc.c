#include "pipex.h"

char	*add_to_save(char *save, char to_add)
{
	int		i;
	int		j;
	size_t	total_len;
	char	*new_save;

	i = 0;
	j = 0;
	total_len = ft_strlen(save) + 1;
	new_save = malloc(total_len + 1);
	if (!new_save)
		return (0);
	if (save)
	{
		while (save[i])
		{
			new_save[i] = save[i];
			i++;
		}
	}
	new_save[i++] = to_add;
	new_save[i] = '\0';
	free(save);
	return (new_save);
}

int	get_next_line(char **line)
{
	char	*save;
	int		readc;
	char	c;

	readc = 1;
	readc = read(0, &c, 1);
	save = malloc(1);
	if (!save)
		return (-1);
	*save = '\0';
	while (readc && c != '\n' && c != '\0')
	{
		save = add_to_save(save, c);
		readc = read(0, &c, 1);
		if (readc < 0)
		{
			free(save);
			return (0);
		}
	}
	*line = save;
	return (readc);
}

int	set_infile(char *file, char *limiter, int *infile_fd)
{
	int	is_here_doc;

	is_here_doc = 0;
	if (ft_strncmp("here_doc", file, 8) == 0)
	{
		is_here_doc = 1;
		here_doc2(limiter);
		*infile_fd = open("heredoc_tmp", O_RDONLY);
		if (infile_fd < 0)
		{
			unlink("heredoc_tmp");
			exit_on_custom_error("HERDOC_ERROR", 1);
		}
	}
	else
		*infile_fd = open(file, O_RDONLY);
	if (errno == 2)
		error_message(FILE_ERROR);
	if (errno == 13)
		error_message(PERM_ERRROR);
	if (*infile_fd == -1)
		exit (EXIT_FAILURE);
	return (is_here_doc);
}

void	here_doc2(char *limiter)
{
	char	*buffer;
	int		here_doc_fd;

	here_doc_fd = open("heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		write(1, "here_doc> ", 10);
		if (get_next_line(&buffer) == -1)
			exit(EXIT_FAILURE);
		if (ft_strncmp(limiter, buffer, ft_strlen(limiter) + 1) == 0)
			break ;
		write(here_doc_fd, buffer, ft_strlen(buffer));
		write(here_doc_fd, "\n", 1);
		free(buffer);
	}
	if (buffer)
		free(buffer);
	close(here_doc_fd);
}
