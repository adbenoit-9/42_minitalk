/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:40:44 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/12 04:07:52 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_error(char *str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
	exit(0);
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

static void	sig_handle(int signum)
{
	if (signum == SIGUSR2)
		ft_error("server.");
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int		bit;
	
	if (ac != 3)
		ft_error("Usage: ./client [PID] [string to send]");
	pid = ft_atoi(av[1]);
	if (pid < 1)
		ft_error("Wrong PID");
	signal(SIGUSR1, sig_handle);
	signal(SIGUSR2, sig_handle);
	while (1)
	{
		bit = get_bit(av[2]);
		usleep(200);
		if (bit == -1)
		{
			ft_putendl_fd("End of the transmission.", 1);
			return (0);
		}
		send_bit(pid, bit);
	}
	return (0);
}
