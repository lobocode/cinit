#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRECTORIES 8
#define CMD_SIZE 512
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

const char *directories[MAX_DIRECTORIES] = {
    "src",
    "build",
    "include",
    "data",
    "libs",
    "tools",
    "docs",
    "tests"
};

const char *makefile_content = 
    "all: build\n"
    "\n"
    "build:\n"
    "\tgcc -o bin/hello src/hello.c\n"
    "\n"
    "clean:\n"
    "\trm -f bin/hello\n";

const char *helloworld_content =
    "#include <stdio.h>\n"
    "\n"
    "int main() {\n"
    "\tprintf(\"Hello, world!\\n\");\n"
    "\treturn 0;\n"
    "}\n";

void create_directories(const char *project_name, const char *name);
void init_git(const char *project_name);
void write_file(const char *path, const char *content);

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <project_name>\n", argv[0]);
        return 1;
    }

    char *project_name = argv[1];
    create_directories(".", project_name);

    for (int i = 0; i < ARRAY_SIZE(directories); i++) {
        create_directories(project_name, directories[i]);
    }

    char makefile_path[CMD_SIZE];
    snprintf(makefile_path, sizeof(makefile_path), "%s/Makefile", project_name);
    write_file(makefile_path, makefile_content);

    char main_path[CMD_SIZE];
    snprintf(main_path, sizeof(main_path), "%s/src/main.c", project_name);
    write_file(main_path, helloworld_content);

    init_git(project_name);

    printf("Project '%s' initialized successfully!\n", project_name);
    return 0;
}

void create_directories(const char *project_name, const char *name) {
    char cmd[CMD_SIZE];
    snprintf(cmd, sizeof(cmd), "mkdir -p %s/%s", project_name, name);
    if (system(cmd) != 0) {
        perror("Failed to create directory");
        exit(EXIT_FAILURE);
    }
}

void init_git(const char *project_name) {
    char cmd[CMD_SIZE];
    snprintf(cmd, sizeof(cmd), "cd %s && git init", project_name);
    if (system(cmd) != 0) {
        perror("Failed to initialize git");
        exit(EXIT_FAILURE);
    }
}

void write_file(const char *path, const char *content) {
    FILE *f = fopen(path, "w");
    if (!f) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    fprintf(f, "%s", content);
    fclose(f);
}
