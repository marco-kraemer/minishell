/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_countstring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:26:00 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/28 17:26:59 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	countstring2_state_0_case(int *state, int *count_space, int *i)
{
	*state = 1;
	*count_space = 0;
	*i += 1;
}

void	countstring2_space_case(int *state, int *count_space, int *i)
{
	if (*count_space == 0)
		*i += 1;
	*count_space = 1;
	*state = 0;
}

int	countstring2(char const *s, char c, int i, int state)
{
	int	count_space;

	count_space = 0;
	while (*s != '\0')
	{
		if (*s == '\"' || *s == '\'')
		{
			c = *s;
			s++;
			while (*s != c && *s != '\0')
				s++;
			i++;
			count_space = 0;
			state = 0;
		}
		else if (*s == ' ')
			countstring2_space_case(&state, &count_space, &i);
		else if (state == 0)
			countstring2_state_0_case(&state, &count_space, &i);
		if (*s != '\0')
			s++;
	}
	return (i);
}
