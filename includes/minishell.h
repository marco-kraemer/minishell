/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:22:27 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/01 14:12:01 by maraurel         ###   ########.fr       */
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
# define	PROMPT_MSG	"\033[0;36m minishell$ \033[0;37m"

int		check_redirection(char **args, char *value);

char	*read_line(void);

char	**get_variable_list(char **env);
char	**delete_line(char **env, int line);
char	**ft_splitn(char const *s, char c);

char		*unset(char **args, char **env);
char		*export(char **args, char **env);
char		*execute(char **args, char **envp, char *line);
char		*env(char **args, char **env);
char		*pwd();
char		*echo(char **args);
char		*change_directory(char **args);
char		*readinput();

void		launch(char** parsed, char **envp, char *file, char *msg);
void		free_and_exit(char **args, char *line);
void		sigintHandler(int sig_num);
void		sigintHandler_process(int sig_num);
#endif
