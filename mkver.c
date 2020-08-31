/**
 * mkver.c
 *
 * Generates a header file containing version information.
 * The build version is incremented automatically, while
 * major, minor and patch numbers are manually changed
 * when needed.
 *
 * Normally invoked as part of the build process.
 * Usage example: mkver ./version.h
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_FILE_SIZE 4096

#define MAJOR "__VERSION_MAJOR__"
#define MINOR "__VERSION_MINOR__"
#define PATCH "__VERSION_PATCH__"
#define BUILD "__VERSION_BUILD__"

struct semver {
	int major, minor, patch, build;
};

int tag_value(char *tag, char *content) {
	char *p = strstr(content, tag);
	if( p ) {
		p+=strlen(tag);
		return atoi(p);
	}
	return 0;
}

void save(char *filename, struct semver *v) {
	FILE *f = fopen(filename, "wt");
	if( !f ) {
		printf("Unable to write file: %s\n", filename);
		exit(1);
	}
	fprintf(f, "// mkver generated file.\n");
	fprintf(f, "#ifndef __VERSION__\n");
	fprintf(f, "#define %s %d\n", MAJOR, v->major);
	fprintf(f, "#define %s %d\n", MINOR, v->minor);
	fprintf(f, "#define %s %d\n", PATCH, v->patch);
	fprintf(f, "#define %s %d\n", BUILD, v->build);
	fprintf(f, "#define __VERSION__ \"%d.%d.%d.%d\"\n", v->major, v->minor, v->patch, v->build);
	fprintf(f, "#endif\n");
	fclose(f);
}

void load(char *filename, struct semver *v) {
	char buffer[MAX_FILE_SIZE];
	FILE *f=fopen(filename, "rt");
	if( f ) {
		int n = fread (buffer, 1, MAX_FILE_SIZE, f);
		buffer[n]=0;
		v->major = tag_value(MAJOR, buffer);
		v->minor = tag_value(MINOR, buffer);
		v->patch = tag_value(PATCH, buffer);
		v->build = tag_value(BUILD, buffer);
		fclose(f);
	}
	else {
		v->major = v->minor = v->patch = v->build = 0;
	}
}

int main(int argc, char **argv) {
	if( argc<=1 ) {
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	struct semver v;

	load(argv[1], &v);
	v.build++;
	save(argv[1], &v);

	return 0;
}
