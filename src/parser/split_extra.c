/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:19:57 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/28 17:26:46 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	loop_quotes(char const *s)
{
	if (*s == '\"')
	{
		s++;
		while (*s != '\"' && *s != '\0')
			s++;
	}
	if (*s == '\'')
	{
		s++;
		while (*s != '\'' && *s != '\0')
			s++;
	}
}

int	countchar2(t_shell shell, char const *s2, int i)
{
	int		lenght;
	char	c;

	lenght = 0;
	if (shell.quotes == 0)
		c = ' ';
	else if (shell.quotes == 1)
		c = '\"';
	else
		c = '\'';
	while (s2[i] != c && s2[i] != '\0')
	{
		if (c == ' ' && (s2[i] == '\'' || s2[i] == '\"'))
			break ;
		lenght++;
		i++;
	}
	return (lenght);
}

int	count_quotes(int quotes, char **p, t_shell *shell, char c)
{
	quotes++;
	shell->j++;
	while (p[shell->i][shell->j] != c && p[shell->i][shell->j])
		shell->j++;
	if (p[shell->i][shell->j] != c)
		return (quotes);
	quotes++;
	shell->j++;
	return (quotes);
}

char	**even_number_of_quotes(t_shell *shell, char **p, int num_commands)
{
	int	double_quotes;
	int	single_quotes;

	shell->i = 0;
	while (p[shell->i])
	{
		shell->j = 0;
		double_quotes = 0;
		single_quotes = 0;
		while (p[shell->i][shell->j])
		{
			if (p[shell->i][shell->j] == '\"')
				double_quotes = count_quotes(double_quotes, p, shell, '\"');
			else if (p[shell->i][shell->j] == '\'')
				single_quotes = count_quotes(single_quotes, p, shell, '\'');
			else
				shell->j++;
		}
		if (double_quotes % 2 != 0 || single_quotes % 2 != 0)
			return (to_free2((char const **)p, num_commands));
		shell->i++;
	}
	return (p);
}
