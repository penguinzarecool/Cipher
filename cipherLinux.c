#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

int charToInt(char ch) {
	switch (ch) {
		case '_': return 0;
		case 'A': return 1;
		case 'B': return 2;
		case 'C': return 3;
		case 'D': return 4;
		case 'E': return 5;
		case 'F': return 6;
		case 'G': return 7;
		case 'H': return 8;
		case 'I': return 9;
		case 'J': return 10;
		case 'K': return 11;
		case 'L': return 12;
		case 'M': return 13;
		case 'N': return 14;
		case 'O': return 15;
		case 'P': return 16;
		case 'Q': return 17;
		case 'R': return 18;
		case 'S': return 19;
		case 'T': return 20;
		case 'U': return 21;
		case 'V': return 22;
		case 'W': return 23;
		case 'X': return 24;
		case 'Y': return 25;
		case 'Z': return 26;
	}
}

char intToChar(int num) {
	switch (num) {
		case 0: return '_';
		case 1: return 'A';
		case 2: return 'B';
		case 3: return 'C';
		case 4: return 'D';
		case 5: return 'E';
		case 6: return 'F';
		case 7: return 'G';
		case 8: return 'H';
		case 9: return 'I';
		case 10: return 'J';
		case 11: return 'K';
		case 12: return 'L';
		case 13: return 'M';
		case 14: return 'N';
		case 15: return 'O';
		case 16: return 'P';
		case 17: return 'Q';
		case 18: return 'R';
		case 19: return 'S';
		case 20: return 'T';
		case 21: return 'U';
		case 22: return 'V';
		case 23: return 'W';
		case 24: return 'X';
		case 25: return 'Y';
		case 26: return 'Z';
	}
}

int Euclidean(int prime, int mod, int* counter) {
	int mult, math, m2;
	*counter = *counter + 1;
	if (mod % prime > 1) {
		mult = Euclidean(mod % prime, prime, counter);
	}
	if (mod % prime == 1) {
		return (mod - (mod % prime)) / prime;
	}
	math = (mod - (mod % prime)) / prime;
	m2 = (mult * (mod - (prime * math)) + 1) / prime;
	return (mult * math) + m2;
}

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int relativelyPrime(int a, int b) {
	return gcd(a, b) == 1 ? 1 : 0;
}

int* primeEncrypt(char *msgInput, int prime, int num2) {

	if (prime % 3 == 0) {
		printf("Your encryption key is invalid. Please choose a new key.\n");
		exit(0);
	}

	int length = strlen(msgInput);
	int *msgOutput = (int*)malloc(length * sizeof(int));
	if(msgOutput == NULL) {
		printf("Memory allocation for msgOut failed\n");
		return NULL;
	}

	for(int i = 0; i < length; i++) {
		msgOutput[i] = charToInt(msgInput[i]);
	}

	int answer;
	for(int i = 0; i < length - 1; i++) {
		answer = ((prime * msgOutput[i]) + num2) % 27;
		msgOutput[i] = answer;
	}
	
	printf("Message output in numbers: ");
	for(int i = 0; i < length - 1; i++) {
		printf("%d ", msgOutput[i]);
	}
	printf("\n");

	return msgOutput;
}

char* bufferEncrypt(int* msgInput, int prime, int size) {
	srand(time(NULL));
	
	printf("Size: %d\n", size);	
	
	int sizeOfOutput = size;
	for (int i = 0; i < size; i++) {
		sizeOfOutput += i % prime + 1;
	}
	printf("sizeOfOutput: %d\n", sizeOfOutput);
	
	int randomInt;
	int msgOutput[sizeOfOutput];
	printf("Buffer test: ");
	int j = 0;
	for(int i = 0; i < size; i++) {
		msgOutput[j] = msgInput[i];
		printf("%d ", msgOutput[j]);
		for(int k = 0; k < i % prime + 1; k++) {
			j++;
			randomInt = rand() % 27;
			msgOutput[j] = randomInt;
			printf("%d ", msgOutput[j]);
		}
		j++;
	}
	printf("\n");

	char* charOutput = (char*)malloc(sizeOfOutput + 1);	
	if(charOutput == NULL) {
		printf("Memory allocation for charOut failed\n");
		return NULL;
	}
	charOutput[sizeOfOutput] = '\0';

	printf("Buffer Encryption with letters: ");
	for(int i = 0; i < sizeOfOutput; i++) {
		charOutput[i] = intToChar(msgOutput[i]);
	}
	printf("%s\n", charOutput);

	return charOutput;
}

char* shiftEncrypt(char* inputMsg, int prime) {

	int size = strlen(inputMsg);
	printf("Size: %d\n",size);
	char* charOutput = (char*)malloc(size + 1);	
	if(charOutput == NULL) {
		printf("Memory allocation for charOut failed\n");
		return NULL;
	}
	
	for(int i = 0; i < size; i++) {
		charOutput[i] = inputMsg[i] + prime;
	}
	charOutput[size] = '\0';
	printf("Shift Encryption output: %s\n", charOutput);

	return charOutput;
}

