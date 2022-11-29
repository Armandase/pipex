/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:04:19 by adamiens          #+#    #+#             */
/*   Updated: 2022/11/15 11:14:35 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	char	*str;

	size = 0;
	while (s[size])
		size++;
	str = malloc(sizeof(char) * (size + sizeof(int)));
	if (!str)
		return (NULL);
	size = 0;
	while (s[size] != '\0')
	{
		str[size] = s[size];
		size++;
	}
	str[size] = '\0';
	return (str);
}
