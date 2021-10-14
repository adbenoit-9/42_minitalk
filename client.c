/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:40:44 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/14 16:00:14 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_trans	g_client;

static void	ft_error(char *str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

/* if it's the last bit of the string, returns -1.
Otherwise returns the bit to send */

static int	get_bit(char *str)
{
	bool		bit;
	static int	i_bit = 0;
	static int	i = 0;

	if (i_bit > 7)
	{
		if (!str[i])
			return (-1);
		i_bit = 0;
		++i;
	}
	bit = (str[i] >> i_bit) & 1;
	++i_bit;
	return (bit);
}

static void	send_bit(pid_t pid, bool bit)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
			ft_error("No such process");
	}
	else if (kill(pid, SIGUSR2) == -1)
		ft_error("No such process");
}

/* wait for the server confirmation to continue the transmission */

static void	send_next_bit(int signum)
{
	int	bit;
	
	if (signum == SIGUSR2)
		ft_error("Wrong signal.\nPlease relaunch the server");
	bit = get_bit(g_client.mess);
	usleep(100);
	if (bit == -1)
	{
		ft_putstr_fd("End of the transmission.\n", 1);
		exit(EXIT_SUCCESS);
	}
	send_bit(g_client.pid, bit);
}

int	main(int ac, char **av)
{
	pid_t	pid;
	if (ac != 3)
		ft_error("Usage: ./client [PID] [string to send]");
	pid = ft_atoi(av[1]);
	if (pid < 1)
		ft_error("Wrong PID");
	g_client.mess = av[2];
	g_client.pid = pid;
	signal(SIGUSR1, send_next_bit);
	signal(SIGUSR2, send_next_bit);
	send_bit(g_client.pid, get_bit(g_client.mess));
	while (1)
	{
		if (sleep(1) == 0)
			ft_error("Transmission failed.\nPlease relaunch the server");
	}
	return (0);
}
