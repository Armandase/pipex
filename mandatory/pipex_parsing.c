/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 13:09:58 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/03 18:46:10 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>

char	*ft_subcpy_str(char *str, char c)
{
	char	*cpy;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	cpy = malloc(sizeof(char) * (i + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

void	ft_get_command(t_args *args, char *argv, int i)
{
	args[i].command = ft_split(argv, ' ');
	free(args[i].command[0]);
	args[i].command[0] = ft_strdup(args[i].path);
}

void	ft_verif_args(char **argv, char **directory, t_args *args)
{
	int		i;
	char	*str;
	int		check;

	i = 2;
	while (argv[i + 1])
	{
		str = ft_subcpy_str(argv[i], ' ');
		check = ft_cpy_path(directory, str, args, i);
		if (!check)
		{
			ft_index_free_struct(args, i - 2);
			ft_exit_error(directory);
		}
		ft_get_command(args, argv[i], i - 2);
		i++;
	}
	args[i - 2].path = NULL;
}

int	check_len(char **argv, int argc)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < argc)
	{
		len = ft_strlen(argv[i]);
		if (len == 0)
			return (0);
		i++;
	}
	return (1);
}

/* **********************************************
 * parsing : 
 * 		claim every directories path from the envp
 * 		check if each argv can be apply a path collected
 * 		free every dir path
 * 		return command path and param to this command 
 * ******************************************* */

t_args	*ft_parsing(int argc, char **argv, char **envp)
{
	char	**directory;
	t_args	*args;

	if (argc != 5 || check_len(argv, argc) == 0)
		exit(1);
	args = ft_calloc(sizeof(t_args), (argc - 2));
	directory = ft_get_path(envp);
	ft_verif_args(argv, directory, args);
	ft_free_strs(directory);
	return (args);
}
