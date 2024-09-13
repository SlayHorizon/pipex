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

void	process(char *cmd, char **envp, int to_wait, int *exit_status)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit_on_error(FILE_ERROR);
	pid = fork();
	if (pid == -1)
		exit_on_error(FORK_ERROR);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execute(cmd, envp);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	if (to_wait && pid == 0)
		*exit_status = wait_processes(pid, 2);
}

int	open_files(int argc, char **argv)
{
	int	infile_fd;
	int	outfile_fd;
	int	return_value;

	infile_fd = 0;
	outfile_fd = 0;
	return_value = 2;
	if (set_infile(argv[1], argv[2], &infile_fd))
	{
		if (argc < 6)
			exit_on_error(ARGC_ERROR);
		return_value++;
		outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
		outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		exit_on_custom_error(PERM_ERRROR, EXIT_FAILURE);
	dup2(infile_fd, STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(infile_fd);
	return (return_value);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		arg_idx;
	int		exit_status;
	int		next_is_parent;

	next_is_parent = 0;
	exit_status = 0;
	if (argc < 5)
		exit_on_error(ARGC_ERROR);
	arg_idx = open_files(argc, argv);
	while (arg_idx < argc - 2)
	{
		process(argv[arg_idx], envp, next_is_parent, &exit_status);
		next_is_parent = !next_is_parent;
		arg_idx++;
	}
	pid = fork();
	if (pid == -1)
		exit_on_error(FORK_ERROR);
	if (pid == 0)
		execute(argv[argc - 2], envp);
	exit_status = wait_processes(pid, 2);
	return (exit_status);
}
