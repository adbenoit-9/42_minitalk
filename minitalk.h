/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:26:24 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/12 20:21:52 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/inc/libft.h"
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>

typedef struct s_trans
{
	pid_t	pid;
	char	*mess;
}				t_trans;

#endif
