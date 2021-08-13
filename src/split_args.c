/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:43:48 by maraurel          #+#    #+#             */
/*   Updated: 2021/08/13 16:04:44 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	special_chars(char **p, t_shell *shell)
{
	int	j;
	int	k;

	j = 0;
	while (p[j])
	{
		k = 0;
		if (shell->quote_rules[j] == 0)
		{
			while (p[j][k])
			{
				if (p[j][k] == '\\' || p[j][k] == ';')
					return (1);
				k++;
			}
		}
		j++;
	}
	return (0);
}

int	quotes_case(int quotes, t_shell *shell, char **p, char const *s)
{
	char	c;

	c = '\0';
	if (quotes == 1)
		c = '\"';
	else if (quotes == 2)
		c = '\'';
	if (quotes == 1 || quotes == 2)
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
		shell->quote_rules[shell->j] = 0;
		while (s[shell->i] != '\0' && s[shell->i] != ' ')
			p[shell->j][shell->k++] = s[shell->i++];
	}
	return (0);
}

void	check_quotes(t_shell *shell, char const *s)
{
	while (s[shell->i] == ' ' || s[shell->i] == '\"' || s[shell->i] == '\'')
	{
		if (s[shell->i] == '\"')
			shell->quotes = 1;
		if (s[shell->i] == '\'')
			shell->quotes = 2;
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
		if (p[shell->j] == NULL)
			return (to_free2((char const **)p, shell->j));
		if (quotes_case(shell->quotes, shell, p, s) == 1)
		{
			ft_free_double(p);
			return (NULL);
		}
		p[shell->j][shell->k] = '\0';
		shell->quotes = 0;
		shell->j++;
	}
	p[shell->j] = 0;
	if (special_chars(p, shell) == 1)
		return (NULL);
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
	i = countstring2(s, c);
	p = (char **)malloc(sizeof(char *) * (i + 1));
	if (p == NULL)
		return (NULL);
	return (makearray2(shell, s, p, i));
}
