/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:22:27 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/28 14:18:54 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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

# define NO_QUOTES	0
# define SINGLE_QUOTES	2
# define DOUBLE_QUOTES	1
# define TRUE	1
# define FALSE	0
# define BUFF_SIZE	1024
# define RED "\001\e[1;31m\002"
# define CYAN "\001\e[1;36m\002"
# define WHITE "\001\e[1;37m\002"
# define RESET "\001\e[0m\002"

typedef struct s_correct_args
{
	char	*new;
	char	*value;
	char	*word;

	char	*string;

	int		status;

	int		i;
	int		j;
	int		k;

	int		rule;
}		t_correct_args;

typedef struct s_shell {
	char	**args;
	char	*outfile;
	char	*infile;

	char	**env;
	char	**splited;

	int		rule;
	int		numcommands;
	int		tmpin;
	int		tmpout;
	int		fdout;
	int		fdin;

	int		status;

	int		*quote_rules;

	int		i;
	int		j;
	int		k;
	int		quotes;
}		t_shell;

typedef struct s_rule {
	int		i;
	int		ret;
	int		check1;
	int		check2;
}		t_rule;

extern int	g_status;

int		countchar2(t_shell shell, char const *s2, int i);
int		countstring2(char const *s, char c, int i, int state);
int		check_redirection(char **args, char *value);
int		check_rule(char *line);
int		treat_quotes(char *line, int i);
int		ft_strcmp(const char *str1, const char *str2);

char	*read_line(void);

char	**treat_tabs(char **args);
char	**get_variable_list(char **env);
char	**split_args(char const *s, t_shell *shell);
char	**to_free2(char const **p, int j);
char	**correct_args(t_shell *shell, int status, char **envp);
char	**split_commands(char const *s);
char	**even_number_of_quotes(t_shell *shell, char **p, int num_commands);
char	**to_free2(char const **p, int j);

char	*unset(char **args, t_shell *shell, int index);
char	*export(char **args, t_shell *shell, int index);
char	*env(char **args, t_shell *shell);
char	*pwd(void);
char	*change_directory(char **args);
char	*readinput(t_shell *shell);
char	*ft_remove(void);
char	*ft_strjoin_free(char const *s1, char const *s2);
char	*replace_words(char *s, char *old, char *new);

void	ft_free_double(char **s);
void	execute(t_shell *shell, char **env);
void	execute_child(t_shell *shell, char **envp, char *line);
void	launch(t_shell *shell, char **envp, char **file, char *msg);
int		iterate_over_path(t_shell *shell, char **envp, char **file, char *msg);
int		contains_slash(char *str, int *ret);
void	free_and_exit(char **args, char *line, t_shell *shell);
void	sigint_handler(int sig_num);
void	sigint_handler_process(int sig_num);
void	free_args(char *line, t_shell *shell);
void	get_in_and_out_file(t_shell *shell, char *line);
void	sigquit_handler_process(int sig_num);
#endif
