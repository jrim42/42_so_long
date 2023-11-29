/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:13:30 by jrim              #+#    #+#             */
/*   Updated: 2022/05/04 21:06:30 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_init(t_game *game);
void	_init_img(t_game *game);
void	_init_p(t_game *game, t_player *player);
void	_init_c(t_game *game, t_map *map);

void	game_init(t_game *game)
{
	int	width;
	int	height;

	game->mlx = mlx_init();
	width = game->maps.rows * TILES;
	height = game->maps.cols * TILES;
	game->win = mlx_new_window(game->mlx, width, height, "titled goose game");
	game->end = 0;
	_init_img(game);
	_init_p(game, &game->player);
	_init_c(game, &game->maps);
}

void	_init_img(t_game *game)
{
	game->road.ptr = file_to_img(game, "img/road.xpm");
	game->wall.ptr = file_to_img(game, "img/wall.xpm");
	game->exit.ptr = file_to_img(game, "img/exit.xpm");
	game->collec.ptr = file_to_img(game, "img/key.xpm");
	game->player.p_img.ptr = file_to_img(game, "img/p_left.xpm");
}

void	_init_p(t_game *game, t_player *player)
{
	int		x;
	int		y;

	player->step = 0;
	player->c_cur = 0;
	player->dir = -1;
	y = 0;
	while (++y < game->maps.cols - 1)
	{
		x = 0;
		while (++x < game->maps.rows - 1)
		{
			if (game->maps.coord[y][x] == 'P')
			{
				player->x_pos = x;
				player->y_pos = y;
			}
			else if (game->maps.coord[y][x] == 'E')
			{
				player->x_end = x;
				player->y_end = y;
			}
		}
	}
}

void	_init_c(t_game *game, t_map *maps)
{
	char	**map;
	int		c_cnt;
	int		x;
	int		y;

	map = maps->coord;
	maps->c_pos = (int *)malloc(game->player.c_tot * sizeof(int));
	if (!maps->c_pos)
		msg_err("[error] : allocation failed");
	c_cnt = 0;
	y = 0;
	while (++y < game->maps.cols - 1 && c_cnt < game->player.c_tot)
	{
		x = 0;
		while (++x < game->maps.rows - 1)
			if (map[y][x] == 'C')
				maps->c_pos[c_cnt++] = x * 100 + y;
	}
}
