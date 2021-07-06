/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:22:27 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/06 11:11:31 by maraurel         ###   ########.fr       */
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
# include <fcntl.h>

# define	TRUE	1
# define	FALSE	0
# define	BUFF_SIZE	1024
# define	PROMPT_MSG	"\033[0;36m minishell$ \033[0;37m"

typedef	struct s_shell {
	char	**args;
	char	*outfile;
	char	*infile;

	char	**splited;

	int		rule;
	int		numcommands;
	int	tmpin;
	int	tmpout;
	int	fdout;
	int	fdin;

	int	status;

	int	*quote_rules;
}		t_shell;


int		check_redirection(char **args, char *value);

char	*read_line(void);

char	**get_variable_list(char **env);
char	**delete_line(char **env, int line);
char	**split_args(char const *s, t_shell *shell);

char		*unset(char **args, char **env);
char		*export(char **args, char **env);
char		*execute(t_shell *shell, char **envp, char *line);
char		*env(char **args, char **env);
char		*pwd();
char		*echo(t_shell *shell, int status,char **envp);
char		*change_directory(char **args);
char		*readinput();

void		launch(t_shell *shell, char **envp, char *file, char *msg);
void		free_and_exit(char **args, char *line);
void		sigintHandler(int sig_num);
void		sigquitHandler(int sig_num);
void		sigintHandler_process(int sig_num);
#endif
