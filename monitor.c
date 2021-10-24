#include "monitor.h"

int main(int argc, char **argv) {

  int fd = inotify_init();

  if (fd < 0) {
    perror("inotify_init()");
    return EXIT_FAILURE;
  }

  for (int i = 1; i <= argc-1; ++i) {
    add_watch_for_file_modified(fd, argv[i]);
  }

  read_events_from_inotify(fd);

  return 0;
}

void add_watch_for_file_modified(int fd, const char* filename) {

  if (is_directory(filename)) {
    printf("current path: %s, cannot be a directory\n", filename);
    exit(EXIT_FAILURE);
  }

  // TODO: link watch descriptor with filename
  int watch_fd = inotify_add_watch(fd, filename, IN_MODIFY);

  if (watch_fd < 0) {
    perror("inotify_add_watch()");
    exit(EXIT_FAILURE);
  }
}

void read_events_from_inotify(int fd) {

  char buf[BUF_SIZE];
  struct inotify_event *nevt;

  while(1) {

    if (read(fd, buf, sizeof(buf)) < 0) {
      perror("read()");
      continue;
    }

    nevt = (struct inotify_event *)buf;

    // TODO: Print filename from watch descriptor
    printf("[EVENT] [MODIFIED]\t%s\n", nevt->name);
  }
}

bool is_directory(const char* filename) {

  struct stat sb;

  if (lstat(filename, &sb) == -1) {
    perror("lstat()");
    exit(EXIT_FAILURE);
  }

  switch (sb.st_mode & S_IFMT) {
    case S_IFDIR:
      return true;
    default:
      return false;
  }
}
