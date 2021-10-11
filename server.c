/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 14:09:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/11 11:28:03 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_buffer(char *buffer, int *i)
{
	if (*i == 4096)
	{
		buffer[*i] = 0;
		ft_putstr_fd(buffer, 1);
		i = 0;
	}
}

static void	receive_str(int signum)
{
	static int	i_bit = 0;
	static char	byte = 0;
	static char buffer[4098];
	static int	i = 0;

	if (signum == SIGUSR2)
		byte += 1 << i_bit;
	++i_bit;
	if (i_bit >= 8)
	{
		buffer[i++] = byte;
		if (!byte)
		{
			ft_putstr_fd(buffer, 1);
			i = 0;
		}
		else
			handle_buffer(buffer, &i);
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
