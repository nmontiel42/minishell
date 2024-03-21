#include "minishell.h"

extern int	g_status;

void	env_add_back(t_env **root, t_env *new)
{
	t_env	*ptr;

	ptr = *root;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

void	print_split(char **line_splited)
{
	int	i;

	i = 0;
	while (line_splited[i] != NULL)
		i++;
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_strends(const char *str, const char *end)
{
	size_t	len_str;
	size_t	len_end;

	len_str = ft_strlen(str);
	len_end = ft_strlen(end);
	if (len_end > len_str)
		return (0);
	return (ft_strncmp(str + len_str - len_end, end, len_end) == 0);
}

void	free_commands(t_process *process)
{
	if (process->path_env)
		free(process->path_env);
	if (process->env)
		free_string_array(process->env);
}
