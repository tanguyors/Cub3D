#include "cub3d.h"

int check_file_extension(char *filename)
{
    char    *dot;

    if (!filename)
        return (0);
    dot = ft_strrchr(filename, '.');
    if (!dot)
        return (0);
    if (ft_strncmp(dot, ".cub", 5) != 0)
        return (0);
    return (1);
}

int check_file_acces(char *filename)
{   
    int fd;

    if(!filename)
        return(0);
    fd = open(filename, O_RDONLY);
    if(fd == -1)
        return(0);
    close(fd);
    return(1);
}