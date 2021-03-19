#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

unsigned long		get_time()
{
	struct timeval	now;
	unsigned long	ms;

	gettimeofday(&now, NULL);
	ms = now.tv_sec * 1000;
	ms += now.tv_usec / 1000;
	return (ms);
}

int		main(void)
{
	unsigned long start;

	start = get_time();
	while (1)
	{
		printf("%lu\n", get_time() - start);
		usleep(200 * 1000);
	}
}
