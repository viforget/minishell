#include "minishell.h"

int bi_pwd(env)
{
	printf("%s", find_in_env(env, "PWD")); //Fonction de Loic
}