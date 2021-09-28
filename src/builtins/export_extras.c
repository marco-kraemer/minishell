/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extras.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:27:44 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/28 17:28:24 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_name(char *args)
{
	int	i;

	i = 0;
	while (args[i] != '=' && args[i])
	{
		if (ft_isalpha(args[i]) == 0 && args[i] != '_')
		{
			printf("export: '%s': not a valid identifier\n", args);
			return (NULL);
		}
		i++;
	}
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
	return (ft_substr(args, i + 1, length));
}
