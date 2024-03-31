/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:20:12 by gabsanch          #+#    #+#             */
/*   Updated: 2024/03/16 17:38:56 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*T_PIECE / T_LEXER FLAGS*/
# define P_MLC 1  //Malloc successful
# define P_SQT 2  //In single quote
# define P_DQT 4  //In double quote
# define P_EXP 8  //Had expansion
# define P_SLT 16 //To be split
# define P_UNL 32 //To be unlinked
# define RED_IN_S 128
# define RED_IN_D 256
# define RED_OUT_S 512
# define RED_OUT_D 1024
# define RED_EXPAND 2048
# define RED_ANY 3968
# define NO_WS 4096

# define DQUO 34
# define QUO 39

/*T_EGG FLAGS*/
# define G_FIRST 1
# define G_LAST 2

/*ERR FLAGS*/
# define PERR_PID 10
# define PERR_EEX 17
# define PERR_PPE 32
# define PERR_CMD_ACC 126
# define PERR_CMD 127
# define PERR_PAR 258
# define ERR_EXIT 1
# define ERR_PROR 2

# include "./libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include "./readline/readline.h"
# include "./readline/history.h"

int	g_received; //marks that a signal was received

typedef struct s_common
{
	char	**env;
	int		exstatus;
}	t_common;

typedef struct s_lexer
{
	int				token;
	char			*word;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_piece
{
	int				flags;
	char			*chunk;
	struct s_piece	*next;
}	t_piece;

typedef struct s_egg
{
	t_piece	*redirs;
	int		*oflags;
	int		*optflags;
	char	**cmdargv;
	char	pos;
}	t_egg;

/*MAIN*/
void	ft_sighandler(int signal);
int		unclosed(char *str);

/*LEXER*/
int		tokenize(char *str, t_lexer **lexer);
void	ft_lxr_addback(t_lexer **lst, t_lexer *new);
int		istoken(char c);
t_lexer	*ft_lxr_last(t_lexer *lst);
int		skip_until_next(char *str);
int		checktokenerrs(t_lexer *lexed, t_common *common);

/*PARSER*/
int		piecelen(t_piece *list);
t_piece	*last_piece(t_piece *piece);
void	pieceaddback(t_piece *toadd, t_piece **list);
int		countargs(t_piece *lexed);
int		countredirs(t_piece	*lexed);
int		count_pipes(t_piece *list);
t_egg	*parse(t_piece *lexed, t_common *common);
t_piece	*newpiece(int status, char *chunk, t_piece *next);
char	*findname(void);
char	*get_term(char *given);
char	*create_hd(char *terminator, t_common *common);
char	**ultrasplit(char const *str, char *separators);
char	*ft_getenv(char **env, char *var);

/*EXPANSOR*/
int		explen(char *var);
t_piece	*getexpansion(char **env, char	*var, int status);
t_piece	*cleanpieces(t_piece **list);
t_piece	*expandstr(char *str, char **env, int exstatus, int status);
t_piece	*expandcmd(char **cmd, const int argc, char **env, int exstatus);
char	**expanded_to_array(t_piece *expanded);

/*EXEGGUTOR*/
int		egglen(t_egg *array);
int		exeggutor(t_egg *info, t_common *common);
void	waitall(pid_t *pids, int *status);
int		retstatus(int status);
int		redirects(int fds[2], t_egg *info, t_common *common);
void	savestd(int	*std);
void	redstd(int *std);
void	breed_process(int fds[2], t_egg *info, t_common *common);
void	_set_and_check(char **path, char *toset);
char	*get_function(char *fname, char **envp);
void	pterr(char **text, char exits, int excode);
int		isstrin(char *str, const char **phrase);

/*BUILTINS UTILS*/
char	**app_exp(char *str, char **env, int k);
char	**new_exp(char *str, char **env, int type);
char	*ft_addargv(char *str, int type);
void	var_append(char *str, char **env, int i);
void	var_replace(char *str, char **env, int i);
int		ft_varexists(char *str, char **env, int k);
void	print_vars(char **env);
int		ft_print_not_valid(char *var, int *exstt);
int		ft_unset_not_valid(char *var, int *exstt);
int		ft_var_is_valid(char *first, int j);
int		ft_isexport(char c);
void	free_env(char **env);

/*BUILTINS*/
int		exebi(t_egg *info, t_common *common);
int		cd(t_egg *info, char ***envp);
int		echo(t_egg *info);
int		env(char **envp);
int		unset(t_egg *info, char **envp, int *exstt);
int		ft_exit(t_egg *info, int exstatus);
int		ft_export(t_egg *info, char ***envp, int *exstt);
int		pwd(void);

/*DESTRUCTORS*/
void	delete_piece(t_piece **piece);
void	scramble_pieces(t_piece **piece);
void	break_eggs(t_egg **eggs);

#endif
