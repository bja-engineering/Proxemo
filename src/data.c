#include <tizen.h>
#include <app.h>
#include <efl_extension.h>
#include <dlog.h>
#include <proxemo.h>
#include "data.h"
#include <storage.h>
#include <dirent.h>

#include "view.h"

typedef struct node {
	char name[256];
	struct node * next;
	struct node * previous;
} currentUser;

currentUser * head = NULL;

/*
 * @brief Initialization function for data module
 */
void data_initialize(void) {
}

void getCurrentUserName(char* currentUserName){
	memcpy(currentUserName,head->name,sizeof head->name);
	currentUserName[strlen(currentUserName)-4] = '\0';
	dlog_print(DLOG_INFO, "selfProxemo", "InsidegetCurrentUserName");
	dlog_print(DLOG_INFO, "selfProxemo", currentUserName);
}

//Loads all Pictures from STORAGE_DIRECTORY_IMAGES and saves them as LinkedList with start and endNode connected
void loadAllPictures(void) {
	head = malloc(sizeof(currentUser));
	if (head == NULL) {
		return;
	}
	head->name[0] = 0;
	head->next = NULL;
	head->previous = NULL;

	char *directoryPath;

	storage_get_directory(0, STORAGE_DIRECTORY_IMAGES, &directoryPath);

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(directoryPath)) != NULL) {
		/* print all the files and directories within directory */
		currentUser * current = head;
		while ((ent = readdir(dir)) != NULL) {
			if (strcmp(ent->d_name,".") == 0 || strcmp(ent->d_name,"..") == 0){
				continue;
			}
			dlog_print(DLOG_INFO, "selfProxemo", ent->d_name);
			if (current->name[0] == 0) {
				memcpy(current->name,ent->d_name,sizeof current->name);
			} else {
				current->next = malloc(sizeof(currentUser));
				memcpy(current->next->name,ent->d_name,sizeof current->next->name);
				current->next->next = NULL;
				current->next->previous = current;
				current = current->next;
			}
		}
		current->next = head;
		head->previous = current;
		closedir(dir);
	}
	view_set_image(view_dialer_get_layout_object(), "user1", data_get_image_path(head->name));
	//view_set_text(view_dialer_get_layout_object(), "user1", head->name);
	free(directoryPath);
	return;
}

void nextUser(void){
	head = head->next;
	dlog_print(DLOG_INFO, "selfProxemo", "InsideNextUser");
	dlog_print(DLOG_INFO, "selfProxemo", head->name);
	view_set_image(view_dialer_get_layout_object(), "user1", data_get_image_path(head->name));
	//view_set_text(view_dialer_get_layout_object(), "user1", head->name);
}

void previousUser(void){
	head = head->previous;
	dlog_print(DLOG_INFO, "selfProxemo", "InsidePreviousUser");
	dlog_print(DLOG_INFO, "selfProxemo", head->name);
	view_set_image(view_dialer_get_layout_object(), "user1", data_get_image_path(head->name));
	//view_set_text(view_dialer_get_layout_object(), "user1", head->name);
}

/*
 * @brief Finalization function for data module
 */
void data_finalize(void) {
}

/*
 * @brief Get full path of resource
 * @param[in] file_path File path of target file
 * @param[out] full_path Full file path concatenated with resource path
 * @param[in] path_max Max length of full file path
 */
void data_get_full_path(const char *file_path, char *full_path, int path_max) {
	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(full_path, path_max, "%s%s", res_path, file_path);
		free(res_path);
	}
}

/*
 * @brief Get path of image file from STORAGE_DIRECTORY_IMAGES
 * @param[in] part_name Part name of the target image path
 */
char *data_get_image_path(const char *part_name) {
	dlog_print(DLOG_INFO, "selfProxemo", "Inside dataGetImmagePath");
	char *ret = NULL;
	char *directoryPath;
	char read_filepath[1000];

	storage_get_directory(0, STORAGE_DIRECTORY_IMAGES, &directoryPath);
	snprintf(read_filepath, sizeof(read_filepath), "%s%s%s", directoryPath, "/",
			part_name);
	dlog_print(DLOG_INFO, "selfProxemo", read_filepath);
	dlog_print(DLOG_INFO, "selfProxemo", directoryPath);

	ret = strdup(read_filepath);
	free(directoryPath);
	return ret;
}

/*
 * Writes the CSV file to STORAGE_DIRECTORY_DOCUMENTS if it dose not exist and appends the given char*
 */
void data_write_file(const char* buffer) {
	dlog_print(DLOG_INFO, "selfProxemo", "Inside dataWriteFile");
	FILE *fp;
	char *directoryPath;
	char write_filepath[1000];

	storage_get_directory(0, STORAGE_DIRECTORY_DOCUMENTS, &directoryPath);
	snprintf(write_filepath, sizeof(write_filepath), "%s%s", directoryPath,
			"/ProxemoLog.csv");
	dlog_print(DLOG_INFO, "selfProxemo", write_filepath);
	dlog_print(DLOG_INFO, "selfProxemo", directoryPath);
	fp = fopen(write_filepath, "a"); //append creates the file if it dose not exist
	fputs(buffer, fp);
	fclose(fp);
	free(directoryPath);
}
