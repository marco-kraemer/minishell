/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:04:49 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/28 14:53:53 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_join(char **str1, char *str2)
{
	char	*tmp;

	tmp = ft_strjoin(*str1, str2);
	free(*str1);
	*str1 = tmp;
}

void	create_prompt(char **prompt)
{
	char	*user;

	*prompt = ft_strdup(RED);
	user = getenv("USER");
	ft_join(prompt, user);
	ft_join(prompt, WHITE);
	ft_join(prompt, ":");
	ft_join(prompt, CYAN);
	ft_join(prompt, "minishell");
	ft_join(prompt, RESET);
	ft_join(prompt, "$ ");
}

char	*readinput(t_shell *shell)
{
	char	*line;
	char	*prompt;
	int		i;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sigint_handler);
	create_prompt(&prompt);
	line = readline(prompt);
	free(prompt);
	if (!line)
	{
		i = 0;
		while (shell->env[i])
		{
			if (ft_strlen(shell->env[i]) == 0)
				break ;
			free(shell->env[i++]);
		}
		free(shell->env);
		printf("exit\n");
		exit (0);
	}
	if (ft_strlen(line) != 0)
		add_history(line);
	return (line);
}
