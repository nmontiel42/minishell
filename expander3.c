#include "minishell.h"

char	*expand_single_quote(char *str, int *i, char *end_str)
{
	int	start;

	start = *i;
	*i = search_end_quoted_string(str[*i], str, *i + 1);
	return (join_expand(str, start, end_str, *i));
}

char	*expand_double_quote(char *str, int *i, t_env *env, char *end_str)
{
	int		start;
	char	*tmp;
	char	*expand;

	start = *i;
	*i = search_end_quoted_string(str[*i], str, *i + 1);
	tmp = ft_substr(str, start, *i - start);
	if (tmp == NULL)
		return (NULL);
	if (ft_strchr(tmp, '$') != 0)
	{
		expand = expand_quoted(tmp, env);
		ft_free_char(tmp);
		end_str = join_expand_quoted(end_str, expand);
	}
	else
	{
		end_str = join_expand_quoted(end_str, tmp);
		ft_free_char(tmp);
	}
	return (end_str);
}

char	*expand_dollar(char *str, int *i, t_env *env, char *end_str)
{
	(*i)++;
	end_str = expand_value(str, *i, env, end_str);
	while (str[*i] && str[*i] != '$' && str[*i] != ' '
		&& str[*i] != '\"' && str[*i] != '\'')
		(*i)++;
	return (end_str);
}

char	*expand_else(char *str, int *i, char *end_str)
{
	end_str = join_expand2(str, *i, end_str);
	*i = search_end_str(str, *i);
	return (end_str);
}
