#include "minishell.h"

extern int	g_status;

void	redirect_infile(t_process *process)
{
	int	fd;

	if (process->infile != NULL)
	{
		fd = open(process->infile, O_RDONLY);
		if (fd == -1)
		{
			perror("Error opening input file");
			exit(g_status);
		}
		dup2(fd, STDIN_FILENO);
		if (close(fd) == -1)
		{
			perror("Error closing input file descriptor");
			exit(g_status);
		}
	}
}

void	redirect_outfile(t_process *process)
{
	int	flags;
	int	fd;

	if (process->outfile != NULL || process->outfile_append != NULL)
	{
		flags = O_WRONLY | O_CREAT;
		if (process->appendf == 1)
		{
			flags |= O_TRUNC;
			fd = open(process->outfile, flags, 0666);
		}
		if (process->appendf == 2)
		{
			flags |= O_APPEND;
			fd = open(process->outfile_append, flags, 0666);
		}
		if (fd == -1)
			put_error2(OPENERROR, 1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			put_error2(REDIRECTOUT, 1);
		close(fd);
	}
}
