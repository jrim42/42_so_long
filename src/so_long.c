/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:28:27 by jrim              #+#    #+#             */
/*   Updated: 2022/05/10 22:00:22 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		key_press(int key, t_game *game);
int		main_loop(t_game *game);
void	end_check(t_game *game, t_player *player);
int		game_end(t_game *game);

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		msg_err("[usage]: ./so_long [FILENAME.ber]");
	map_read(&game, argv[1]);
	map_check(&game, game.maps.coord);
	game_init(&game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &game_end, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

int	key_press(int key, t_game *game)
{
	if (key == KEY_EXIT)
		game_end(game);
	else if (key == KEY_A || key == KEY_LF)
		move(game, &game->player, DIR_LF);
	else if (key == KEY_S || key == KEY_DW)
		move(game, &game->player, DIR_DW);
	else if (key == KEY_D || key == KEY_RT)
		move(game, &game->player, DIR_RT);
	else if (key == KEY_W || key == KEY_UP)
		move(game, &game->player, DIR_UP);
	return (0);
}

int	main_loop(t_game *game)
{
	map_gen(game);
	if (game->end == 1)
	{
		ft_putstr_fd("\033[0;32mcongrats!\n\033[0;37m", 1);
		msg_dfl("total step : ", game->player.step, 0);
		game_end(game);
	}
	return (0);
}

void	end_check(t_game *game, t_player *player)
{
	int	c_left;

	c_left = player->c_tot - player->c_cur;
	if (player->x_pos == player->x_end && player->y_pos == player->y_end)
	{
		if (c_left == 0)
			game->end = 1;
		else
			msg_dfl(0, c_left, " items left! you can't leave!");
	}
}

int	game_end(t_game *game)
{
	ft_putstr_fd("\033[0;33mbye!\n\033[0;37m", 1);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}
