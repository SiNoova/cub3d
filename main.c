/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:08:02 by ymassiou          #+#    #+#             */
/*   Updated: 2025/02/08 16:29:00 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	terminate(void *param)
{
	int		i;
	t_cub	*cub;

	i = 0;
	cub = (t_cub *)param;
	clear_textures(cub);
	while (cub->sprites_ready == true && i < 13)
	{
		if (cub->sprites.textures[i])
			mlx_delete_texture(cub->sprites.textures[i]);
		i++;
	}
	if (cub->mlx_window && cub->sprites.img)
		mlx_delete_image(cub->mlx_window, cub->sprites.img);
	if (cub->mlx_window && cub->mlx_img)
		mlx_delete_image(cub->mlx_window, cub->mlx_img);
	if (cub->mlx_window)
		mlx_terminate(cub->mlx_window);
	gc_free(cub);
	free_trash(cub->garbage);
	close(cub->map_fd);
	exit(0);
}

void	keyhook(mlx_key_data_t key, void *param)
{
	t_cub				*cub;
	static int			doors_opened;

	cub = (t_cub *)param;
	if (key.action == MLX_PRESS && key.key == MLX_KEY_O && !doors_opened)
	{
		change_map(cub, '2', '3');
		doors_opened = 1;
	}
	else if (key.action == MLX_PRESS && key.key == MLX_KEY_O
		&& doors_opened && cub->map[(long)(cub->player->y / TILESIZE)]
		[(long)(cub->player->x / TILESIZE)] != '3')
	{
		change_map(cub, '3', '2');
		doors_opened = 0;
	}
	if (key.action == MLX_PRESS && key.key == MLX_KEY_ESCAPE)
		terminate(cub);
}

void	terminate_on_error(t_cub *cub)
{
	size_t	i;

	i = 0;
	mlx_delete_texture(cub->ea_pic_data);
	mlx_delete_texture(cub->we_pic_data);
	mlx_delete_texture(cub->so_pic_data);
	mlx_delete_texture(cub->no_pic_data);
	mlx_delete_texture(cub->door_pic_data);
	while (i < 13)
	{
		mlx_delete_texture(cub->sprites.textures[i]);
		i++;
	}
	gc_free(cub);
	free_trash(cub->garbage);
}

int	render(t_cub *cub)
{
	cub->mlx_window = mlx_init(WIN_WIDTH, W_HEIGHT, "cub3d", true);
	if (!cub->mlx_window)
		return (terminate_on_error(cub), -1);
	cub->mlx_img = mlx_new_image(cub->mlx_window,
			WIN_WIDTH, W_HEIGHT);
	if (!cub->mlx_img)
	{
		mlx_terminate(cub->mlx_window);
		return (terminate_on_error(cub), -1);
	}
	if (mlx_image_to_window(cub->mlx_window,
			cub->mlx_img, 0, 0) < 0)
	{
		mlx_delete_image(cub->mlx_window, NULL);
		mlx_terminate(cub->mlx_window);
		return (terminate_on_error(cub), -1);
	}
	mlx_get_mouse_pos(cub->mlx_window, &cub->x_mouse, &cub->y_mouse);
	put_frame(cub);
	sprite(cub, 1, 0);
	mlx_loop_hook(cub->mlx_window, my_keyhook, cub);
	mlx_key_hook(cub->mlx_window, keyhook, cub);
	mlx_close_hook(cub->mlx_window, terminate, cub);
	mlx_loop(cub->mlx_window);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
	{
		ft_putstr_fd("Error: Usage: cub3D <MAP.cub>\n", 2);
		return (EXIT_FAILURE);
	}
	if (map_check(&cub, av[1]) == -1)
	{
		close(cub.map_fd);
		gc_free(&cub);
		free_trash(cub.garbage);
		return (EXIT_FAILURE);
	}
	if (render(&cub) == -1)
	{
		close(cub.map_fd);
		return (EXIT_FAILURE);
	}
	close(cub.map_fd);
	return (EXIT_SUCCESS);
}
