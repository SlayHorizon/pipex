/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atreus <atreus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:28:51 by atreus            #+#    #+#             */
/*   Updated: 2024/03/19 23:27:39 by atreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int	infile_fd;

	infile_fd = open(argv[1], O_RDONLY, 0777);
	if (infile_fd == -1)
		exit_on_error(PERM_ERRROR, PERM_DENIED_CODE);
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	outfile_fd;

	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		exit_on_error(PERM_ERRROR, EXIT_FAILURE);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc != 5)
		exit_on_error(ARGC_ERROR, EXIT_FAILURE);
	if (pipe(fd) == -1)
		exit_on_error(FILE_ERROR, EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		exit_on_error(FORK_ERROR, EXIT_FAILURE);
	if (pid1 == 0)
		child_process(argv, envp, fd);
	waitpid(pid1, NULL, 0);
	parent_process(argv, envp, fd);
	exit(EXIT_SUCCESS);
}
