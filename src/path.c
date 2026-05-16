#include "shell.h"
#include "path.h"

char *find_executable(const char *command) {
    char *path = getenv("PATH");
    
    if (!path)
        return NULL;
    
    char *path_copy = strdup(path);
    char *saveptr;
    char *dir = strtok_r(path_copy, ":", &saveptr);
    char *fullpath = malloc(256 * sizeof(char));

    while (dir != NULL) {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dir, command);

        if ((access(fullpath, F_OK)) == 0 && access(fullpath, X_OK) == 0) {
            free(path_copy);
            return fullpath;
        }

        dir = strtok_r(NULL, ":", &saveptr);
    }

    free(path_copy);
    free(fullpath);

    return NULL;
}
