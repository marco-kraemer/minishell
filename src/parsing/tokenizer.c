/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:57:01 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/29 22:53:34 by maraurel         ###   ########.fr       */
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

/* Contar número de palavras sem contar espaços */
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

/* Juntar argumentos quando não há espaço entre eles e remover os espaços*/
char	**join_no_space_args(char **args, int i, int j, int count_words)
{
	char	**ret;

	count_words = count_num_word(args);
	ret = (char **)malloc(sizeof(char *) * (count_words + 1));
	i = 0;
	j = 0;
	while (args[i])
	{
		ret[j] = ft_strdup(args[i]);
		i++;
		while (args[i])
		{
			if ((ft_strcmp(args[i], " ") == 0 && ft_strlen(args[i]) == 1) || ft_strlen(args[i]) == 0)
			{
				i++;
				break ;
			}
			ret[j] = ft_strjoin_free(ret[j], args[i]);
			i++;
		}
		j++;
	}
	ret[count_words] = 0;
	ft_free_double(args);
	return (ret);
}

char	**tokenizer(t_shell *shell, int status, char **envp)
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
	free(shell->quote_rules);
	return (join_no_space_args(shell->splited, 0, 0, 0));
}
