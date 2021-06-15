/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <maraurel@student.42sp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/15 15:39:39 by user42           ###   ########.fr       */
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
	while (cwd[i])
		write (1, &cwd[i++], 1);
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
	char	*l;
	char	**line;
	char	**args;
	char	**env;
	int		i;
	env = get_variable_list(envp);
	if (argc == 54225 && argv)
		printf("oi\n");
	while (TRUE)
	{
		signal(SIGINT, sigintHandler);
		print_prompt();
		l = readline("");
		line = ft_split(l, ';');
		i = 0;
		while (line[i])
		{
			args = ft_split(line[i], ' ');
			execute(args, env, line[i]);
			i++;
		}
	}
	exit (EXIT_SUCCESS);
}
