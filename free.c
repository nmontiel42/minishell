#include "minishell.h"

void	free_temp(char **temp)
{
	int	i;

	i = 0;
	if (temp)
	{
		while (temp[i])
		{
			free(temp[i]);
			temp[i] = NULL;
			i++;
		}
		free(temp);
		temp = NULL;
	}
}

void	free_echo(char **str)
{
	int	i;

	i = 0;
	if (*str != NULL)
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		if (str)
			free(str);
		str = NULL;
	}
}

void	free_list_p(t_list **tmp)
{
	t_list	*next;

	while (*tmp != NULL)
	{
		if ((*tmp)->next != NULL)
			next = (*tmp)->next;
		else
			next = NULL;
		if (*tmp != NULL)
		{
			free(*tmp);
			*tmp = NULL;
		}
		*tmp = next;
	}
	next = NULL;
}

void	free_list(t_list **list)
{
	t_list	*next;

	while (*list != NULL)
	{
		if ((*list)->next != NULL)
			next = (*list)->next;
		else
			next = NULL;
		if ((*list)->content != NULL)
		{
			free((*list)->content);
			(*list)->content = NULL;
			free(*list);
		}
		*list = next;
	}
	if (list != NULL)
		free_list_p(list);
	return ;
}

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		temp = env;
		env = env->next;
		free(temp->name);
		temp->name = NULL;
		free(temp->value);
		temp->value = NULL;
		free(temp);
		temp = NULL;
	}
}
