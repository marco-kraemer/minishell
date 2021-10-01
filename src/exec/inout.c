/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:23:20 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/30 21:45:11 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	treat_quotes(char *line, int i)
{
	if (line[i] == '\"')
	{
		i++;
		while (line[i] != '\"' && line[i])
			i++;
		if (line[i] != '\0')
			i++;
		return (i + 0);
	}
	if (line[i] == '\'')
	{
		i++;
		while (line[i] != '\'' && line[i])
			i++;
		if (line[i] != '\0')
			i++;
		return (i);
	}
	i++;
	return (i);
}

int	redirections_rules2(char *arg, int i, t_shell *shell)
{
	if (!arg)
		return (0);
	if ((ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, "<") == 0)
		&& shell->quote_rules_char[i][0] == 1)
		return (0);
	if ((ft_strcmp(arg, ">>") == 0 || ft_strcmp(arg, "<") == 0)
		&& shell->quote_rules_char[i][0] == 1
			&& shell->quote_rules_char[i][1] == 1)
		return (0);
	return (1);
}

char	*get_in_out_file_syntax_error(t_shell *shell)
{
	ft_free_double(shell->splited);
	printf("minishell: syntax error\n");
	shell->error = 1;
	return (NULL);
}

char	*get_in_out_file(char **args, char *type1, char *type2, t_shell *shell)
{
	char	*filename;
	int		i;

	i = 0;
	filename = NULL;
	while (args[i])
	{
		if ((ft_strcmp(args[i], type2) == 0
				&& shell->quote_rules_char[i][0] == 1
			&& shell->quote_rules_char[i][1] == 1)
			|| (ft_strcmp(args[i], type1) == 0
			&& shell->quote_rules_char[i][0] == 1))
		{
			i++;
			if (filename != NULL)
				free(filename);
			if (!(args[i]) || redirections_rules2(args[i], i, shell) == 0)
				return (get_in_out_file_syntax_error(shell));
			filename = ft_strdup(args[i]);
			if (shell->rule == 0)
				open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
		}
		i++;
	}
	return (filename);
}

int	redirections_rules(char *arg, t_shell *shell, int i)
{
	if (ft_strcmp(arg, ">") == 0 && shell->quote_rules_char[i][0] == 1)
		shell->outfile_rule = 1;
	else if (ft_strcmp(arg, ">>") == 0 && shell->quote_rules_char[i][0] == 1
		&& shell->quote_rules_char[i][1] == 1)
		shell->outfile_rule = 2;
	else if (ft_strcmp(arg, "<") == 0 && shell->quote_rules_char[i][0] == 1)
		shell->infile_rule = 1;
	else if (ft_strcmp(arg, "<<") == 0 && shell->quote_rules_char[i][0] == 1
		& shell->quote_rules_char[i][1] == 1)
		shell->infile_rule = 2;
	else
		return (1);
	return (0);
}

char	**remove_redirections(char **args, t_shell *shell)
{
	int		i;
	int		size;
	char	**ret;

	size = 0;
	while (args[size])
		size++;
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	size = 0;
	while (args[i])
	{
		if (redirections_rules(args[i], shell, i) == 0 && args[i + 1])
			i += 2;
		else
		{
			ret[size] = ft_strdup(args[i]);
			i++;
			size++;
		}
	}
	ret[size] = 0;
	ft_free_double(args);
	return (ret);
}

int	check_syntax(char **args, t_shell *shell)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (args[i])
	{
		j = 0;
		count = 0;
		while (args[i][j])
		{
			if ((args[i][j] == '>' || args[i][j] == '<')
				&& shell->quote_rules_char[i][j] == 1)
				count++;
			j++;
		}
		if (count == (int)ft_strlen(args[i])
			&& redirections_rules2(args[i], i, shell) == 1)
			return (1);
		i++;
	}
	return (0);
}

char	**get_in_and_out_file(t_shell *shell, char **args)
{
	shell->infile_rule = 0;
	shell->outfile_rule = 0;
	shell->files_rule = 0;
	shell->error = 0;
	if (check_syntax(args, shell) == 1)
	{
		printf("minishell: syntax error\n");
		return (NULL);
	}
	shell->rule = 0;
	shell->outfile = get_in_out_file(args, ">", ">>", shell);
	if (shell->error == 1)
		return (NULL);
	shell->files_rule = 1;
	shell->rule = 1;
	shell->infile = get_in_out_file(args, "<", "<<", shell);
	if (shell->error == 1)
		return (NULL);
	return (remove_redirections(args, shell));
}
