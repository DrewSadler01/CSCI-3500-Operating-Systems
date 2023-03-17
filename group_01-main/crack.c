#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <math.h>

//GRADING NOTE:

// Code segfaults if no arguments are given- always have a usage statement!

// Otherwise, code looks to be correct. Finds all test cases, and shows
// reasonable parallel speedup.

//First two extra credits successful - +4 points

//Score 99/100

int keySize;
char salt[3];
char* target;

struct threadArgs {
        int threads;
        char start;
        char end;
};

int alphabet_increment(char* word, int size, int num) {

        int alphabet = 0;
        if (num == size - 1) {
                if (word[num] == 'z') {
                        word[num] = 'a';
                        return 1;
                }

                else {
                        word[num]++;
                        return 0;
                }
        }
        alphabet = alphabet_increment(word, size, num+1);

        if (alphabet == 1 && word[num] == 'z') {
                word[num] = 'a';
                return 1;
        }
        else if (alphabet == 1) {
                word[num]++;
                return 0;
        }
}

void crack(int size, char start, char range, int threads, struct crypt_data *data) {

        char word[size];
        for (int x = 0; x < size; x++) {
                word[x] = 'a';
        }
        word[0] = start;
        int passes = (pow(26, size - 1) * range);

        for (int a = 0; a < passes; a++) {
                char* result;
                result = crypt_r(word, salt, data);
                if (result == NULL) {
                        perror("crypt() did not work.");
                        exit(-1);
                }
                else if (strcmp(result, target) == 0) {
                        printf("Password: %s\n", word);
                        exit(0);
                }
                else {
                        alphabet_increment(word, size, 0);
                }
        }
}

void* entry(void* args) {

        struct threadArgs* ptr = (struct threadArgs*) args;
        struct crypt_data data;
        char start = ptr -> start;
        char end = ptr -> end;
        int threads = ptr -> threads;
        int range = end-start + 1;
        for (int j = 1; j <= keySize; j++) {
                crack(j, start, range, threads, &data);
        }
}

int main( int argc, char* argv[] ) {
        int threads = atoi(argv[1]);
        keySize = atoi(argv[2]);
        target = argv[3];
        if (argc != 4 ) {
                printf("Usage: <threads> <keysize> <target> \n");
                return -1;
        }
        
        if (keySize > 8 || keySize < 1) {
                printf("keysize must be between 0 and 8.\n");
                return -1;
        }
        
        for (int k = 0; k < 2; k++) {
                salt[k] = target[k];
        }
        salt[2] = '\0';
        char password[strlen(target) - 2];
        int m = 0;

        for (int l = 2; l < strlen(target); l++) {
                password[m] = target[l];
                m++;
        }
        password[m] = '\0';
        pthread_t tid[threads];
        struct threadArgs args[threads];
        int divisor = 27 / threads;
        args[0].start = 'a';

        for (int n = 0; n < threads; n++) {

                args[n].start = 'a' + divisor * n;

                if(n == threads - 1) {
                        args[n].end = 'z';
                }
                else {
                        args[n].end = 'a' + divisor * (n+1) - 1;
                }

                args[n].threads = n;
        }

        for (int m = 0; m < threads; m++ ) {
                pthread_create(&tid[m], NULL, entry, &args[m]);
        }

        for (int j = 0; j < threads; j++ ) {
                pthread_join(tid[j], NULL);
        }
        printf("Password was not found.\n");
        return 0;
}
