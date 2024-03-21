#include "minishell.h"

void	free_expander(t_env **tmp_env, t_list **tmp_list)
{
	if (tmp_env != NULL)
		free (tmp_env);
	tmp_env = NULL;
	if (tmp_list != NULL)
		free (tmp_list);
	tmp_list = NULL;
}

void	ft_free_char(char *str)
{
	if (str != NULL)
		free(str);
	str = NULL;
}

void	free_list_process(t_list *list)
{
	if (list != NULL)
	{
		free_list(&list);
		free(list);
		list = NULL;
	}
}

void	free_list_dp(t_list **list)
{
	if (list != NULL)
	{
		free(list);
		list = NULL;
	}
}

void	free_process(t_process *process)
{
	t_process	*tmp;
	t_process	*next;

	tmp = process;
	while (tmp)
	{
		next = tmp->next_process;
		ft_free_char(tmp->command);
		free_list_process(tmp->argv);
		ft_free_char(tmp->infile);
		ft_free_char(tmp->outfile);
		ft_free_char(tmp->outfile_append);
		free_list_process(tmp->here_doc);
		if (tmp->args)
		{
			free_echo(tmp->args);
			tmp->args = NULL;
		}
		free (tmp);
		tmp = next;
	}
}
