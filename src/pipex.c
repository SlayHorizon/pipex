#include "pipex.h"

void	execute(char *argv, char **envp)
{
	char	*path;
	char	**cmd;

	path = NULL;
	cmd = ft_split(argv, ' ');
	if (is_empty_string(argv))
		exit_on_custom_error(CMD_ERROR, 127);
	if (!cmd)
		return ;
	if (is_absolue_path(cmd[0]))
	{
		if (access(cmd[0], F_OK | X_OK) != 0)
			free_and_exit_on_cmd_error(cmd, 1);
		path = cmd[0];
	}
	else
		path = find_path(cmd[0], envp);
	if (!path)
	{
		free_split(cmd);
		exit_on_custom_error(CMD_ERROR, 127);
	}
	execve(path, cmd, envp);
	free(path);
	free_and_exit_on_cmd_error(cmd, 0);
}

void	child_process(char **argv, char **envp, int *fd)
{
	int	infile_fd;

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	infile_fd = open(argv[1], O_RDONLY);
	if (errno == 2)
		error_message(FILE_ERROR);
	if (errno == 13)
		error_message(PERM_ERRROR);
	if (infile_fd == -1)
		exit (EXIT_FAILURE);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	execute(argv[2], envp);
	exit(EXIT_FAILURE);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	outfile_fd;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		exit_on_custom_error(PERM_ERRROR, EXIT_FAILURE);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	execute(argv[3], envp);
	exit(EXIT_FAILURE);
}

int	wait_processes(pid_t parent_pid, int nb_process)
{
	int		i;
	int		status;
	int		parent_status;
	pid_t	wait_pid;

	i = 0;
	status = 0;
	parent_status = 0;
	while (i < nb_process)
	{
		wait_pid = wait(&status);
		if (wait_pid == -1)
			error_message(PERM_ERRROR);
		else if (wait_pid == parent_pid)
		{
			parent_status = WEXITSTATUS(status);
			if (parent_status != 0)
				return (parent_status);
		}
		i++;
	}
	if (WIFEXITED(parent_status))
		return (WEXITSTATUS(parent_status));
	else
		return (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		exit_on_error(ARGC_ERROR);
	if (pipe(fd) == -1)
		exit_on_error(FILE_ERROR);
	pid1 = fork();
	if (pid1 == -1)
		exit_on_error(FORK_ERROR);
	else if (pid1 == 0)
		child_process(argv, envp, fd);
	pid2 = fork();
	if (pid2 == -1)
		exit_on_error(FORK_ERROR);
	else if (pid2 == 0)
		parent_process(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	return (wait_processes(pid2, 2));
}
