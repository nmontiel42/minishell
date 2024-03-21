#include "minishell.h"

extern int	g_status;

void	env_command(t_data *shell)
{
	t_env	*head;

	head = shell->env;
	while (head)
	{
		if (head != NULL && head->value)
			printf("%s=%s\n", head->name, head->value);
		head = head->next;
	}
	g_status = 0;
}

void	pwd_command(t_data *shell, t_process *process)
{
	char	*path;

	(void)process;
	(void)shell;
	path = malloc(sizeof(char) * 100);
	path = getcwd(path, 100);
	printf("%s\n", path);
	free(path);
	g_status = 0;
}

void	echo_command(t_process *process, int exists)
{
	int		i;
	char	*arg;
	t_list	*aux;

	aux = process->argv;
	while (aux != NULL)
	{
		arg = (char *)aux->content;
		if (ft_strncmp(arg, "-n", 2) == 0)
			exists = 1;
		i = 0;
		while (arg[i] != '\0' && ft_strcmp(&arg[i], "-n") != 0)
		{
			printf("%c", arg[i]);
			i++;
		}
		if (aux->next != NULL)
			printf(" ");
		aux = aux->next;
	}
	if (!exists)
		printf("\n");
	g_status = 0;
}

void	unset_command(t_data *shell, char *name)
{
	t_env	*aux;
	t_env	*del;
	t_env	*prev;

	if (!name)
		return ;
	aux = shell->env;
	prev = NULL;
	while (aux)
	{
		if (ft_strcmp(aux->name, name) == 0)
		{
			del = aux;
			if (prev)
				prev->next = aux->next;
			else
				shell->env = aux->next;
			free_unset(del);
			g_status = 0;
			return ;
		}
		prev = aux;
		aux = aux->next;
	}
}

void	export_command(t_process *process, t_data *shell)
{
	if (process->command && !process->args)
	{
		only_export(shell);
		g_status = 0;
	}
	else
	{
		while (process->argv->content)
		{
			if (check_args(process->argv->content, process->argv->content))
			{
				create_variable(process->argv->content, shell);
				g_status = 0;
			}
			break ;
		}
	}
}
