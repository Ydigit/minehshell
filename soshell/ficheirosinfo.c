#include "shell.h"


void getFileType(const char* filename) {
    struct stat fileStat;

    if (stat(filename, &fileStat) == -1) {
        perror("Error opening file, or file does not exist\n");
        exit(0);
    }

    if ((fileStat.st_mode & S_IFREG) == S_IFREG) {
        printf("%s: A regular file\n", filename);
    } else if ((fileStat.st_mode & S_IFDIR) == S_IFDIR) {
        printf("%s: A directory\n", filename);
    } else if ((fileStat.st_mode & S_IFCHR) == S_IFCHR) {
        printf("%s: A character device\n", filename);
    } else if ((fileStat.st_mode & S_IFBLK) == S_IFBLK) {
        printf("%s: A block device\n", filename);
    } else if ((fileStat.st_mode & S_IFLNK) == S_IFLNK) {
        printf("%s: A symbolic link\n", filename);
    } else if ((fileStat.st_mode & S_IFSOCK) == S_IFSOCK) {
        printf("%s: A socket\n", filename);
    } else if ((fileStat.st_mode & S_IFIFO) == S_IFIFO) {
        printf("%s: A FIFO/pipe\n", filename);
    } else {
        printf("%s: Unknown type\n", filename);
    }
    

}
