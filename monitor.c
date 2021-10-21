#include <stdio.h>
#include <stdlib.h>

#include <sys/inotify.h>

#include <limits.h>

#define BUF_SIZE sizeof(struct inotify_event) + NAME_MAX + 1

void exec_ctag_for_file();

int add_watch_for_file(const char* filename);

int main(int argc, char **argv) {

  int fd = inotify_init();

  if (fd < 0) {
    perror("inotify_init();");
    return EXIT_FAILURE;
  }

  // CRITICAL SESSION?
  char buf[BUF_SIZE];
  struct inotify_event *nevt;
  // CRITICAL SESSION?

  int watch_fd = inotify_add_watch(fd, argv[1], IN_MODIFY);

  if (watch_fd < 0) {
    perror("inotify_add_watch();");
    return EXIT_FAILURE;
  }

  while(1) {

    if (read(fd, buf, sizeof(buf)) < 0) {
      perror("read();");
      continue;
    }

    nevt = (struct inotify_event *)buf;

    printf("[%s]\t%s\n", "IN_MODIFY", nevt->name);
  }

  return 0;
}
