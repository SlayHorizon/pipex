#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

# define ARGC_ERROR "Invalid number of arguments.\n"
# define FILE_ERROR "No such file or directory.\n"
# define FORK_ERROR "Crash on fork().\n"
# define CMD_ERROR "Command not found.\n"
# define PERM_ERRROR "Permission denied.\n"
# define EXEC_ERROR "Error on exec.\n"
# define MALLOC_ERROR "Malloc failed.\n"

# define PERM_DENIED_CODE 126
# define NOT_FOUND_CODE 127

// error.c
void	error_message(char *message);
void	exit_on_custom_error(char *error_message, int exit_code);
void	free_and_exit_on_cmd_error(char **to_free, int is_absolut_path_cmd);
void	exit_on_error(char *error_message);

// utils.c
void	execute(char *argv, char **envp);
char	*find_path(char *cmd, char **envp);
int		is_absolue_path(const char *path);
int		is_empty_string(const char *str);

// string_utils.c
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

// ft_split.c
char	**ft_split(char const *str, char c);
char	**free_split(char **tab);

// bonus
// here_doc.c
int		set_infile(char *file, char *limiter, int *infile_fd);
void	here_doc2(char *limiter);

#endif
