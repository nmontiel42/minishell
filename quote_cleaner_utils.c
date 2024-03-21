#include "minishell.h"

char	*add_quot_substr(int start, int i, char *str, char *end_str)
{
	char	*tmp_str;
	char	*join;

	tmp_str = ft_substr(str, start, i - start - 1);
	if (!end_str)
	{
		end_str = ft_strdup(tmp_str);
		ft_free_char(tmp_str);
		return (end_str);
	}
	else
	{
		join = ft_strjoin(end_str, tmp_str);
		ft_free_char(tmp_str);
		ft_free_char(end_str);
		return (join);
	}
}

char	*add_substr(int start, int i, char *str, char *end_str)
{
	char	*tmp_str;
	char	*join;

	tmp_str = ft_substr(str, start, i - start);
	if (!tmp_str)
	{
		put_error(MEMPROBLEM, 1);
		return (NULL);
	}
	if (!end_str)
	{
		end_str = ft_strdup(tmp_str);
		ft_free_char(tmp_str);
		return (end_str);
	}
	else
	{
		join = ft_strjoin(end_str, tmp_str);
		ft_free_char(tmp_str);
		ft_free_char(end_str);
		return (join);
	}
}
