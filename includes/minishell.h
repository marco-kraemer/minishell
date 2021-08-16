/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:22:27 by maraurel          #+#    #+#             */
/*   Updated: 2021/08/16 09:48:21 by maraurel         ###   ########.fr       */
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

# define TRUE	1
# define FALSE	0
# define BUFF_SIZE	1024
# define RED "\001\e[1;31m\002"
# define CYAN "\001\e[1;36m\002"
# define WHITE "\001\e[1;37m\002"
# define RESET "\001\e[0m\002"

typedef	struct s_shell {
	char	**args;
	char	*outfile;
	char	*infile;

	char	**env;
	char	**splited;

	int		rule;
	int		numcommands;
	int	tmpin;
	int	tmpout;
	int	fdout;
	int	fdin;

	int	status;

	int	*quote_rules;

	int	i;
	int	j;
	int	k;
	int	quotes;
}		t_shell;

typedef	struct s_rule {
	int	i;
	int	ret;
	int	check1;
	int	check2;
}		t_rule;

extern int	g_status;

int		countchar2(t_shell shell, char const *s2, int i);
int		countstring2(char const *s, char c);
int		check_redirection(char **args, char *value);
int		check_rule(char *line);
int		treat_quotes(char *line, int i);
char	*read_line(void);

char	**get_variable_list(char **env);
char	**split_args(char const *s, t_shell *shell);
char	**to_free2(char const **p, int j);

char		*get_outfile(char *line);
char		*get_infile(char *line);
char		*unset(char **args, t_shell *shell);
char		*export(char **args, t_shell *shell);
char		*env(char **args, t_shell *shell);
char		*pwd();
char		*echo(t_shell shell, char **envp);
char		*change_directory(char **args);
char		*readinput(t_shell *shell);
char		*ft_remove(char **envp);

void		ft_free_double(char **s);
void		execute(t_shell *shell, char **env);
void		execute_child(t_shell *shell, char **envp, char *line);
void		launch(t_shell *shell, char **envp, char *file, char *msg);
void		free_and_exit(char **args, char *line, t_shell *shell);
void		sigintHandler(int sig_num);
void		sigquitHandler(int sig_num);
void		sigintHandler_process(int sig_num);
void		freeArgs(char *line, t_shell *shell);
#endif
