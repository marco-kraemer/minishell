/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:57:01 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/27 13:47:04 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	replace_values2(t_correct_args *helper, char *old, char ret[9999])
{
	int		k;
	char	tmp[999];

	k = 0;
	while (helper->string[helper->i + k] != ' '
		&& helper->string[helper->i + k])
	{
		tmp[k] = helper->string[helper->i + k];
		k++;
	}
	tmp[k] = '\0';
	if (ft_strncmp(tmp, old, ft_strlen(old)) == 0 && helper->rule == NO_QUOTES)
	{
		k = 0;
		if (helper->new)
			while (helper->new[k])
				ret[helper->j++] = helper->new[k++];
		helper->rule = DOUBLE_QUOTES;
		helper->i += ft_strlen(tmp);
	}
	ret[helper->j] = helper->string[helper->i];
	helper->i++;
}

char	*replace_values(char *string, char *old, char *new)
{
	t_correct_args	helper;
	char			ret[9999];

	helper.i = 0;
	helper.j = 0;
	helper.rule = 0;
	helper.new = new;
	helper.string = string;
	while (helper.string[helper.i])
	{
		replace_values2(&helper, old, ret);
		if (helper.i > (int)ft_strlen(helper.string))
			break ;
		helper.j++;
	}
	ret[helper.j] = '\0';
	return (ft_strdup(ret));
}

void	replace(t_shell *shell, t_correct_args helper, char **envp)
{
	int	word_length;

	word_length = 0;
	while (shell->splited[helper.i][helper.j + word_length] != ' '
		&& shell->splited[helper.i][helper.j + word_length])
		word_length++;
	helper.word = ft_substr(shell->splited[helper.i], helper.j, word_length);
	if (ft_strcmp(helper.word, "$?") == 0 && word_length == 2)
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

/* Juntar argumentos quando não há espaço entre eles e remover os espaços*/
char	**join_no_space_args(char **args, t_shell *shell)
{
	char	**ret;
	int		i;
	int		j;

	/* Calcular numeros de palavras, sem contar espaços */
	i = 0;
	j = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], " ") == 0 && ft_strlen(args[i]) == 1 && args[i + 1])
			j++;
		i++;
	}

	/* Juntar argumentos quando não há espaços*/
	ret = (char **)malloc(sizeof(char *) * (j + 1));
	i = 0;
	j = 0;
	while (args[i])
	{
		ret[j] = ft_strdup(args[i]);
		i++;
		while (args[i])
		{
			if (ft_strcmp(args[i], " ") == 0 && ft_strlen(args[i]) == 1)
				break ;
			ret[j] = ft_strjoin_free(ret[j], args[i]);
			i++;
		}
		j++;
	}
	ret[j] = 0;
	ft_free_double(shell->splited);
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
	shell->splited = join_no_space_args(shell->splited, shell);
	return (shell->splited);
}
