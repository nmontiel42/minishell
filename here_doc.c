#include "minishell.h"

static void	execute_command_with_heredoc(t_process *process, int fd_read,
		t_data *shell)
{
	char	**argv;
	int		fd_pipe[2];
	pid_t	pid;
	char	*full_path;
	int		i;

	i = 0;
	find_path(process, shell);
	while (process->env[i++] != NULL)
	{
		process->temp = ft_strjoin(process->env[i], "/");
		full_path = ft_strjoin(process->temp, process->command);
		if (access(full_path, F_OK | X_OK) != -1)
		{
			argv = create_argv2(argv, process);
			pipe(fd_pipe);
			pid = fork();
			if (pid == 0)
				child_process2(process, fd_pipe, full_path, argv);
			else
				father_process2(fd_pipe, fd_read, pid);
			free_things(process, argv);
		}
		free_elements(process->temp, full_path);
	}
}

int	handle_heredoc(t_process *process, t_data *shell)
{
	char	*filename;
	int		fd_write;
	int		fd_read;

	if (!process->here_doc)
		return (0);
	filename = "here_doc.tmp";
	fd_write = create_temp_file(filename);
	read_lines_until_delimiter(fd_write, process->here_doc->content);
	close(fd_write);
	fd_read = open_temp_file_read(filename);
	if ((process->command || (process->command && process->args))
		&& process->here_doc)
		execute_command_with_heredoc(process, fd_read, shell);
	close(fd_read);
	unlink(filename);
	return (1);
}
