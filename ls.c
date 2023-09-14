#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void list_directory(const char *path, int show_hidden, int long_format, int recursive) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_info;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        exit(1);
    }

    if (!recursive)
        printf("Directory: %s\n", path);

    while ((entry = readdir(dir)) != NULL) {
        if (!show_hidden && entry->d_name[0] == '.')
            continue;

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (lstat(full_path, &file_info) == -1) {
            perror("lstat");
            exit(1);
        }

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
        } 
        else {
            printf("%s\n", entry->d_name);
        // }

        if (recursive && S_ISDIR(file_info.st_mode) && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            list_directory(full_path, show_hidden, long_format, recursive);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    int show_hidden = 0;
    int long_format = 0;
    int recursive = 0;
    char *directory = ".";

    // Check command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            show_hidden = 1;
        } else if (strcmp(argv[i], "-l") == 0) {
            long_format = 1;
        } else if (strcmp(argv[i], "-R") == 0) {
            recursive = 1;
        } else if (argv[i][0] != '-') {
            // If not an option, assume it's a directory
            directory = argv[i];
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            exit(1);
        }
    }

    list_directory(directory, show_hidden, long_format, recursive);

    return 0;
}
