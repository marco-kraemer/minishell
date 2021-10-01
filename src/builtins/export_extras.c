/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extras.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:27:44 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/30 22:12:27 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_name(char *args)
{
	int		i;
	char	*value;

	i = 0;
	while (args[i] != '=' && args[i])
	{
		if (ft_isalpha(args[i]) == 0 && args[i] != '_')
		{
			g_status = 1;
			printf("export: '%s': not a valid identifier\n", args);
			return (NULL);
		}
		i++;
	}
	value = get_value(args);
	if (!value)
		return (NULL);
	free(value);
	return (ft_substr(args, 0, i));
}

char	*get_value(char *args)
{
	int	i;
	int	length;

	i = 0;
	while (args[i] != '=' && args[i])
		i++;
	length = 0;
	while (args[i + length])
		length++;
	if (length < 2)
		return (NULL);
	return (ft_substr(args, i + 1, length));
}
