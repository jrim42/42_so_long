/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:32:21 by jrim              #+#    #+#             */
/*   Updated: 2022/05/01 20:52:01 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	msg_err(char *msg);
void	msg_dfl(char *msg1, int num, char *msg2);
void	*file_to_img(t_game *game, char *str);
void	put_img(t_game *game, void *img_ptr, int x, int y);

void	msg_err(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

void	msg_dfl(char *msg1, int num, char *msg2)
{
	if (msg1 != 0)
		ft_putstr_fd(msg1, 1);
	ft_putnbr_fd(num, 1);
	if (msg2 != 0)
		ft_putstr_fd(msg2, 1);
	write(1, "\n", 1);
}

void	*file_to_img(t_game *game, char *str)
{
	void	*img;
	int		width;
	int		height;

	width = game->img_dlf.w;
	height = game->img_dlf.h;
	img = mlx_xpm_file_to_image(game->mlx, str, &width, &height);
	return (img);
}

void	put_img(t_game *game, void *img_ptr, int x, int y)
{
	int	x_pos;
	int	y_pos;

	x_pos = x * TILES;
	y_pos = y * TILES;
	mlx_put_image_to_window(game->mlx, game->win, img_ptr, x_pos, y_pos);
}
