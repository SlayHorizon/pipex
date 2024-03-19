/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atreus <atreus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:39:31 by atreus            #+#    #+#             */
/*   Updated: 2024/03/19 23:27:59 by atreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

# define RED_COLOR "\033[31m"

# define ARGC_ERROR "Invalid number of arguments.\n"
# define FILE_ERROR "No such file or directory\n"
# define FORK_ERROR "Crash on fork().\n"
# define COMD_ERROR "Command not found.\n"
# define PERM_ERRROR "Permission denied\n"
# define EXEC_ERROR "Error on exec.\n"

# define PERM_DENIED_CODE 126
# define NOT_FOUND_CODE 127

// utils.c
void	exit_on_error(char *error_message, int exit_code);
void	execute(char *argv, char **envp);

// string_utils.c
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

// ft_split.c
char	**ft_split(char const *str, char c);
char	**free_split(char **tab);

#endif
