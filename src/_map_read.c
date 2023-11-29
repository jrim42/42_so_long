/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _map_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrim <jrim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:13:59 by jrim              #+#    #+#             */
/*   Updated: 2022/05/10 16:59:31 by jrim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_read(t_game *game, char *map_file);
void	_map_cnt(t_game *game, char *map_file);
void	_map_malloc(t_game *game);
void	_map_save(t_game *game, char *map_file);

void	map_read(t_game *game, char *map_file)
{
	_map_cnt(game, map_file);
	_map_malloc(game);
	_map_save(game, map_file);
}

void	_map_cnt(t_game *game, char *map_file)
{
	int		fd;
	char	*line;
	int		tot_cnt;
	int		col_cnt;
	int		row_cnt;

	fd = open(map_file, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		msg_err("[error] : file open failed or empty map");
	col_cnt = 0;
	row_cnt = ft_strlen(line) - 1;
	tot_cnt = 0;
	while (line != 0)
	{
		tot_cnt += ft_strlen(line) - 1;
		col_cnt++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if ((tot_cnt + 1) % col_cnt != 0)
		msg_err("[error] : not rectangle");
	game->maps.cols = col_cnt;
	game->maps.rows = row_cnt;
}

void	_map_malloc(t_game *game)
{
	int		col;
	int		row;
	int		idx;

	col = game->maps.cols;
	row = game->maps.rows;
	idx = -1;
	game->maps.coord = (char **)malloc(col * sizeof(char *));
	if (!game->maps.coord)
		msg_err("[error] : allocation failed");
	while (++idx < col)
	{
		game->maps.coord[idx] = (char *)malloc((row + 1) * sizeof(char));
		if (!game->maps.coord[idx])
			msg_err("[error] : allocation failed");
	}
}

void	_map_save(t_game *game, char *map_file)
{
	int		fd;
	int		x;
	int		y;
	char	*line;

	fd = open(map_file, O_RDONLY);
	y = -1;
	while (++y < game->maps.cols)
	{
		line = get_next_line(fd);
		x = -1;
		while (++x < game->maps.rows)
			game->maps.coord[y][x] = line[x];
		game->maps.coord[y][x] = '\0';
		free(line);
	}
	close(fd);
}
