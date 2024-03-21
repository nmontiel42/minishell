#include "minishell.h"

static int	len_split(char *line, int i)
{
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = search_end_quoted_string(line[i], line, i + 1);
		else
			i++;
	}
	return (i);
}

void	init_list(t_list **list)
{
	*list = (t_list *)ft_calloc(0, sizeof(t_list));
	if (*list == NULL)
	{
		put_error(MEMPROBLEM, 1);
		return ;
	}
	(*list)->content = NULL;
	(*list)->next = NULL;
}

void	create_line_splited(char *line, t_list **list)
{
	char	*tmp_word;
	int		i;
	int		start;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		if (line[i] != ' ' && line[i])
		{
			start = i;
			i = len_split(line, i);
			tmp_word = ft_substr(line, start, i - start);
			if ((*list)->content == NULL)
				(*list)->content = ft_strdup(tmp_word);
			else
				ft_lstadd_back(list, ft_lstnew(tmp_word));
			free (tmp_word);
			tmp_word = NULL;
		}
	}
}

void	ft_free_list(t_list **list)
{
	free_list(list);
	free(list);
	list = NULL;
}

void	lexer(t_data *shell, t_list **redir_splited)
{
	char	*line;
	t_list	**pipes_splited;
	t_list	**words_splited;

	pipes_splited = (t_list **)ft_calloc(0, sizeof(t_list *));
	words_splited = (t_list **)ft_calloc(0, sizeof(t_list *));
	if (!words_splited || !pipes_splited)
	{
		put_error(MEMPROBLEM, 1);
		free(words_splited);
		free(pipes_splited);
		return ;
	}
	init_list(words_splited);
	init_list(pipes_splited);
	line = ft_strdup(shell->line);
	create_line_splited(line, words_splited);
	ft_free_char(line);
	split_pipes(words_splited, pipes_splited);
	ft_free_list(words_splited);
	split_redirections(pipes_splited, redir_splited);
	ft_free_list(pipes_splited);
	expander(shell->env, redir_splited);
	quot_cleaner(redir_splited);
	return ;
}
