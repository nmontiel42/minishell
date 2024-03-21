#include "minishell.h"

char	*handle_quoted_string(char *str, int *i, char *end_str)
{
	int		start;

	start = *i + 1;
	*i = search_end_quoted_string(str[*i], str, *i + 1);
	end_str = add_quot_substr(start, *i, str, end_str);
	return (end_str);
}

char	*handle_unquoted_string(char *str, int *i, char *end_str)
{
	int		start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	end_str = add_substr(start, *i, str, end_str);
	return (end_str);
}

void	update_list_content(t_list **list, char *end_str)
{
	if ((*list)->content)
	{
		free((*list)->content);
		(*list)->content = NULL;
	}
	(*list)->content = ft_strdup(end_str);
	ft_free_char (end_str);
}

void	clean_str_quot(char *str, t_list **list)
{
	int		i;
	char	*end_str;

	i = 0;
	end_str = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			end_str = handle_quoted_string(str, &i, end_str);
		else
		{
			end_str = handle_unquoted_string(str, &i, end_str);
			if (!end_str)
			{
				ft_free_char (end_str);
				break ;
			}
		}
	}
	if (end_str != NULL)
		update_list_content(list, end_str);
	return ;
}

void	quot_cleaner(t_list **list)
{
	t_list	**tmp;
	char	*tmp_word;

	tmp = (t_list **)ft_calloc(0, sizeof(t_list *));
	if (!tmp)
	{
		put_error(MEMPROBLEM, 1);
		return ;
	}
	*tmp = *list;
	while (*tmp != NULL)
	{
		tmp_word = ft_strdup((*tmp)->content);
		if (tmp_word != NULL)
		{
			clean_str_quot(tmp_word, tmp);
			ft_free_char (tmp_word);
		}
		if ((*tmp)->next != NULL)
			*tmp = (*tmp)->next;
		else
			*tmp = NULL;
	}
	free (tmp);
	tmp = NULL;
}
