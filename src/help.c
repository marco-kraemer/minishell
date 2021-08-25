#include "../includes/minishell.h"

int	check_rule(char *line)
{
	t_rule	rule;

	rule.i = 0;
	rule.ret = 0;
	rule.check1 = 0;
	rule.check2 = 0;
	while (line[rule.i])
	{
		if (line[rule.i] == '>' && rule.check1 == 0)
		{
			rule.ret += 1;
			rule.check1++;
			if (line[rule.i + 1] == '>')
				rule.ret += 6;
		}
		if (line[rule.i] == '<' && rule.check2 == 0)
		{
			rule.ret += 4;
			rule.check2++;
			if (line[rule.i + 1] == '<')
				rule.ret += 8;
		}
		rule.i = treat_quotes(line, rule.i);
	}
	return (rule.ret);
}

char	*ft_exec_rm(char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return (NULL);
	}
	else if (pid == 0)
	{
		if (execve("/bin/rm", args, NULL) < 0)
			printf("rm: No such file or directory\n");
		exit(0);
	}
	else
	{
		wait(NULL);
		return (NULL);
	}
	return (NULL);
}

char	*ft_remove(void)
{
	char	**args;

	args = ft_split("rm ../tmp", ' ');
	ft_exec_rm(args);
	ft_free_double(args);
	return (NULL);
}
