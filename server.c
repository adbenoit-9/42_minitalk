/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 14:09:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/09 19:43:05 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	receive_str(int signum)
{
	static int	i_bit = 0;
	static char	byte = 0;

	if (signum == SIGUSR2)
		byte += 1 << i_bit;
	++i_bit;
	if (i_bit >= 8)
	{
		if (byte)
			ft_putchar_fd(byte, 1);
		byte = 0;
		i_bit = 0;
	}
}

int	main(void)
{
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, receive_str);
	signal(SIGUSR2, receive_str);
	while (1)
		pause();
	return (0);
}
