#include "minishell.h"

void	check_pipe(char *tmp_word)
{
	if (ft_strncmp(tmp_word, "|", 2) == 0)
		put_error(UNEXPECTEDTOKEN, 2);
	return ;
}

void	check_infile(char *tmp_word, t_process *tmp_process)
{
	if (access(tmp_word, F_OK) == -1)
		put_error(NOTFILEORDIR, 1);
	else if (access(tmp_word, R_OK) == -1)
		put_error(NOTPERMISSION, 1);
	else
		tmp_process->infile = ft_strdup(tmp_word);
}

int	check_access_outfile(char *tmp_word)
{
	if (access(tmp_word, F_OK) == -1)
	{
		put_error(NOTFILEORDIR, 1);
		return (1);
	}
	else if (access(tmp_word, W_OK) == -1)
	{
		put_error(NOTPERMISSION, 1);
		return (1);
	}
	return (0);
}

void	check_outfile(char *tmp_word, t_process *tmp_process)
{
	int	file;

	if (access(tmp_word, F_OK) == -1 || access(tmp_word, F_OK) != -1)
	{
		file = open(tmp_word, O_WRONLY | O_CREAT | O_TRUNC);
		if (file < 0)
		{
			put_error(OPENERROR, 1);
			return ;
		}
		else
			close(file);
	}
	if (access(tmp_word, W_OK) == -1)
	{
		put_error(NOTPERMISSION, 1);
		return ;
	}
	free(tmp_process->outfile);
	tmp_process->outfile = ft_strdup(tmp_word);
	tmp_process->appendf = 1;
}

void	check_outfile_append(char *tmp_word, t_process *tmp_process)
{
	int	file;

	if (access(tmp_word, F_OK) == -1 || access(tmp_word, F_OK) != -1)
	{
		file = open(tmp_word, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		if (file < 0)
		{
			put_error(OPENERROR, 1);
			return ;
		}
		else
			close(file);
	}
	else if (access(tmp_word, W_OK) == -1)
	{
		put_error(NOTPERMISSION, 1);
		return ;
	}
	free(tmp_process->outfile_append);
	tmp_process->outfile_append = ft_strdup(tmp_word);
	tmp_process->appendf = 2;
}
