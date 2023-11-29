/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _collec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:33:14 by jrim              #+#    #+#             */
/*   Updated: 2022/05/10 21:59:15 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collec(t_game *game, t_player *player);
void	_collec_msg(t_player *player);
void	_alt_collec(t_game *game, int c_pos);

void	collec(t_game *game, t_player *player)
{
	int	p_pos;
	int	*c_pos;
	int	idx;

	p_pos = player->x_pos * 100 + player->y_pos;
	c_pos = game->maps.c_pos;
	idx = 0;
	while (idx < player->c_tot)
	{
		if (c_pos[idx] != -1 && c_pos[idx] == p_pos)
		{
			player->c_cur++;
			_alt_collec(game, c_pos[idx]);
			_collec_msg(player);
			c_pos[idx] = -1;
		}
		idx++;
	}
}

void	_collec_msg(t_player *player)
{
	int	c_left;

	c_left = player->c_tot - player->c_cur;
	if (c_left == 0)
		ft_putstr_fd("\033[0;32myou have collected all items!\n\033[0;37m", 1);
	else
		msg_dfl("\033[0;32myou have collected an item\033[0;37m (", \
		c_left, " left)");
}

void	_alt_collec(t_game *game, int c_pos)
{
	int		x_pos;
	int		y_pos;
	char	**map;

	x_pos = c_pos / 100;
	y_pos = c_pos % 100;
	map = game->maps.coord;
	map[y_pos][x_pos] = '0';
}
