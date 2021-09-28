/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:57:01 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/28 14:18:46 by maraurel         ###   ########.fr       */
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

/* Conta quantas vezes palavra 'word' aparece na 'string' */
int	count_times_word_occur_in_string(char *string, char *word)
{
	int	wordlen;
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	wordlen = ft_strlen(word);
	while (string[i] != '\0')
	{
		if (strstr(&string[i], word) == &string[i])
		{
			cnt++;
			i += wordlen - 1;
		}
		i++;
		if (i > (int)ft_strlen(string))
			break ;
	}
	return (cnt);
}

/* Troca as palavras old por new na string s */
char	*replace_words(char *s, char *old, char *new)
{
	int		i;
	int		newlen;
	int		oldlen;
	char	*result;

	i = 0;
	newlen = ft_strlen(new);
	oldlen = ft_strlen(old);
	result = (char *)malloc(sizeof(char) * ft_strlen(s)
			+ count_times_word_occur_in_string(s, old)
			* (ft_strlen(new) - ft_strlen(old)) + 1);
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

/* Realiza checkagem para while loop função replace */
int	check_replace(t_shell *shell, int word_length, t_correct_args helper)
{
	if (((ft_isalpha(shell->splited[helper.i][helper.j + word_length]) != 0
			|| shell->splited[helper.i][helper.j + word_length] == '$'
		|| shell->splited[helper.i][helper.j + word_length] == '?'
		|| shell->splited[helper.i][helper.j + word_length] == '_')
		&& shell->splited[helper.i][helper.j + word_length]))
		return (0);
	return (1);
}

/* Free parametros da função duplicate */
void	free_and_duplicate_replace(t_shell *shell, t_correct_args *helper)
{
	free(shell->splited[helper->i]);
	shell->splited[helper->i] = ft_strdup(helper->new);
	free(helper->value);
	free(helper->new);
	free(helper->word);
}

/* Replace string iniciadas com $ pelo valor
			da variável de ambiende correspondente */
void	replace(t_shell *shell, t_correct_args helper, char **envp)
{
	int	word_length;
	int	status;

	status = 0;
	word_length = 0;
	while (check_replace(shell, word_length, helper) == 0)
	{
		if (shell->splited[helper.i][helper.j + word_length] == '$')
			status++;
		if (status > 1)
			break ;
		word_length++;
	}
	helper.word = ft_substr(shell->splited[helper.i], helper.j, word_length);
	if (ft_strncmp(shell->splited[helper.i], "$?", word_length) == 0
		&& word_length == 2)
		helper.value = ft_itoa(shell->status);
	else
		helper.value = ft_getenv(helper.word, envp);
	helper.new = replace_words(shell->splited[helper.i],
			helper.word, helper.value);
	free_and_duplicate_replace(shell, &helper);
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
	return (join_no_space_args(shell->splited, 0, 0, 0));
}
