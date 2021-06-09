/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/09 14:38:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_prompt()
{
	char	cwd[FILENAME_MAX];
	int		i;

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
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
	char	*line;
	char	**args;
	char	**env;
	int		status;
	int		i;

	env = get_variable_list(envp);
	if (argc == 54225 && argv)
		printf("oi\n");
	while (TRUE)
	{
		signal(SIGINT, sigintHandler);
		print_prompt();
		line = read_line();
		args = ft_split(line, ' ');
		status = execute(args, env, line);
		i = 0;
		while (args[i])
			free(args[i++]);
		free(line);
		free(args);
	}
	exit (EXIT_SUCCESS);
}
