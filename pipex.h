/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:20:46 by ralves-g          #+#    #+#             */
/*   Updated: 2022/07/25 13:53:21 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <string.h>
# include <errno.h>
# include "get_next_line.h"
# include "stdio.h"
# include <sys/wait.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		here_doc;
	int		pipe[2];
	int		lastcmd;
	int		cmdnbr;
	char	**arg;
	int		id;
	pid_t	pid;
	char	**cmd;
	char	**path;
	char	*cmdpath;
}	t_pipex;

//pipex.c
void	err_args(void);
void	child_process(t_pipex *p, int i, char **env);

//parsing.c
void	heredoc_filler(int tempfile, char	**av);
void	has_heredoc(t_pipex *p, char **av, int ac);
void	no_heredoc(t_pipex *p, char **av, int ac);
void	parse_args(t_pipex *p, char **av, int ac);
void	parse_path(t_pipex *p, char **env);

//child_work.c
void	not_absolute(t_pipex *p);
void	absolute(t_pipex *p);
void	child_work(t_pipex *p, int i);

//split.c
char	**ft_split(char const *str, char c);
char	*ft_substr(char const *str, int start, int end);

//errors&frees.c
void	free_not_all(t_pipex *p);
void	free_all(t_pipex *p);
void	ft_err(t_pipex *p, char *str);
void	special_err(t_pipex *p, char *str);
void	err_all(t_pipex *p, char *str);

//utils.c
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);

#endif