/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:43:48 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/30 10:45:59 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quotes_case(int quotes, t_shell *shell, char **p, char const *s)
{
	char	c;

	if (quotes == DOUBLE_QUOTES)
		c = '\"';
	else if (quotes == SINGLE_QUOTES)
		c = '\'';
	if (quotes == SINGLE_QUOTES || quotes == DOUBLE_QUOTES)
	{
		shell->quote_rules[shell->j] = quotes;
		while (s[shell->i] != '\0' && s[shell->i] != c)
			p[shell->j][shell->k++] = s[shell->i++];
		if (s[shell->i] != '\0')
			shell->i++;
		if (s[shell->i] == '\0' && s[shell->i - 1] != c)
			return (1);
	}
	else
	{
		shell->quote_rules[shell->j] = NO_QUOTES;
		while (s[shell->i] != '\0' && s[shell->i] != ' '
			&& s[shell->i] != '\'' && s[shell->i] != '\"')
			p[shell->j][shell->k++] = s[shell->i++];
	}
	return (0);
}

void	check_quotes(t_shell *shell, char const *s)
{
	while (s[shell->i] == ' ' || s[shell->i] == '\"' || s[shell->i] == '\'')
	{
		if (s[shell->i] == '\"')
		{
			shell->quotes = DOUBLE_QUOTES;
			shell->i++;
			break ;
		}
		if (s[shell->i] == '\'')
		{
			shell->quotes = SINGLE_QUOTES;
			shell->i++;
			break ;
		}
		shell->i++;
	}
}

char	**makearray2(t_shell *shell, char const *s, char **p, int l)
{
	shell->i = 0;
	shell->j = 0;
	shell->quotes = 0;
	while (s[shell->i] != '\0' && shell->j < l)
	{
		shell->k = 0;
		check_quotes(shell, s);
		p[shell->j] = (char *)malloc(sizeof(char)
				* countchar2(*shell, s, shell->i) + 1);
		if (quotes_case(shell->quotes, shell, p, s) == 1 || p[shell->j] == NULL)
			return (to_free2((char const **)p, shell->j));
		p[shell->j][shell->k] = '\0';
		shell->quotes = 0;
		if (s[shell->i] == ' ')
		{
			shell->j++;
			p[shell->j] = (char *)malloc(sizeof(char) * 2);
			shell->quote_rules[shell->j] = 0;
			p[shell->j][0] = ' ';
			p[shell->j][1] = '\0';
		}
		shell->j++;
	}
	return (p);
}

char	**split_args(char const *s, t_shell *shell)
{
	char	**p;
	int		i;
	char	c;

	c = ' ';
	if (s == NULL)
		return (NULL);
	i = countstring2(s, c, 0, 0);
	shell->quote_rules = malloc(sizeof(int) * i);
	p = (char **)malloc(sizeof(char *) * (i + 1));
	if (p == NULL)
		return (NULL);
	p = makearray2(shell, s, p, i);
	if (ft_strlen(p[shell->j - 1]) == 0)
	{
		free (p[shell->j - 1]);
		p[shell->j - 1] = 0;
	}
	if (!(p[0]))
	{
		free(p);
		return (NULL);
	}
	p[shell->j] = 0;
	return (p);
}
