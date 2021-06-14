/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <maraurel@student.42sp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:22:27 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/14 10:11:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL
# include "../libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <termcap.h>
#include <sys/wait.h>

# define	TRUE	1
# define	FALSE	0
# define	BUFF_SIZE	1024

char	*read_line(void);

char	**get_variable_list(char **env);
char	**delete_line(char **env, int line);
char	**add_line(char **env, char *name, char *value);

int		unset(char **args, char **env);
int		export(char **args, char **env);
int		launch_program(char **args);
int		execute(char **args, char **envp, char *line);
int		env(char **args, char **env);
int		pwd();
int		echo(char **args);
int		change_directory(char **args);
int		free_and_exit(char **args, char *line);

#endif
