#include "minishell.h"

int	check_memory(t_env **tmp_env, t_list **tmp_list)
{
	if (tmp_env == NULL || tmp_list == NULL)
	{
		put_error(MEMPROBLEM, 1);
		return (1);
	}
	return (0);
}

void	expander(t_env *env, t_list **line_splited)
{
	t_env	**tmp_env;
	t_list	**tmp_list;
	char	*tmp_str;

	tmp_env = (t_env **)ft_calloc(0, sizeof(t_env *));
	tmp_list = (t_list **)ft_calloc(0, sizeof(t_list *));
	if (check_memory(tmp_env, tmp_list) == 1)
		return ;
	*tmp_env = env;
	*tmp_list = *line_splited;
	while (*tmp_list != NULL)
	{
		tmp_str = ft_strdup((*tmp_list)->content);
		if (tmp_str == NULL)
			return ;
		if (ft_strchr(tmp_str, '$') != 0)
		{
			free((*tmp_list)->content);
			(*tmp_list)->content = expand(tmp_str, *tmp_env);
		}
		ft_free_char(tmp_str);
		tmp_str = NULL;
		*tmp_list = list_next(tmp_list);
	}
	free_expander(tmp_env, tmp_list);
}

char	*join_expand2(char *str, int i, char *end_str)
{
	char	*tmp;
	int		start;
	char	*join;

	start = i;
	while (str[i] && str[i] != '$' && str[i] != '\'' && str[i] != '\"')
		i++;
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

char	*join_expand3(char *str, int i, char *end_str)
{
	char	*tmp;
	int		start;
	char	*join;

	start = i;
	while (str[i] && str[i] != '$')
		i++;
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
