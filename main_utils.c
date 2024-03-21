#include "minishell.h"

extern int	g_status;

void	executor(t_process *process, t_data *shell, t_list **redir_splited)
{
	lexer(shell, redir_splited);
	parse(process, redir_splited);
	ft_free_list(redir_splited);
	shell->echo = ft_split(shell->line, ' ');
	if ((shell->echo && shell->echo[0] != NULL))
	{
		if (*shell->line)
			add_history(shell->line);
		if (is_builtin(process, shell))
			execute_builtin(process, shell);
		if (!is_builtin(process, shell))
			main_executor(shell, process);
		free(shell->line);
		free_echo(shell->echo);
		shell->line = NULL;
		if (process != NULL)
			free_process(process);
	}
	else
	{
		free(shell->line);
		shell->line = NULL;
	}
}

void	check_quotes_and_executor(t_process *process, t_data *shell,
	t_list **redir_splited)
{
	int	q;

	q = check_quotes(shell->line, 0, 0);
	if (q % 2 != 0)
	{
		put_error(DEQUOTE, 1);
		free (redir_splited);
		free (process);
		rl_replace_line("", 0);
	}
	else if (shell->line && *shell->line)
		executor(process, shell, redir_splited);
}

void	ctrl_d(t_data *shell)
{
	if (shell->line == NULL)
	{
		printf("exit\n");
		exit(g_status);
	}
}

void	is_space(t_data *shell)
{
	int	i;

	i = 0;
	while (shell->line[i] == ' ')
		i++;
	if (shell->line[i] == '\0')
	{
		free(shell->line);
		shell->line = NULL;
	}
}

void	extra_cases(t_data *shell)
{
	ctrl_d(shell);
	is_space(shell);
}
