#include "minishell.h"

void	init_process(t_process *process)
{
	process->next_process = NULL;
	process->command = NULL;
	process->argv = NULL;
	process->args = NULL;
	process->pid = 0;
	process->infile = NULL;
	process->in_fd = 0;
	process->outfile = NULL;
	process->outf = 1;
	process->appendf = 1;
	process->outfile_append = NULL;
	process->here_doc = NULL;
	process->stderr = 2;
	process->completed = 0;
	process->stopped = 0;
	process->status = 0;
}

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	check_mem(char **str)
{
	if (!str)
	{
		put_error(MEMPROBLEM, 1);
		return (1);
	}
	return (0);
}

char	**list_to_array(t_list *list)
{
	char	**array;
	int		i;
	t_list	*tmp;

	i = ft_lstsize(list);
	tmp = NULL;
	array = (char **)malloc(sizeof(char *) * (i + 1));
	if (check_mem(array) == 1)
		return (NULL);
	i = 0;
	tmp = list;
	if (!tmp)
	{
		free(array);
		return (NULL);
	}
	while (tmp)
	{
		array[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

int	check_redir(char *tmp_word)
{
	if (tmp_word == NULL)
		return (0);
	if (ft_strncmp(tmp_word, "|", 2) == 0
		|| ft_strncmp(tmp_word, ">", 2) == 0
		|| ft_strncmp(tmp_word, ">>", 3) == 0
		|| ft_strncmp(tmp_word, "<<", 3) == 0
		|| ft_strncmp(tmp_word, "<", 2) == 0)
	{
		put_error(UNEXPECTEDTOKEN, 2);
		return (1);
	}
	return (0);
}
