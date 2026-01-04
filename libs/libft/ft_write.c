#include <stdlib.h>
#include <unistd.h>

void	ft_write(int fdout, char *str, size_t len)
{
	ssize_t check_w = write(fdout, str, len);

	if ((len >> (sizeof(size_t) -1)) || check_w != (ssize_t)len)
		abort();
}