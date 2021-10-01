/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 22:12:59 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/30 22:14:50 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
