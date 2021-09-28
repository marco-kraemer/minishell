/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:57:01 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/28 09:54:17 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include "../includes/minishell.h"

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

char	*replace_values(char *s, char *old, char *new)
{
	char	*result;
	int		i;
	int		cnt;
	int		newlen;
	int		oldlen;

	i = 0;
	cnt = 0;
	newlen = ft_strlen(new);
	oldlen = ft_strlen(old);
	
	/* Contar num vezes old word aparece*/
	while (s[i] != '\0')
	{
		if (ft_strstr(&s[i], old) == &s[i])
			cnt++;
		i += oldlen - 1;
		if (i > (int)ft_strlen(s))
			break ;
	}
	/* Allocar memória suficiente */
	result = (char*)malloc(i + cnt * (newlen - oldlen) + 1);

	i = 0;
	while (*s)
	{
		if (ft_strstr(s, old) == s)
		{
			if (new)
				ft_strcpy(&result[i], new);
			i += newlen;
			s += oldlen;
		}
		else
			result[i++] = *s++;
	}
	result[i] = '\0';
	return (result);
}

/* Replace string iniciadas com $ pelo valor
			da variável de ambiende correspondente */
void	replace(t_shell *shell, t_correct_args helper, char **envp)
{
	int	word_length;

	word_length = 0;
	while ((ft_isalpha(shell->splited[helper.i][helper.j + word_length]) != 0
		|| shell->splited[helper.i][helper.j + word_length] == '$'
		|| shell->splited[helper.i][helper.j + word_length] == '?')
		&& shell->splited[helper.i][helper.j + word_length])
		word_length++;
	helper.word = ft_substr(shell->splited[helper.i], helper.j, word_length);
	if (ft_strncmp(shell->splited[helper.i], "$?", word_length) == 0
		&& word_length == 2)
		helper.value = ft_itoa(shell->status);
	else
		helper.value = ft_getenv(helper.word, envp);
	helper.new = replace_values(shell->splited[helper.i],
			helper.word, helper.value);
	free(shell->splited[helper.i]);
	shell->splited[helper.i] = ft_strdup(helper.new);
	free(helper.value);
	free(helper.new);
	free(helper.word);
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
			if (ft_strcmp(args[i], " ") == 0 && ft_strlen(args[i]) == 1)
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

char	**correct_args(t_shell *shell, int status, char **envp)
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
				replace(shell, helper, envp);
			helper.j++;
			if (helper.j > (int)ft_strlen(shell->splited[helper.i]))
				break ;
		}
		helper.i++;
	}
	return (join_no_space_args(shell->splited, 0, 0, 0));
}
