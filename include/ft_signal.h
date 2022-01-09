/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyokota <nyokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:35:57 by nyokota           #+#    #+#             */
/*   Updated: 2022/01/09 17:35:08 by nyokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include "ft_signal.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <unistd.h>
# include <readline/readline.h>

void	ft_signal(void);
void	ft_signal_process(void);

#endif
