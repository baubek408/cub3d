#include "include/cube.h"

int main()
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    if (!mlx)
    {
        printf("Failed to initialize MLX\n");
        return 1;
    }

    win = mlx_new_window(mlx, 400, 300, "Test");
    if (!win)
    {
        printf("Failed to create window\n");
        return 1;
    }

    printf("MLX initialized successfully\n");
    mlx_destroy_window(mlx, win);
    mlx_destroy_display(mlx);
    return 0;
}
