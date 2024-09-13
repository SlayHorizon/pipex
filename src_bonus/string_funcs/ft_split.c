#include "pipex.h"

char	**free_split(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

size_t	ft_nb_words(char const *str, char c)
{
	size_t	i;
	size_t	nb_words;

	i = 0;
	nb_words = 0;
	if (!str)
		return (i);
	while (str[i] == c && str[i])
		i++;
	while (str[i])
	{
		if (str[i] != c)
		{
			nb_words++;
			while (str[i] != c && str[i])
				i++;
		}
		else
			i++;
	}
	return (nb_words);
}

void	get_next_word(char **next_word, size_t *next_word_len, char c)
{
	size_t	i;

	i = 0;
	*next_word += *next_word_len;
	*next_word_len = 0;
	while (**next_word && **next_word == c)
		(void)*(*next_word)++;
	while ((*next_word)[i])
	{
		if ((*next_word)[i] == c)
			return ;
		(*next_word_len)++;
		i++;
	}
}

char	**ft_split(char const *str, char c)
{
	size_t	i;
	size_t	next_word_len;
	char	**tab;
	char	*next_word;

	i = 0;
	next_word_len = 0;
	if (!str)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_nb_words(str, c) + 1));
	next_word = (char *)str;
	while (i < ft_nb_words(str, c))
	{
		get_next_word(&next_word, &next_word_len, c);
		tab[i] = malloc(next_word_len + 1);
		if (tab[i] == NULL)
			return (free_split(tab));
		ft_strlcpy(tab[i], next_word, next_word_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
