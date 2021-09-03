#include "minishell.h"

int 	check_in_env_u(char *str, char **env);

char	*check_pwd(char *str, char **env, int opwd, int home)
{
	char *s;

	s = NULL;
	if (ft_strncmp(str, "-", 2) == 0)
	{
		if (opwd != -1)
		{
			s = ft_strdup(env[opwd] + 7);
			printf("%s\n", env[opwd] + 7);
		}
		else
			printf("minishell: cd: OLDPWD not set\n");	
	} 
	else if (ft_memcmp("~", str, 2) == 0)
		if (home != -1)
			s = ft_strdup(env[home] + 5);
		else
			printf("minishell: cd: HOME not set\n");
	else if (ft_memcmp("~/", str, 2) == 0)
		if (home != -1)
			s = ft_strjoin(env[home] + 5, str + 2);
		else
			printf("minishell: cd: HOME not set\n");
	else
		s = ft_strdup(str);
	return (s);
}

char	**bi_cd(char *str, char **env)
{
	char	*pwd;
	char	*tmp;
	char	*s;
	int		i[2];


	i[0] = find_env(env, "ENV");
	i[1] = find_env(env, "OLDPWD");
	s = check_pwd(str, env, i[1], find_env(env, "HOME"));
	if (!s)
		return (env);
	if (chdir(s) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", s);
	}
	else
	{
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
	}
	free(s);
	return (env);
}