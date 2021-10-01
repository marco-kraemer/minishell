/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:57:01 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/30 21:44:00 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char *old, char **env)
{
	int		i;
	int		j;
	char	*value;
	char	*name;
	int		length;

	i = 0;
	value = NULL;
	name = ft_substr(old, 1, ft_strlen(old) - 1);
	while (env[i])
	{
		j = 0;
		length = 0;
		while (env[i][j] != '=' && env[i][j])
			j++;
		if (ft_strncmp(env[i], name, j) == 0 && (int)ft_strlen(name) == j)
		{
			value = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j);
			free(name);
			return (value);
		}
		i++;
	}
	free(name);
	return (value);
}

int	count_num_word(char **args)
{
	int	i;
	int	count_words;

	i = 0;
	count_words = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], " ") == 0
			&& ft_strlen(args[i]) == 1 && args[i + 1])
			count_words++;
		i++;
	}
	return (count_words);
}

int	count_num_word_spaces(char **args)
{
	int	i;
	int	count_words;

	i = 0;
	count_words = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], " ") != 0 && args[i])
			count_words++;
		i++;
	}
	return (count_words);
}

void	set_quotes_char_rules(t_shell *shell, int i)
{
	int	j;
	int	counter;

	shell->quote_rules_char = (int **)malloc(sizeof(int *)
			* (count_num_word_spaces(shell->splited) + 1));
	i = 0;
	j = 0;
	while (shell->splited[i])
	{
		counter = 0;
		if ((ft_strcmp(shell->splited[i], " ") != 0)
			&& ft_strlen(shell->splited[i]) != 0)
		{
			shell->quote_rules_char[j] = (int *)malloc(sizeof(int)
					* (ft_strlen(shell->splited[i]) + 1));
			while (counter < (int)ft_strlen(shell->splited[i]))
				shell->quote_rules_char[j][counter++]
					= shell->quote_rules[i] + 1;
			shell->quote_rules_char[j][counter++] = 0;
			j++;
		}
		i++;
	}
	shell->quote_rules_char[j] = (int *)malloc(sizeof(int) * 1);
	shell->quote_rules_char[j][0] = 0;
}

char	**join_no_space_args(t_shell *shell, int i, int j, int count_words)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * (count_words + 1));
	set_quotes_char_rules(shell, i - 1);
	while (shell->splited[i])
	{
		ret[j] = ft_strdup(shell->splited[i++]);
		while (shell->splited[i])
		{
			if ((ft_strcmp(shell->splited[i], " ") == 0
					&& ft_strlen(shell->splited[i]) == 1)
				|| ft_strlen(shell->splited[i]) == 0)
			{
				i++;
				break ;
			}
			ret[j] = ft_strjoin_free(ret[j], shell->splited[i]);
			i++;
		}
		j++;
	}
	ret[count_words] = 0;
	ft_free_double(shell->splited);
	return (ret);
}

char	**expander(t_shell *shell, int status, char **envp)
{
	t_correct_args	helper;

	shell->status = status;
	helper.i = 0;
	while (shell->splited[helper.i])
	{
		helper.j = 0;
		while (shell->splited[helper.i][helper.j])
		{
			if (shell->splited[helper.i][helper.j] == '$'
				&& shell->quote_rules[helper.i] != SINGLE_QUOTES
				&& shell->splited[helper.i][helper.j + 1] != ' '
				&& shell->splited[helper.i][helper.j + 1] != '\0')
			{
				replace(shell, helper, envp);
				helper.j--;
			}
			helper.j++;
			if (helper.j > (int)ft_strlen(shell->splited[helper.i]))
				break ;
		}
		helper.i++;
	}
	return (join_no_space_args(shell, 0, 0, count_num_word(shell->splited)));
}
