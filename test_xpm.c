#include "include/cube.h"

int main()
{
    void *mlx;
    void *img;
    int width, height;

    mlx = mlx_init();
    if (!mlx)
    {
        printf("Failed to initialize MLX\n");
        return 1;
    }

    img = mlx_xpm_file_to_image(mlx, "textures/test.xpm", &width, &height);
    if (!img)
    {
        printf("Failed to load XPM file\n");
        return 1;
    }

    printf("XPM loaded successfully: %dx%d\n", width, height);
    mlx_destroy_image(mlx, img);
    mlx_destroy_display(mlx);
    return 0;
}
