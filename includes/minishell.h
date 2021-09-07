#ifndef MINISHELL_H
# define MINISHELL_H

# include	<unistd.h>
# include	<sys/wait.h>
# include	<stdlib.h>
# include	<fcntl.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<signal.h>
# include	<stdio.h>
# include	<readline/readline.h>

# include	"../lib/libft/libft.h"

int	g_exit;

/*
// index value:
//  f  0 : binary
//  f  1 : echo
//  f  2 : pwd
//  f  3 : env
//  *  4 : cd
//  *  5 : export
//  *  6 : unset
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
	int					index;
	char				*bin;
	char				**av;
	int					pipe;
	int					guil;
	char				*file;
	char				*file_g;
	struct s_command	*next;
}						t_command;

typedef struct s_var
{
	char			*name;
	char			*content;
	struct s_var	*next;
}				t_var;

/*
// PARSER_C
*/

t_command	*boucle(char *order, char **env, t_command *info);
int			file_with_g_exit(char *order);
void		file_new(char *new, char *order, char **env, int s);
char		*change_arg(char *order, char **ev);
t_command	*parser(char *order, char **env);

/*
// CUT_C
*/

char		*cut(char *text);
char		*cutg(char *text);
char		*cutb(char *txt);

/*
// BIN_C
*/

int			find_env(char **env, char *word);
int			set_index(char *order);
t_command	*set_bin(char *text, char **env, t_command *info);

/*
// AV_C
*/

int			ft_if(char x, char y, int test);
void		size_av(t_command *info, char *order, int size);
int			nb_word(char *order);
int			skip(char *txt);
void		nb_av(t_command *maillon, char *order);

/*
// TOOLS_C
*/

int			is_char(char *c, char *test);
t_command	*mal_maillon(void);
void		clean(t_command *info);
void		remplir(char *dest, char *txt, int x);
void		set_guil(int i, t_command *info, char *order, int pos);

/*
// TOOLS2_C
*/

char		*next_word(char *order);
int			size_arg(char **env, int pos);
void		setg(t_command *info, char *order, int pos);
int			ft_ctoa(unsigned char c);
char		*verif_guil(char *order);

/*
// SKIP_C
*/

int			skip(char *txt);
int			skip_hard(char *order);

/*
// MAIN_C
*/

void		free_command(t_command *st);

/*
// PIPE_ARCH_C
*/

char		**recurs_pipe(t_command *ins, int fd_p[2], int pip, char **env);

/*
// PIPE_OPEN_CLOSE_C
*/

void	double_close(int fd[2]);
void	cond_dup_close(int fd, int fd2, int nb);
void	opcl_pipe(t_command *ins, int fd_p[2], int fd_n[2], int fd[2]);
void	pipe_and_open(int fd_n[2], int fd[2], t_command *ins);
void	pipe_and_exit(t_command *ins, int fd[2], int fd_p[2], int pip);

/*
// BUILT_IN
*/
int			bi_echo(char **av);
void		bi_pwd(void);
void		bi_env(char **env);
char		**bi_cd(char *str, char **env);
int			len_name(char *str);
char		**ad_arg_exp(char **env, char *str);
char		**bi_export(char **env, char **av);
char		**bi_unset(char **env, char **av);
void		free_env(char **env);
void		bi_exit(t_command *ins, char **env, char **av);
int			exit_error(char *exe, char *msg, int exit_value, int arg);

/*
// TABDUP_C
*/

int			tablen(char **tab);
char		**tabdup(char **tab);

/*
// READLINE LIBRARY
*/

int			rl_replace_line(const char *text, int clear_undo);
void		rl_clear_history(void);

#endif