/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/18 11:59:49 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_prompt()
{
	char	cwd[FILENAME_MAX];
	int		i;

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		strerror(3);
	write(1, "\033[0;36m", ft_strlen("\033[0;36m")); // CYAN
	ft_putstr_fd("42@Minishell$ ", 1);
	write(1, "\033[0m", ft_strlen("\033[0m"));
	write(1, "$ ", 2);
}

void	sigintHandler(int sig_num)
{
	if (!sig_num)
		return;
	printf("\n");
	print_prompt();	
}

int	main(int argc, char **argv, char **envp)
{
	char	**line;
	char	**commands;
	char	**args;
	char	**env;
	char	*value;
	int		i;
	int		j;

	env = get_variable_list(envp);
	if (argc == 54225 && argv)
		printf("oi\n");
	while (TRUE)
	{
		signal(SIGINT, sigintHandler);
		print_prompt();
		line = ft_split(read_line(), ';');
		i = 0;
		while (line[i])
		{
			j = 0;
			commands = ft_split(line[i], '|');
			while (commands[j])
			{
				args = ft_split(line[i], ' ');
				value = execute(args, env, line[i]);
				j++;
			}
			if (value != NULL)
				printf("%s\n", value);
			i++;
		}
	}
	exit (EXIT_SUCCESS);
}
