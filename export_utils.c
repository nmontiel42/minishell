#include "minishell.h"

void	only_export(t_data *shell)
{
	t_env	*current;

	current = shell->env;
	while (current)
	{
		printf("declare -x %s", current->name);
		if (current->value)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

void	create_variable(char *variable, t_data *shell)
{
	t_env	*new_env;
	char	*name;
	char	*value;

	name = obtain_env_name(variable);
	if (ft_strcmp(name, "=") == 0)
	{
		put_error(NOTVALID, 1);
		ft_free_char(name);
		return ;
	}
	value = obtain_env_value(variable);
	if (!check_if_exists(name, value, shell))
	{
		new_env = new_node(name, value);
		env_add_back(&shell->env, new_env);
	}
	free(value);
}

bool	check_args(char *arg, char *cmd)
{
	int		i;
	char	*name;

	i = 0;
	(void)cmd;
	name = obtain_env_name(arg);
	if (ft_isdigit(name[i]) || name[i] == '-')
	{
		put_error2(NOTVALID, 1);
		return (free(name), false);
	}
	while (name[i])
	{
		if (ft_isalnum(name[i]))
			i++;
		else
		{
			put_error2(NOTVALID, 1);
			return (free(name), false);
		}
	}
	return (free(name), true);
}

int	check_if_exists(char *name, char *value, t_data *shell)
{
	t_env	*ptr;

	ptr = shell->env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->name, name, ft_strlen(name)))
		{
			free(ptr->value);
			ptr->value = ft_strdup(value);
			free(name);
			return (1);
		}
		ptr = ptr->next;
	}
	free(name);
	return (0);
}

t_env	*new_node(char *name, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->name = ft_strdup(name);
	if (value == NULL)
		env->value = NULL;
	else
		env->value = ft_strdup(value);
	env->next = NULL;
	return (env);
}
