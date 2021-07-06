/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:10 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/06 12:00:58 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*change_directory(char **args)
{
	if (args[1] == NULL)
		chdir("");
	else
	{
		if (chdir(args[1]) != 0)
			printf("shell: No such file or directory\n");
	}
	return (NULL);
}
