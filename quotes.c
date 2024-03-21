#include "minishell.h"

int	check_closed_quotes(char *line, int q, int i, char in_quot);

char	set_in_quot(char *line, int i)
{
	char	in_quot;

	if (line[i] == '\'')
		in_quot = '\'';
	else
		in_quot = '\"';
	return (in_quot);
}

int	check_quotes(char *line, int q, int i)
{
	char	quote;
	char	d_quote;
	char	in_quot;

	in_quot = 0;
	quote = 39;
	d_quote = 34;
	while (line[i])
	{
		if (line[i] == quote || line[i] == d_quote)
		{
			q++;
			in_quot = set_in_quot(line, i);
			i++;
			q = check_closed_quotes(line, q, i, in_quot);
			return (q);
		}
		i++;
	}
	return (q);
}

int	check_closed_quotes(char *line, int q, int i, char in_quot)
{
	while (line[i])
	{
		if (line[i] == in_quot)
		{
			q++;
			i++;
			if (line[i] != '\0')
			{
				q = check_quotes(line, q, i);
				return (q);
			}
		}
		i++;
	}
	return (q);
}
