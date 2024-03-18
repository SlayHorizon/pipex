/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschneid <tschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:39:31 by atreus            #+#    #+#             */
/*   Updated: 2024/03/15 14:52:03 by tschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# define RED_COLOR "\033[31m"
# define ARGC_ERROR "Invalid number of arguments.\n"
# define FILE_ERROR "Error while trying to read file.\n\
Given input file path may be incorrect.\n"
# define FORK_ERROR "Crash on fork().\n"
# define COMD_ERROR "Command doesn't exit.\n"
# define EXEC_ERROR "Error on exec\n"

// utils.c
void	exit_on_error(char *error_message);
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
