#include "minishell.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

void	split_iterator(char **str, char d, char *aux, int *flag)
{
	while ((**str == d || **str == '\'' || **str == '\"') && **str != '\0')
	{
		if (**str == '\'' || **str == '\"')
		{
			*aux = **str;
			*flag = !*flag;
		}
		(*str)++;
	}
}

size_t	wordscount(char *str, char d)
{
	size_t	cnt;
	int		flag;
	char	aux;

	cnt = 0;
	flag = 0;
	while (*str)
	{
		split_iterator(&str, d, &aux, &flag);
		if (*str != '\'' && *str != '\"' && *str != d)
			cnt++;
		if (flag)
			while (*str != aux && *str)
				str++;
		else
			while (*str != d && *str)
				str++;
	}
	return (cnt);
}

int	wordlen(char *str, char d, int flag, char c)
{
	int		flag2[2];
	char	aux;

	flag2[0] = flag;
	flag2[1] = 0;
	aux = c;
	if (flag2[0])
	{
		while (*str != aux && *str)
		{
			flag2[1]++;
			str++;
		}
	}
	else
	{
		while (*str != d && *str)
		{
			flag2[1]++;
			str++;
		}
	}
	return (flag2[1]);
}

char	**new_split_version(char *s, char d)
{
	char	**new_str;
	int		i;
	int		flag;
	char	aux;
	int		word_len;

	i = -1;
	flag = 0;
	new_str = ft_calloc(wordscount(s, d) + 1, sizeof(char *));
	if (!new_str)
		return (NULL);
	//printf("25.0.new_str pointer = %p\n", new_str);
	while (*s)
	{
		split_iterator(&s, d, &aux, &flag);
		while ((*s != aux && flag) || (*s != d && !flag && *s))
		{
			word_len = wordlen(s, d, flag, aux);
			new_str[++i] = ft_calloc(word_len + 1, sizeof(char));
			//printf("25.0.1.new_str[%i] pointer = %p\n", i, new_str);
			if (!new_str[i])
				return (free_split(new_str), NULL);
			ft_strlcpy(new_str[i], s, word_len + 1);
			s += word_len;
		}
	}
	return (new_str[++i] = NULL, new_str);
}
