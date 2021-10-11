/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:40:44 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/12 00:29:30 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* indicates the status of the transmission
is equal to 1 if it has received a confirmation that the signal has been
received by the server. Otherwise is equal to 0 */

bool	g_status;

/* indicates the reception of the signal by modifying the status */

static void	server_response(int signum)
{
	if (signum == SIGUSR1)
		g_status = 1;
}

/* wait a few microseconds for the confirmation signal from the server
If the signal isn't received, the program quit */

static void	wait_signal(void)
{
	int	loop;

	loop = 0;
	while (loop > 5 || g_status == 0)
	{
		usleep(10);
		++loop;
		if (loop > 30)
		{
			ft_putendl_fd("Transmission Failed.", 2);
			exit(1);
		}
	}
}

static void	send_char(pid_t pid, char c)
{
	bool	bit;
	int		i;

	i = 0;
	while (i < 8)
	{
		bit = (c >> i) & 1;
		g_status = 0;
		if (bit == 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_error("No such process");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_error("No such process");
		}
		wait_signal();
	}
}

static void	send_str(pid_t pid, char *str)
{
	int	i;

	i = 0;
	usleep(100);
	while (str[i])
	{
		send_char(pid, str[i]);
		++i;
	}
	ft_putendl_fd("Transmission succeed.", 1);
	send_char(pid, 0);
	exit(0);
}

int	main(int ac, char **av)
{
	pid_t	pid;

	signal(SIGUSR1, server_response);
	if (ac != 3)
		ft_error("Usage: ./client [PID] [string to send]");
	g_status = 0;
	pid = ft_atoi(av[1]);
	if (pid < 1)
		ft_error("Wrong PID");
	send_str(pid, av[2]);
	return (0);
}
