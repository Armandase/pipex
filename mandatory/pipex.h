/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:24:21 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/03 19:07:33 by adamiens         ###   ########.fr       */
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
	char	*path;
	char	**command;
}	t_args;

typedef struct s_file
{
	int		fd_in;
	int		fd_out;
}	t_file;
void	ft_open_file(int argc, char **argv, t_file *fd, t_args *args);
t_args	*ft_parsing(int argc, char **argv, char **envp);
int		ft_cpy_path(char **directory, char *argv, t_args *args, int i);
char	**ft_get_path(char **envp);
void	ft_exit_error(char **strs);
void	free_struct(t_args *args);
void	ft_exit_error(char **strs);
void	ft_free_strs(char **strs);
void	ft_free_struct(t_args *args);
void	ft_index_free_struct(t_args *args, int max);
void	ft_first_read(int pipe_tab[2], t_args *args, t_file *fd);
void	ft_end_read(int pipe_tab[2], t_args *args, t_file *fd);

#endif
