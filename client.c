/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:40:44 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/10 15:22:18 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_error(char *str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
	exit(0);
}

static void	send_char(pid_t pid, char c)
{
	bool	bit;
	int		i;

	i = 0;
	while (i < 8)
	{
		bit = (c >> i) & 1;
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
		++i;
		usleep(100);
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
	ft_putendl_fd("The string has been sent.", 1);
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 3)
		ft_error("Usage: ./client [PID] [string to send]");
	pid = ft_atoi(av[1]);
	if (pid < 1)
		ft_error("Wrong PID");
	send_str(pid, av[2]);
	return (0);
}
