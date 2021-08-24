#include "minishell.h"

int 	check_in_env_u(char *str, char **env);

char	**bi_cd(char *str, char **env)
{
	char *pwd;
	char *tmp;
	int	i[2];

	chdir(str);
	i[0] = check_in_env_u("PWD", env);
	i[1] = check_in_env_u("OLDPWD", env);
	if (i[0] != -1 && i[1] != -1)
	{
		pwd = ft_strjoin("OLD", env[i[0]]);
		free(env[i[1]]);
		env[i[1]] = pwd;
	}
	if (i[0] != -1)
	{
		tmp = getcwd(NULL, 0);
		pwd = ft_strjoin("PWD=", tmp);
		free(tmp);
		env[i[0]] = pwd;
	}
	return (env);
}