#include "minishell.h"

int	check_f_d(t_process *process)
{
	struct stat	file_info;
	t_list		*aux;
	int			i;

	i = 0;
	aux = process->argv;
	while (aux && ft_strchr(aux->content, '-'))
	{
		while (aux->content[i])
		{
			if (ft_isdigit(aux->content[i]))
				return (0);
			i++;
		}
		aux = aux->next;
	}
	if ((aux && (stat(aux->content, &file_info) == 0 || !aux->content))
		|| aux == NULL)
		return (1);
	return (0);
}

char	*ft_strndup(const char *str, size_t n)
{
	size_t	len;
	char	*new_str;
	size_t	i;

	if (str == NULL)
		return (NULL);
	len = 0;
	while (len < n && str[len] != '\0')
		len++;
	new_str = (char *)malloc(len + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[len] = '\0';
	return (new_str);
}

char	*obtain_env_name(char *fullenv)
{
	int	i;

	i = 0;
	if (fullenv[0] == '=' && !fullenv[1])
		return (ft_strdup("="));
	while (fullenv[i] && fullenv[i] != '=' && fullenv[i] != ' ')
		i++;
	return (ft_substr(fullenv, 0, i));
}

char	*obtain_env_value(char *fullenv)
{
	int	i;

	i = 0;
	while (fullenv[i] && fullenv[i] != '=' && fullenv[i] != ' ')
		i++;
	return (ft_substr(fullenv, i + 1, ft_strlen(fullenv) - i));
}

void	free_unset(t_env *del)
{
	free(del->name);
	free(del->value);
	free(del);
}
