#ifndef MONITOR_H
#define MONITOR_H

#include <stdio.h>
#include <stdlib.h>

#include <sys/inotify.h>

#include <limits.h>

// read one event
#define BUF_SIZE sizeof(struct inotify_event) + NAME_MAX + 1

void add_watch_for_file_modified(int fd, const char* filename);

void read_events_from_inotify(int fd);

#endif
