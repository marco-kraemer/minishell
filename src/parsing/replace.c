/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:31:26 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/28 17:32:27 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
