/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:23:20 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/29 12:03:50 by maraurel         ###   ########.fr       */
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

char	*get_in_out_file(char **args, char *type1, char *type2)
{
	char	*filename;
	int		i;
	int		start;

	i = 0;
	filename = NULL;
	while (args[i])
	{
		if (ft_strcmp(args[i], type1) == 0 || ft_strcmp(args[i], type2) == 0)
		{
			i++;
			if (filename != NULL)
				free(filename);
			if (!(args[i]))
			{
				printf("minishell: syntax error\n");
				return (NULL);
			}
			filename = ft_strdup(args[i]);
		}
		i++;
	}
	return (filename);
}

void	get_in_and_out_file(t_shell *shell, char **args)
{
	shell->outfile = get_in_out_file(args, ">", ">>");
	shell->infile = get_in_out_file(args, "<", "<<");

	printf("%s e %s\n", shell->outfile, shell->infile);
}
