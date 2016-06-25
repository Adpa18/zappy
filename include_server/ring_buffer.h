/*
** ring_buffer.h for CIRCULAR BUFFER in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myirc
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Fri Jun  3 09:46:55 2016 Victor Gouet
** Last update Fri Jun  3 10:17:50 2016 Victor Gouet
*/

#ifndef RING_BUFFER_HPP_
# define RING_BUFFER_HPP_

typedef struct	s_ring_buffer
{
  int		begin;
  int		end;
  char		buffer[512];
}		t_ring_buffer;

void	reset(t_ring_buffer *ring);

#endif
