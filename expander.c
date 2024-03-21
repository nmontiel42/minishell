#include "minishell.h"

extern int	g_status;

char	*get_expanded_value(t_env *env, char *key)
{
	char	*value;
	t_env	**tmp;
	char	*name;

	tmp = NULL;
	tmp = init_tmp_env(tmp);
	*tmp = env;
	name = NULL;
	while (*tmp != NULL)
	{
		name = ft_strdup((*tmp)->name);
		if (ft_strncmp(key, name, ft_strlen(name)) == 0)
		{
			value = ft_strdup((*tmp)->value);
			return (free(tmp), free (name), value);
		}
		if (name)
			free(name);
		if ((*tmp)->next)
			*tmp = (*tmp)->next;
		else
			*tmp = NULL;
	}
	value = ft_strdup("");
	return (free(tmp), value);
}

char	*get_status(char *str)
{
	char	*value;
	char	*join;

	value = ft_itoa(g_status);
	if (str[1])
	{
		join = ft_strjoin(value, str + 1);
		free (value);
		return (join);
	}
	return (value);
}

char	*join_expand_value(char *value, char *end_str, char *tmp)
{
	char	*join;

	join = ft_strjoin(end_str, value);
	ft_free_char(value);
	ft_free_char(end_str);
	ft_free_char(tmp);
	return (join);
}

char	*expand_value(char *str, int i, t_env *env, char *end_str)
{
	char	*value;
	char	*tmp;
	char	*join;

	tmp = set_key(str, i);
	if (ft_strncmp(tmp, "$", 1) != 0 && ft_strncmp(tmp, "?", 1) != 0)
		value = get_expanded_value(env, tmp);
	else if (ft_strncmp(tmp, "?", 1) == 0)
		value = get_status(tmp);
	else
		value = ft_strdup(tmp);
	if (!end_str)
	{
		end_str = ft_strdup(value);
		if (tmp && tmp != NULL && *tmp != '\0')
			ft_free_char(tmp);
		ft_free_char(value);
		return (end_str);
	}
	else
	{
		join = join_expand_value(value, end_str, tmp);
		return (join);
	}
}

char	*join_expand(char *str, int start, char *end_str, int i)
{
	char	*tmp;
	char	*join;

	tmp = ft_substr(str, start, i - start);
	if (!end_str)
	{
		end_str = ft_strdup(tmp);
		ft_free_char(tmp);
		return (end_str);
	}
	else
	{
		join = ft_strjoin(end_str, tmp);
		ft_free_char(end_str);
		return (ft_free_char(tmp), join);
	}
}
