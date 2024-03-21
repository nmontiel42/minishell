#include "minishell.h"

int	get_len_word(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] != ' ' && str[i] && str[i] != '\"'
		&& str[i] != '\'' && str[i] != '$')
	{
		i++;
		len++;
	}
	return (len);
}

char	*set_key(char *str, int i)
{
	size_t	len;
	char	*tmp;

	len = get_len_word(str, i);
	if (len > 0)
	{
		tmp = ft_substr(str, i, len);
		if (tmp == NULL)
			return (NULL);
	}
	else
		tmp = ft_strdup("$");
	return (tmp);
}

t_env	**init_tmp_env(t_env **tmp)
{
	tmp = (t_env **)malloc(sizeof(t_env *));
	if (!tmp)
	{
		put_error(MEMPROBLEM, 1);
		return (NULL);
	}
	return (tmp);
}
