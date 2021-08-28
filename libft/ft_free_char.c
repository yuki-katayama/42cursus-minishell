/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuki <kyuki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 03:12:33 by kyuki             #+#    #+#             */
/*   Updated: 2021/05/30 14:43:03 by kyuki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_char(char **word, int index)
{
	int	i;

	i = -1;
	while (++i < index)
	{
		free(*word);
		word++;
	}
	free(word);
	return (NULL);
}
