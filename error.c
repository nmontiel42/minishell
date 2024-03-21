#include "minishell.h"

extern int	g_status;

void	put_error(int error_type, int error_code)
{
	g_status = error_code;
	if (error_type == DEQUOTE)
		printf("minishell: error: dequoted line\n");
	else if (error_type == NOTFILEORDIR)
		perror("minishell: error: No such file or directory");
	else if (error_type == NOTPERMISSION)
		perror("minishell: error: Permission denied");
	else if (error_type == NOTCOMMAND)
		perror("minishell: error: command not found");
	else if (error_type == DUPERROR)
		printf("minishell: error: fd duplication failed\n");
	else if (error_type == FORKERROR)
		printf("minishell: error: fork failed\n");
	else if (error_type == PIPEERROR)
		printf("minishell: error: pipe failed\n");
	else if (error_type == UNEXPECTEDTOKEN)
		perror("minishell: error: syntax error near unexpected token");
	else if (error_type == MEMPROBLEM)
		printf("minishell: error: memory allocation failed\n");
	else if (error_type == ISDIR)
		perror("minishell: error: Is a directory");
	else if (error_type == NOTDIR)
		printf("minishell: error: Not a directory\n");
	else
		put_error2(error_type, error_code);
}

void	put_error2(int error_type, int error_code)
{
	g_status = error_code;
	if (error_type == NUMARG)
		perror("minishell: exit: a: numeric argument required.");
	else if (error_type == TOMANYARG)
		perror("minishell: exit: too many arguments");
	else if (error_type == NOTVALID)
		perror("minishell: is not a valid identifier");
	else if (error_type == OPENERROR)
		printf("minishell: error: open failed\n");
	else if (error_type == ARGS)
		printf("minishell: error: wrong number of arguments\n");
	else if (error_type == CLOSEERROR)
		printf("minishell: error: close failed\n");
	else if (error_type == SINTAXERROR)
		perror("minishell: error: syntax error near unexpected`newline'");
	else if (error_type == REDIRECTOUT)
		perror("minishell: error redirecting output");
}
