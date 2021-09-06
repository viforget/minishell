#include "minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin(s1, "/");
	str2 = ft_strjoin(str1, s2);
	free(str1);
	return (str2);
}

char	*check_pwd(char *str, char **env, int opwd, int home)
{
	char	*s;

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
	else if (ft_memcmp("~", str, 2) == 0 || ft_memcmp("~/", str, 2) == 0)
	{
		if (home != -1 && str[1] == 0)
			s = ft_strdup(env[home] + 5);
		else if (home != -1 && str[1] == '/')
			s = ft_strjoin2(env[home] + 5, str + 2);
		else
			printf("minishell: cd: HOME not set\n");
	}
	else
		s = ft_strdup(str);
	return (s);
}

char	**cd_env(char **env, int i[2])
{
	char	*pwd;
	char	*tmp;

	if (i[0] != -1)
	{
		pwd = ft_strjoin("OLD", env[i[0]]);
		env = ad_arg_exp(env, pwd);
		tmp = getcwd(NULL, 0);
		pwd = ft_strjoin("PWD=", tmp);
		free(tmp);
		env[i[0]] = pwd;
	}
	return (env);
}

char	**bi_cd(char *str, char **env)
{
	char	*s;
	int		i[2];

	i[0] = find_env(env, "ENV");
	i[1] = find_env(env, "OLDPWD");
	s = check_pwd(str, env, i[1], find_env(env, "HOME"));
	if (!s)
		return (env);
	if (chdir(s) == -1)
		printf("minishell: cd: %s: No such file or directory\n", s);
	else
		cd_env(env, i);
	free(s);
	return (env);
}
