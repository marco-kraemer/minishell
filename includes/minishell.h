/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:22:27 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/16 15:32:48 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <termcap.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <fcntl.h>
# define	TRUE	1
# define	FALSE	0
# define	BUFF_SIZE	1024


char	*read_line(void);

char	**get_variable_list(char **env);
char	**delete_line(char **env, int line);
char	**add_line(char **env, char *name, char *value);
char	**ft_splitn(char const *s, char c);

char		*unset(char **args, char **env);
char		*export(char **args, char **env);
char		*execute(char **args, char **envp, char *line);
char		*env(char **args, char **env);
char		*pwd();
char		*echo(char **args);
char		*change_directory(char **args);
char		*launch_program(char **args);

void		free_and_exit(char **args, char *line);
void		check_redirection(char **args, char *value);
#endif
