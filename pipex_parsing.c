/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 13:09:58 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/12 09:20:23 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

void	ft_verif_args(char **argv, char **directory, t_args *args)
{
	int		i;
	int		offset;

	offset = 2;
	i = 2;
	while (argv[i + 1])
	{
		if (ft_strlen(argv[i]) == 0)
		{
			write(2, "Error : Empty command\n", 22);
			i++;
			offset++;
		}
		args[i - offset].command = ft_split(argv[i], ' ');
		ft_cpy_path(args[i - offset].command, directory);
		i++;
	}
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

	args = ft_calloc(sizeof(t_args), (argc - 2));
	directory = ft_get_path(envp);
	ft_verif_args(argv, directory, args);
	ft_free_strs(directory);
	return (args);
}
