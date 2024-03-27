/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atreus <atreus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:33:14 by tschneid          #+#    #+#             */
/*   Updated: 2024/03/27 23:43:17 by atreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_message(char *message)
{
	write(2, message, ft_strlen(message));
}

void	exit_on_custom_error(char *error_message, int exit_code)
{
	write(2, error_message, ft_strlen(error_message));
	exit(exit_code);
}

void	free_and_exit_on_cmd_error(char **to_free, int is_absolut_path_cmd)
{
	int	exit_code;

	exit_code = 1;
	free_split(to_free);
	if (errno == EACCES)
	{
		exit_code = 126;
		write(2, PERM_ERRROR, ft_strlen(PERM_ERRROR));
	}
	else if (errno == ENOENT)
	{
		exit_code = 127;
		if (is_absolut_path_cmd)
			write(2, FILE_ERROR, ft_strlen(FILE_ERROR));
		else
			write(2, CMD_ERROR, ft_strlen(CMD_ERROR));
	}
	exit(exit_code);
}

void	exit_on_error(char *error_message)
{
	int	exit_code;

	exit_code = 1;
	if (!error_message)
	{
		if (errno == EACCES)
			write(2, PERM_ERRROR, ft_strlen(PERM_ERRROR));
		else if (errno == ENOENT)
			write(2, FILE_ERROR, ft_strlen(FILE_ERROR));
	}
	else
		write(2, error_message, ft_strlen(error_message));
	exit(exit_code);
}
