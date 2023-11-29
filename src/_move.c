/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _move.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:31:09 by jrim              #+#    #+#             */
/*   Updated: 2022/05/10 21:55:06 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move(t_game *game, t_player *player, int new_dir);
void	_alt_dir(t_game *game, t_player *player, int new_dir);
int		_stuck(char **map, t_player *player, int new_dir);
void	_alt_tile(t_player *player, char **map);
void	_alt_pos(t_player *player, int new_dir);

void	move(t_game *game, t_player *player, int new_dir)
{
	_alt_dir(game, player, new_dir);
	if (_stuck(game->maps.coord, player, new_dir) == 1)
		return ;
	_alt_tile(player, game->maps.coord);
	_alt_pos(player, new_dir);
	collec(game, player);
	game->maps.coord[player->y_pos][player->x_pos] = 'P';
	end_check(game, player);
}

void	_alt_dir(t_game *game, t_player *player, int new_dir)
{
	if (new_dir == DIR_LF && player->dir != DIR_LF)
		player->p_img.ptr = file_to_img(game, "img/p_left.xpm");
	else if (new_dir == DIR_RT && player->dir != DIR_RT)
		player->p_img.ptr = file_to_img(game, "img/p_right.xpm");
}

int	_stuck(char **map, t_player *player, int new_dir)
{
	int	x;
	int	y;

	x = player->x_pos;
	y = player->y_pos;
	if (new_dir == DIR_UP && map[y - 1][x] == '1')
		return (1);
	else if (new_dir == DIR_DW && map[y + 1][x] == '1')
		return (1);
	else if (new_dir == DIR_LF && map[y][x - 1] == '1')
		return (1);
	else if (new_dir == DIR_RT && map[y][x + 1] == '1')
		return (1);
	return (0);
}

void	_alt_tile(t_player *player, char **map)
{
	if (player->x_pos == player->x_end && player->y_pos == player->y_end)
		map[player->y_pos][player->x_pos] = 'E';
	else
		map[player->y_pos][player->x_pos] = '0';
}

void	_alt_pos(t_player *player, int new_dir)
{
	if (new_dir == DIR_UP)
		player->y_pos--;
	else if (new_dir == DIR_DW)
		player->y_pos++;
	else if (new_dir == DIR_LF)
		player->x_pos--;
	else if (new_dir == DIR_RT)
		player->x_pos++;
	player->dir = new_dir;
	player->step++;
	msg_dfl("step : ", player->step, 0);
}
