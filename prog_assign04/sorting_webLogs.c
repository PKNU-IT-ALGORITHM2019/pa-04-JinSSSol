#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NWEBLOGS 20000
#define MAX 1000
#define BUFFER_LENGTH 100

typedef struct webLog {
	char ip[BUFFER_LENGTH];
	char time[BUFFER_LENGTH];
	char URL[BUFFER_LENGTH];
	char status[BUFFER_LENGTH];
}Web;

void load();
int compare_time(const void *first, const void *second);
int month_to_num(char month[]);
int compare_ip(const void *first, const void *second);
void print(int sorting_type);

Web* webs;
int n = 0;

int main() {
	webs = (Web *)malloc(NWEBLOGS * sizeof(Web)); //webs: Web의  배열
	int sorting_type = 0; //1: time, 2:ip

	while (1) {
		char command[BUFFER_LENGTH];
		char type[BUFFER_LENGTH];
		printf("$ ");
		scanf("%s", command);
		if (strcmp(command, "read") == 0) load();
		else if (strcmp(command, "sort") == 0) {
			scanf("%s", type);
			if (strcmp(type, "-t") == 0) {
				qsort(webs, n, sizeof(Web), compare_time);
				sorting_type = 1;
			}
			else if (strcmp(type, "-ip") == 0) {
				qsort(webs, n, sizeof(Web), compare_ip);
				sorting_type = 2;
			}
			else printf("Error SortingType.\n");
		}
		else if (strcmp(command, "print") == 0) print(sorting_type);
		else if (strcmp(command, "exit") == 0) break;
		else printf("Error Command.\n");
	}
	free(webs);
	getchar();
	return 0;
}

void load()
{
	char filename[BUFFER_LENGTH];
	scanf("%s", filename);
	FILE *fp = fopen(filename, "r");
	char str[MAX];
	fgets(str, MAX, fp);
	while (!feof(fp)) {
		fgets(str, MAX, fp);

		char *token = strtok(str, ","); //첫 토큰:IP
		strcpy(webs[n].ip, token);
		token = strtok(NULL, "[,");  //두번째 토큰:time
		strcpy(webs[n].time, token);
		token = strtok(NULL, ",");   //세번째 토큰: URL
		strcpy(webs[n].URL, token);
		token = strtok(NULL, ",");  //네번째 토큰: status
		strcpy(webs[n].status, token);
		n++;
	}
	fclose(fp);
}

int compare_time(const void *first, const void *second) {
	char tmp_first[BUFFER_LENGTH], tmp_second[BUFFER_LENGTH];
	strcpy(tmp_first, ((Web *)first)->time);
	strcpy(tmp_second, ((Web *)second)->time);
	char time1[4][BUFFER_LENGTH];
	char time2[4][BUFFER_LENGTH];
	char *token_first = strtok(tmp_first, "/ ");
	strcpy(time1[0], token_first);
	token_first = strtok(NULL, "/ ");
	strcpy(time1[1], token_first);
	token_first = strtok(NULL, "/: ");
	strcpy(time1[2], token_first);
	token_first = strtok(NULL, "/ ");
	strcpy(time1[3], token_first);

	char *token_second = strtok(tmp_second, "/ ");
	strcpy(time2[0], token_second);
	token_second = strtok(NULL, "/ ");
	strcpy(time2[1], token_second);
	token_second = strtok(NULL, "/: ");
	strcpy(time2[2], token_second);
	token_second = strtok(NULL, "/ ");
	strcpy(time2[3], token_second);

	int result = strcmp(time1[2], time2[2]);          //Year 검사
	if (result != 0) return result;

	int day1 = month_to_num(time1[1]);                 //Month 검사
	int day2 = month_to_num(time2[1]);
	result = day1 - day2;
	if (result != 0)return result;

	result = strcmp(time1[0], time2[0]);             //Day 검사
	if (result != 0)return result;

	return strcmp(time1[3], time2[3]);               //clock(시간) 검사 

}

int month_to_num(char month[])
{
	if (strcmp(month, "Jan") == 0) return 1;
	if (strcmp(month, "Feb") == 0) return 2;
	if (strcmp(month, "Mar") == 0) return 3;
	if (strcmp(month, "Apr") == 0) return 4;
	if (strcmp(month, "May") == 0) return 5;
	if (strcmp(month, "Jun") == 0) return 6;
	if (strcmp(month, "Jul") == 0) return 7;
	if (strcmp(month, "Aug") == 0) return 8;
	if (strcmp(month, "Sep") == 0) return 9;
	if (strcmp(month, "Oct") == 0) return 10;
	if (strcmp(month, "Nov") == 0) return 11;
	if (strcmp(month, "Dec") == 0) return 12;
	return -1;
}

int compare_ip(const void *first, const void *second) {
	int result = strcmp(((Web *)first)->ip, ((Web *)second)->ip);
	if (result != 0) return result;
	return compare_time(first, second);
}

void print(int sorting_type)
{
	if (sorting_type == 1) {
		for (int i = 0; i < n; i++) {
			printf("%s\n", webs[i].time);
			printf("   IP: %s\n", webs[i].ip);
			printf("   URL: %s\n", webs[i].URL);
			printf("   Status: %s", webs[i].status);
		}
	}

	else if (sorting_type == 2) {
		for (int i = 0; i < n; i++) {
			printf("%s\n", webs[i].ip);
			printf("   Time: %s\n", webs[i].time);
			printf("   URL: %s\n", webs[i].URL);
			printf("   Status: %s", webs[i].status);
		}
	}

	else printf("Not Sorted.\n");
}