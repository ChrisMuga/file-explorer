#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void check_directories(char* path, char* separator){
	struct dirent *entry;

	DIR *dir = opendir(path);

	if (dir == NULL) {
		printf("Directory cannot be opened!");
	}else{
		int counter = 0;
		while ((entry = readdir(dir))) {
			int ignore = (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0);

			// Print entry name
			if(ignore == 0){
				printf("%s %s\n", separator, entry->d_name);
			}

			// Check if current entry is a directory
			DIR *nested_dir = opendir(entry->d_name);
			
			// If not a directory: no-op
			if(nested_dir == NULL){
			}else{
				// We're skipping . and .. entries which cause segfaults
				if(ignore == 1){
					// No-op
				}else{
					// Otherwise make a recursive call on the found directory
					check_directories(entry->d_name, "\t");
				}
			}
			counter += 1;
		}
	}
	closedir(dir);
}

int main(){
	check_directories(".", "");
	return 0;
}

