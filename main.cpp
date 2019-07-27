#include <stdio.h>
#include <magic.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
	char *actual_file = "/bin/bash";
	const char *magic_full;
	magic_t magic_cookie;

	magic_cookie = magic_open(MAGIC_MIME);

	if (magic_cookie == NULL) {
		printf("unable to initialize magic library\n");
		return 1;
	}

	if (magic_load(magic_cookie, NULL) != 0) {
		printf("cannot load magic database - %s\n", magic_error(magic_cookie));
		magic_close(magic_cookie);
		return 1;
	}

#if 0
	magic_full = magic_file(magic_cookie, actual_file);
#else
	magic_full = NULL;
	char tmp[65536];
	int fd = open(actual_file, O_RDONLY);
	if (fd != -1) {
		int n = read(fd, tmp, sizeof(tmp));
		if (n > 0) {
			magic_full = magic_buffer(magic_cookie, tmp, sizeof(tmp));
		}
	}
#endif

	printf("%s\n", magic_full ? magic_full : "");
	magic_close(magic_cookie);
	return 0;
}
