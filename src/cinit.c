#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *directories[] = {
    "src",
    "bin",
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

void create_directories(const char *project_name, const char *name) {
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "mkdir -p %s/%s", project_name, name);
    system(cmd);
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

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <project_name>\n", argv[0]);
        return 1;
    }

    char *project_name = argv[1];

    // Create main dir
    create_directories(".", project_name);


    // Create internal subdirs
    for (int i = 0; i < sizeof(directories) / sizeof(directories[0]); i++) {
        create_directories(project_name, directories[i]);
    }

    char makefile_path[512];
    snprintf(makefile_path, sizeof(makefile_path), "%s/Makefile", project_name);
    write_file(makefile_path, makefile_content);

    char main_path[512];
    snprintf(main_path, sizeof(main_path), "%s/src/main.c", project_name);
    write_file(main_path, helloworld_content);

    printf("Project '%s' initialized successfully!\n", project_name);

    return 0;

}
