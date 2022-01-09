/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xclose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyokota <nyokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 20:31:19 by nyokota           #+#    #+#             */
/*   Updated: 2021/12/23 16:43:14 by nyokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	xclose(int fd)
{
	if (close(fd))
	{
		xperror("close");
		exit(EXIT_FAILURE);
	}
}