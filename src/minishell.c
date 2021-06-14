/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <maraurel@student.42sp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/14 14:25:54 by user42           ###   ########.fr       */
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

static char	term_buffer[2048];

void	init_terminal_data(void)
{
	char	*termtype;
	int		success;

	termtype = getenv ("TERM");
	success = tgetent (term_buffer, termtype);
}

int	main(int argc, char **argv, char **envp)
{
	char	**line;
	char	**args;
	char	**env;
	int		i;

	env = get_variable_list(envp);
	init_terminal_data();
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
			args = ft_split(line[i], ' ');
			execute(args, env, line[i]);
			i++;
		}
		i = 0;
		while (args[i])
			free(args[i++]);
		free(line);
		free(args);
	}
	exit (EXIT_SUCCESS);
}
