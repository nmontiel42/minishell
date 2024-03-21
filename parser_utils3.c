#include "minishell.h"

void	add_heredoc(t_list **here_doc, char *word)
{
	if (!(*here_doc))
		*here_doc = ft_lstnew(word);
	else
		ft_lstadd_back(here_doc, ft_lstnew(word));
}

void	parse_final(t_process **process, t_list **tmp)
{
	if ((*process)->argv)
		(*process)->args = list_to_array((*process)->argv);
	free_list_dp(tmp);
	if (process != NULL)
	{
		free (process);
		process = NULL;
	}
}

void	handle_command_pipe_redir(t_process **tmp_process, t_list **tmp)
{
	if ((*tmp)->content == NULL)
		return ;
	if (is_redir((*tmp)->content) == 1)
	{
		if ((*tmp)->next == NULL)
		{
			put_error(SINTAXERROR, 2);
			return ;
		}
		handle_redirection(tmp, *tmp_process);
	}
	else if (ft_strncmp((*tmp)->content, "|", 2) == 0)
	{
		if ((*tmp)->next == NULL)
		{
			put_error(SINTAXERROR, 2);
			return ;
		}
		handle_pipe(tmp_process, *tmp);
	}
	else
		handle_command(tmp_process, *tmp);
}

void	check_redirs(char *tmp_word, char *tmp_word_next,
			t_process *tmp_process)
{
	if (ft_strncmp(tmp_word, ">", 2) == 0)
		check_outfile(tmp_word_next, tmp_process);
	else if (ft_strncmp(tmp_word, ">>", 3) == 0)
		check_outfile_append(tmp_word_next, tmp_process);
	else if (ft_strncmp(tmp_word, "<<", 3) == 0)
		add_heredoc(&tmp_process->here_doc, tmp_word_next);
	else if (ft_strncmp(tmp_word, "<", 2) == 0)
		check_infile(tmp_word_next, tmp_process);
}

int	check_parser_pipe(t_list **tmp, t_process **tmp_process)
{
	if (ft_strcmp((*tmp)->content, "|") == 0)
	{
		put_error(UNEXPECTEDTOKEN, 2);
		free(tmp);
		free(tmp_process);
		return (1);
	}
	return (0);
}
