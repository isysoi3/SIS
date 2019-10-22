#include <stdio.h>
#include <Windows.h> 
#include <locale.h>
#pragma warning(disable:4996)

int isValidFile(const char fileName[], const char signature[]) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		return 0;
	}

	char* buffer = NULL;
	long file_size;
	long read_size;

	fseek(file, 0L, SEEK_END);
	file_size = ftell(file);
	rewind(file);


	buffer = (char*)malloc(sizeof(char) * (file_size + 1));
	read_size = fread(buffer, sizeof(char), file_size, file);

	buffer[file_size] = '\0';

	if (file_size == read_size)
	{
		char subbuff[4];

		for (int i = 0; i < file_size - 2; i++) {
			memcpy(subbuff, &buffer[i], 3);
			subbuff[3] = '\0';
			if (strcmp(subbuff, signature) == 0) {
				free(buffer);
				fclose(file);
				return 1;
			}
		}
	}
	fclose(file);
	free(buffer);
	return 0;
}

int main() {
	setlocale(LC_ALL, "russian");

	WIN32_FIND_DATA findData;
	HANDLE hFind;
	if ((hFind = FindFirstFile("./\\*", &findData)) != INVALID_HANDLE_VALUE) {
		do {
			printf("%s\n", findData.cFileName);
			if (isValidFile(findData.cFileName, "*.*")) {
				printf("%s -- will be removed\n", findData.cFileName);
				remove(findData.cFileName);
			}
		} while (FindNextFile(hFind, &findData) != 0);
		FindClose(hFind);
	}

	system("pause");

	return 0;
}