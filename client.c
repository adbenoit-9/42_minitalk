/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 14:09:43 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/08 16:01:49 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"
#include <sys/types.h>
#include <signal.h>

int main(int ac, char **av)
{
    if (ac != 3)
        return (1);
    kill(ft_atoi(av[1]), SIGUSR1);
}