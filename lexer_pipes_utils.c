#include "minishell.h"

extern int	g_status;

int	get_pipe_nbr(char *line, int i)
{
	int		pipe_nbr;

	pipe_nbr = 0;
	if (line == NULL)
		return (-1);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = search_end_quoted_string(line[i], line, i + 1);
		else if (line[i] != '\'' && line[i] != '\"' && line[i] != '|')
			i++;
		else if (line[i] == '|')
		{
			pipe_nbr++;
			i++;
		}
	}
	return (pipe_nbr);
}

int	get_pipe_index(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = search_end_quoted_string(line[i], line, i + 1);
		else if (line[i] != '\'' && line [i] != '\"' && line[i] != '|')
			i++;
		else if (line[i] == '|')
			return (i);
	}
	return (-1);
}
