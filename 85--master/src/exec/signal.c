/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:42:36 by dojannin          #+#    #+#             */
/*   Updated: 2023/04/20 12:42:37 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/include.h"

void sig_handler(int sig) {
   struct termios	conf;
   printf("signal %d\n", sig);
    if (sig == SIGINT) {
         printf("\nCTRL+C détecté. Sortie.\n");
         ioctl(ttyslot(), TIOCGETD, &conf);
         conf.c_lflag |= ECHO;
         ioctl(ttyslot(), TIOCSETD, &conf);
    }
}

void sig_quit(int sig)
{
   printf("signal %d\n", sig);
   if (sig == SIGQUIT) {
      printf("CTRL+D détecté. Sortie.\n");
      exit(0);
   }
}
