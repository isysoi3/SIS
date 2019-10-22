// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
//
#include <stdio.h>
#include <string.h>

void print() {
	printf("%s", "*.*");
}

void printToFile() {
	FILE *fp;
	char const *str = "*.*";

	fp = fopen("out.txt", "w");
	fwrite(str, strlen(str), 1, fp);

	fclose(fp);
}

int main() {
	print();
	printToFile();
	return 0;
}

