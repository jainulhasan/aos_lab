#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void listFiles(const char *path, int showHidden, int recursive, int longFormat) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir))) {
        char fullpath[1024]; // Adjust the buffer size as needed
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (!showHidden && entry->d_name[0] == '.') {
            continue; // Skip hidden files and directories
        }

        if (stat(fullpath, &statbuf) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        if (S_ISDIR(statbuf.st_mode)) {
            if (recursive && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                printf("%s/\n", fullpath);
                listFiles(fullpath, showHidden, recursive, longFormat);
            }
        } else {
            if (long_format) {
            struct passwd *pw = getpwuid(file_info.st_uid);
            struct group *gr = getgrgid(file_info.st_gid);
            struct tm *tm_info = localtime(&file_info.st_mtime);

            printf("%s %6ld %s %s %5ld %4d-%02d-%02d %02d:%02d %s\n",
                   (S_ISDIR(file_info.st_mode) ? "d" : "-"),
                   (long)file_info.st_size,
                   (pw ? pw->pw_name : "?"),
                   (gr ? gr->gr_name : "?"),
                   (long)file_info.st_size,
                   1900 + tm_info->tm_year,
                   tm_info->tm_mon + 1,
                   tm_info->tm_mday,
                   tm_info->tm_hour,
                   tm_info->tm_min,
                   entry->d_name);
        }  else {
                printf("%s\n", fullpath);
            }
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *path = "."; // Default to current directory
    int showHidden = 0;     // Do not show hidden files by default
    int recursive = 0;      // Do not list recursively by default
    int longFormat = 0;     // Do not use long format by default

    if (argc > 1) {
        if (argv[1][0] != '-') {
            // If the first argument doesn't start with '-', treat it as the directory name.
            path = argv[1];
            argv++;
            argc--;
        }

        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-l") == 0) {
                longFormat = 1;
            } else if (strcmp(argv[i], "-a") == 0) {
                showHidden = 1;
            } else if (strcmp(argv[i], "-R") == 0) {
                recursive = 1;
            }
        }
    }

    listFiles(path, showHidden, recursive, longFormat);

    return 0;
}
