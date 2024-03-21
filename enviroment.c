#include "minishell.h"

t_env	*copy_env_to_list(char **envp, t_data *shell)
{
	t_env	*head;
	t_env	*current;
	char	*name_value;
	char	*delim;
	t_env	*new_node;

	head = NULL;
	current = NULL;
	shell->i = 0;
	while (envp[shell->i] != NULL)
	{
		name_value = ft_strdup(envp[shell->i]);
		delim = ft_strchr(name_value, '=');
		if (delim)
		{
			new_node = create_env_node(name_value, delim + 1, shell->i);
			if (new_node)
				add_env_node(&head, &current, new_node);
		}
		free(name_value);
		shell->i++;
	}
	return (head);
}

t_env	*create_env_node(char *name, char *value, int index)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strndup(name, ft_strchr(name, '=') - name);
	new_node->value = ft_strdup(value);
	new_node->index = index;
	new_node->next = NULL;
	return (new_node);
}

void	add_env_node(t_env **head, t_env **current, t_env *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*current = new_node;
	}
	else
	{
		(*current)->next = new_node;
		*current = new_node;
	}
}

void	copy_env_to_data(t_data *data, char **envp)
{
	data->env = copy_env_to_list(envp, data);
}
