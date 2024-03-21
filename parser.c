#include "minishell.h"

//extern int g_status;

void	handle_redirection(t_list **tmp, t_process *tmp_process)
{
	t_list	*tmp_next;
	char	*tmp_word_next;
	char	*tmp_word;

	if ((*tmp)->content == NULL)
		return ;
	tmp_word = ft_strdup((*tmp)->content);
	if ((*tmp)->next != NULL)
		tmp_next = (*tmp)->next;
	else
		tmp_next = NULL;
	if (tmp_next && tmp_next->content != NULL)
		tmp_word_next = ft_strdup(tmp_next->content);
	else
		tmp_word_next = NULL;
	if (check_redir(tmp_word_next) == 0)
		check_redirs(tmp_word, tmp_word_next, tmp_process);
	ft_free_char(tmp_word_next);
	ft_free_char (tmp_word);
	if (tmp_next != NULL)
		*tmp = tmp_next;
}

void	handle_pipe(t_process **tmp_process, t_list *tmp)
{
	t_process	*next_pr;
	char		*tmp_word;

	if (tmp->next == NULL)
	{
		put_error(UNEXPECTEDTOKEN, 2);
		return ;
	}
	tmp_word = ft_strdup(tmp->next->content);
	check_pipe(tmp_word);
	next_pr = (t_process *)malloc(sizeof(t_process));
	if (!next_pr)
	{
		put_error(MEMPROBLEM, 1);
		return ;
	}
	(*tmp_process)->args = list_to_array((*tmp_process)->argv);
	init_process(next_pr);
	(*tmp_process)->next_process = next_pr;
	*tmp_process = (*tmp_process)->next_process;
	ft_free_char(tmp_word);
}

void	handle_command(t_process **tmp_process, t_list *tmp)
{
	char		*tmp_word;

	tmp_word = ft_strdup((tmp->content));
	if ((*tmp_process)->command == NULL || *(*tmp_process)->command == '\0')
		(*tmp_process)->command = ft_strdup(tmp_word);
	else
	{
		if (!((*tmp_process)->argv))
			(*tmp_process)->argv = ft_lstnew(tmp_word);
		else
			ft_lstadd_back(&(*tmp_process)->argv,
				ft_lstnew(tmp_word));
	}
	free(tmp_word);
	tmp_word = NULL;
}

int	is_redir(char *tmp_word)
{
	if (tmp_word == NULL)
		return (0);
	if (ft_strncmp(tmp_word, ">", 2) == 0
		|| ft_strncmp(tmp_word, ">>", 3) == 0
		|| ft_strncmp(tmp_word, "<<", 3) == 0
		|| ft_strncmp(tmp_word, "<", 2) == 0)
		return (1);
	return (0);
}

void	parse(t_process *process, t_list **words_splited)
{
	t_list		**tmp;
	t_process	**tmp_process;

	tmp_process = (t_process **)malloc(sizeof(t_process *));
	tmp = (t_list **)malloc(sizeof(t_list *));
	if (!tmp || !tmp_process)
	{
		put_error(MEMPROBLEM, 1);
		return ;
	}
	*tmp = *words_splited;
	init_process(process);
	*tmp_process = process;
	if (check_parser_pipe(tmp, tmp_process) == 1)
		return ;
	while (*tmp)
	{
		handle_command_pipe_redir(tmp_process, tmp);
		*tmp = (*tmp)->next;
	}
	parse_final(tmp_process, tmp);
	return ;
}
