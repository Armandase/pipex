/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:24:21 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/14 16:37:56 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_args
{
	char	**command;
}	t_args;

typedef struct s_file
{
	int		fd_in;
	int		fd_out;
	int		pipe_tab[2][2];
}	t_file;
void	ft_open_file(int argc, char **argv, t_file *fd, int heredoc);
t_args	*ft_parsing(int argc, char **argv, char **envp);
void	ft_cpy_path(char **command, char **directory);
char	**ft_get_path(char **envp);
void	ft_exit_error(char **strs);
void	free_struct(t_args *args);
void	ft_exit_error(char **strs);
void	ft_free_strs(char **strs);
void	ft_free_struct(t_args *args);
void	ft_index_free_struct(t_args *args, int max);
void	ft_init_exec(t_args *args, t_file *fd);
int		ft_count_pid(t_args *args);
void	ft_wait_end_child(t_args *args, int pid, t_file *fd);
void	ft_first_read(t_args *args, t_file *fd, int *tab_pid);
void	ft_end_read(t_args *args, t_file *fd, int *tab_pid, int i);
void	ft_error(t_args *args, t_file *fd);
void	ft_close_pipe(int pipe_tab[2][2]);
t_args	*ft_heredoc_pars(int argc, char **argv, char **envp);
t_file	*ft_heredoc(char **argv, int argc);
void	ft_execve_error(t_file *fd, t_args *args, int *tab_pid);
#endif
