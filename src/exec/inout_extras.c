/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 22:12:59 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/01 14:55:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_syntax(char **args, t_shell *shell, int i, int k)
{
	int	j;
	int	count;

	while (args[++i])
	{
		j = -1;
		count = 0;
		if (ft_strcmp(shell->splited[i], " ") != 0 && ft_strlen(args[i]) != 0)
		{
			while (args[k][++j])
			{
				if ((args[k][j] == '>' || args[k][j] == '<')
					&& shell->quote_rules_char[k][j] == 1)
					count++;
			}
			if (count == (int)ft_strlen(args[k])
				&& redirections_rules2(args[k], i, shell) == 1)
			{
				ft_free_double(shell->splited);
				return (1);
			}
			k++;
		}
	}
	return (0);
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

int	redirections_rules2(char *arg, int i, t_shell *shell)
{
	if (!arg)
		return (0);
	if ((ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, "<") == 0)
		&& shell->quote_rules_char[i][0] == 1)
		return (0);
	if ((ft_strcmp(arg, ">>") == 0 || ft_strcmp(arg, "<<") == 0)
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
