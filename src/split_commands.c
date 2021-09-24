/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 07:16:24 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/21 09:52:50 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes2(char const line, int rule)
{
	static int	check;

	if (line == '\"' && check != 2)
	{
		check = 1;
		if (rule > 0 && line == '\"')
		{
			check = 0;
			return (0);
		}
		rule++;
	}
	if (line == '\'' && check != 1)
	{
		check = 2;
		if (rule > 0 && line == '\'')
		{
			check = 0;
			return (0);
		}
		rule++;
	}
	if (rule > 0)
		return (rule);
	return (0);
}

int	count_string(char const *s)
{
	int	i;
	int	j;
	int	rule;

	i = 0;
	j = 0;
	rule = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s == '|' && (check_quotes2(*s, rule) == 0))
			j = 0;
		else if (j == 0)
		{
			j = 1;
			i++;
		}
		rule = check_quotes2(*s, rule);
		s++;
	}
	return (i);
}

int	count_char(char const *s2, int i)
{
	int	lenght;
	int	rule;

	lenght = 0;
	rule = 0;
	while (s2[i] != '\0')
	{
		if (s2[i] == '|' && check_quotes2(s2[i], rule) == 0)
			break ;
		lenght++;
		rule = check_quotes2(s2[i], rule);
		i++;
	}
	return (lenght);
}

char	**make_array(t_shell *shell, char const *s, char **p, int l)
{
	shell->i = 0;
	shell->j = 0;
	while (s[shell->i] != '\0' && shell->j < l)
	{
		shell->rule = 0;
		shell->k = 0;
		while (s[shell->i] == '|')
			shell->i++;
		p[shell->j] = (char *)malloc(sizeof(char)
				* count_char(s, shell->i) + 1);
		if (p[shell->j] == NULL)
			return (to_free2((char const **)p, shell->j));
		while (s[shell->i] != '\0')
		{
			if (s[shell->i] == '|' && check_quotes2(s[shell->i],
					shell->rule) == 0)
				break ;
			shell->rule = check_quotes2(s[shell->i], shell->rule);
			p[shell->j][shell->k++] = s[shell->i++];
		}
		p[shell->j][shell->k] = '\0';
		shell->j++;
	}
	p[shell->j] = 0;
	return (p);
}

char	**split_commands(char const *s)
{
	char	**p;
	int		i;
	t_shell	shell;

	if (s == NULL)
		return (NULL);
	i = count_string(s);
	p = (char **)malloc(sizeof(char *) * (i + 1));
	if (p == NULL)
		return (NULL);
	p = make_array(&shell, s, p, i);
	return (even_number_of_quotes(&shell, p, i));
}