char* primeDecrypt(int* msgInput, int prime, int num2) {
	
	int size = msgInput[0];
	printf("size: %d\n", size);

	printf("reset msgInput test: ");
	for(int i = 0; i < size; i++) {
		msgInput[i] = msgInput[i + 1];
		printf("%d ", msgInput[i]);
	}
	printf("\n");

	int* counter = (int*)malloc(sizeof(int));
	*counter = 0;
	int rPrime = Euclidean(prime, 27, counter);
	if (*counter % 2 == 1) {
		rPrime = 27 - rPrime;
	}
	
		
	printf("Prime decrypt test: ");
	for(int i = 0; i < size; i++) {
		msgInput[i] = 27 + ((rPrime * (msgInput[i] - num2)) % 27);
		printf("%d ", msgInput[i]);
	}
	printf("\n");
		
	char* charOutput = (char*)malloc(size + 1);	
	if(charOutput == NULL) {
		printf("Memory allocation for charOut failed\n");
		return NULL;
	}
	
	for(int i = 0; i < size; i++) {
		charOutput[i] = intToChar((msgInput[i] % 27));
	}
	charOutput[size] = '\0';
	printf("Shift Decryption output: %s\n", charOutput);

	free(counter);	
	return charOutput;
}

int* bufferDecrypt(char* msgInput, int prime, int size) {
	
	int sizeOfOutput = 0;
	int j = 1;
	printf("size: %d\n", size);
	printf("Checking SizeOfOutput: ");
	for(int i = 0; j < size; i++) {
		j += i % prime + 2;
		sizeOfOutput++;
		printf("%d ", j);
	}
	printf("\n");
	printf("sizeOfOutput: %d\n", sizeOfOutput);

	int msgNum[size];
	for(int i = 0; i < size; i++) {
		msgNum[i] = charToInt(msgInput[i]);
	}

	int *msgOutput = (int*)malloc(sizeOfOutput * sizeof(int) + 1);
	if(msgOutput == NULL) {
		printf("Memory allocation for msgOut failed\n");
		return NULL;
	}

	j = 0;
	msgOutput[0] = sizeOfOutput;	
	printf("Buffer decrypt: ");
	for( int i = 0; j < size - 1; i++) {
		msgOutput[i + 1] = msgNum[j];
		j += i % prime + 2;
		printf("%d ", msgOutput[i + 1]);
	}
	printf("\n");
	
	return msgOutput;
}

char* shiftDecrypt(char* inputMsg, int prime) {
	
	int size = strlen(inputMsg);
	char* charOutput = (char*)malloc(size + 1);
	if(charOutput == NULL) {
		printf("Memory allocation for charOut failed\n");
		return NULL;
	}
	
	for(int i = 0; i < size; i++) {
		charOutput[i] = inputMsg[i] - prime;
	}
	charOutput[size] = '\0';
	printf("Shift Decryption output: %s\n", charOutput);
	
	return charOutput;
}

int genKey() {
	srand(time(NULL));
	int key1 = rand() % 27;
	while (!relativelyPrime(key1, 27)) {
		key1 = rand() % 27;
	}
	int key2 = rand() % 1000;
	printf("Your key is: %d %d\n", key1, key2);
	return 1;
}

int main(int argc, char *argv[]) {

	if (argc != 5) {
		printf("Usage: %s [-flag] [filepath] [num1] [num2]\n", argv[0]);
		return 1;
	}

	char *flag = argv[1];
	printf("Flag provided: %s\n", flag);

	char *filepath = argv[2];
	printf("Filepath provided: %s\n", filepath);

	int rPrime = atoi(argv[3]);
	int ranNum = atoi(argv[4]);
	
	FILE *inputFile = fopen(filepath, "r");
	if (inputFile == NULL) {
		printf("Error: Unable to open file '%s'\n", filepath);
		return 1;
	}

	fseek(inputFile, 0, SEEK_END);
	long file_size = ftell(inputFile);
	fseek(inputFile, 0, SEEK_SET);

	char *inMsg = (char *)malloc(file_size + 1);
	if (inMsg == NULL) {
		printf("Error: Memory allocation failed\n");
		fclose(inputFile);
		return 1;
	}

	char *outMsg;
	size_t bytes_read = fread(inMsg, 1, file_size, inputFile);
	if (bytes_read != file_size) {
		printf("Error: Failed to read the entire file\n");
		fclose(inputFile);
		free(inMsg);
		return 1;
	}

	inMsg[file_size] = '\0';
	fclose(inputFile);
	
	int* numCode;
	char* charCode;
	switch (flag[0]) {
		case '-':
			switch (flag[1]) {
				case 'e':
					numCode = primeEncrypt(inMsg, rPrime, ranNum);
					charCode = bufferEncrypt(numCode, rPrime, strlen(inMsg) - 1);
					outMsg = shiftEncrypt(charCode, rPrime);
					break;
				case 'd':
					printf("Decrypt selected\n");
					charCode = shiftDecrypt(inMsg, rPrime);
					int* numCode = bufferDecrypt(charCode, rPrime, strlen(inMsg));
					outMsg = primeDecrypt(numCode, rPrime, ranNum);
					break;
				case 'g':
					printf("Generate key selected\n");
					genKey();
					return 0;
				default:
					printf("Not an available flag.\n");
					return 1;
			}
			break;
		default:
			printf("Invalid flag. Proper format for a flag is [-flag].\n");
			return 1;
	}
	free(charCode);
	free(numCode);

	FILE *outputFile = fopen("decrypted.txt", "w");
	if (outputFile == NULL) {
		printf("Error: Unable to create output file 'decrypted.txt'\n");
		free(inMsg);
		//free(outMsg);
		return 1;
	}

	printf("File contents: %s\n", outMsg);

	fprintf(outputFile, "%s\n", outMsg);

	fclose(outputFile);

	printf("File copied successfully from '%s' to 'decrypted.txt'\n", filepath);
	free(inMsg);
	free(outMsg);

	return 0;
}
