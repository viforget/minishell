#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../lib/libft/libft.h"

/*
// index value:
//	0 : binary
//	1 : echo
//	2 : pwd
//	3 : env
//	4 : cd
//	5 : export
//	6 : unset
//	7 : exit
//
// bin : path to the binary if index == 0
//
// av : tab to send to the binary
//
// pipe :
//	0 : no pipe
//	1 : pipe betwen 2 commands
//	2 : >  between the command and a file (char *file)
//	3 : >> between the command and a file (char *file)
//	
// guil : <  between the command and a file (char *file_g)
*/

typedef struct s_command
{
	int		index;
	char	*bin;
	char	**av;
	int		pipe;
	int		guil;
	char	*file;
	char	*file_g;
	struct s_command *next;
}				t_command;

typedef struct s_var
{
	char	*name;
	char	*content;
	struct s_var *next;
}				t_var;

/*
// PARSER_C
*/

t_command	*parser(char *order, char **env);

/*
// PIPE_ARCH_C
*/

void	recurs_pipe(t_command *ins, int fd_p[2], int pip, char **env);

#endif