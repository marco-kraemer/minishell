/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_counters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 22:15:27 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/30 22:15:46 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	count_num_word_spaces(char **args)
{
	int	i;
	int	count_words;

	i = 0;
	count_words = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], " ") != 0 && args[i])
			count_words++;
		i++;
	}
	return (count_words);
}
