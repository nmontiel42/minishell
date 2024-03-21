#include "minishell.h"

int	g_status;

/*void	ft_header(void)
{
	printf("\n");
	printf("               ╔╗ ╔╦═══╗ \n");
	printf("               ║║ ║║╔═╗║ \n");
	printf("               ║╚═╝╠╝╔╝║ \n");
	printf("               ╚══╗╠═╝╔╝ \n");
	printf("                  ║║║╚═╗ \n");
	printf("                  ╚╩═══╝ \n");
	printf("   ╔═╗╔═╦══╦═╗ ╔╦══╦═══╦╗ ╔╦═══╦╗  ╔╗    \n");
	printf("   ║║╚╝║╠╣╠╣║╚╗║╠╣╠╣╔═╗║║ ║║╔══╣║  ║║    \n");
	printf("   ║╔╗╔╗║║║║╔╗╚╝║║║║╚══╣╚═╝║╚══╣║  ║║    \n");
	printf("   ║║║║║║║║║║╚╗║║║║╚══╗║╔═╗║╔══╣║ ╔╣║ ╔╗ \n");
	printf("   ║║║║║╠╣╠╣║ ║║╠╣╠╣╚═╝║║ ║║╚══╣╚═╝║╚═╝║ \n");
	printf("   ╚╝╚╝╚╩══╩╝ ╚═╩══╩═══╩╝ ╚╩═══╩═══╩═══╝ \n");
	printf("\n");
}*/

void	initialize_minishell(t_data **shell, char **env)
{
	(void)env;
	g_status = 0;
	*shell = (t_data *)malloc(sizeof(t_data));
	if (!*shell)
	{
		put_error(MEMPROBLEM, 1);
		exit(g_status);
	}
}

void	start_minishell(t_data *shell)
{
	t_list		**redir_splited;
	t_process	*process;

	while (1)
	{
		setup_signal_handlers();
		//system("leaks -q minishell");
		if (shell->line)
			free(shell->line);
		shell->line = readline("Minishell@ ~ ");
		extra_cases(shell);
		if (shell->line && *shell->line)
		{
			redir_splited = (t_list **)malloc(sizeof(t_list *));
			process = (t_process *)malloc(sizeof(t_process));
			if (!redir_splited || !process)
			{
				put_error(MEMPROBLEM, 1);
				return ;
			}
		}
		if (shell->line == NULL)
			printf("");
		else
			check_quotes_and_executor(process, shell, redir_splited);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data		*shell;

	(void)argv;
	if (argc == 1)
	{
		shell = NULL;
		initialize_minishell(&shell, env);
		copy_env_to_data(shell, env);
		shell->line = NULL;
		if (argc == 1)
		{
			//ft_header();
			start_minishell(shell);
		}
		free(shell->line);
		free_echo(shell->echo);
		free(shell);
		clear_history();
		return (g_status);
	}
	put_error(ARGS, 1);
}

/*void	ft_leaks(void)
{
	system("leaks -q minishell");
}*/
