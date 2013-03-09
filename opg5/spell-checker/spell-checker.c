#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>

#include "hash.h"

#define BUF_SIZE 256

/* TEXT_SIZE is the maximum size of the input text. */
#define TEXT_SIZE  (6 * 1024 * 1024)

/* Word seperators */
#define DELIM " ,.:;\"-_(){}[]?!*^&'\n\t"

/* Helper functions. */
/* Print elapsed time in seconds. */
void print_elapsed_clock(clock_t start, clock_t stop) {
        printf("seconds:               %f\n",
                (float)(stop - start)/CLOCKS_PER_SEC);
}

/* Checks is word contains digits. So it can be ignored for spell
 * checking. */
int contains_numbers(char *word) {
    while ( *word && !isdigit(*word) ) {
        word++;
    }
    return *word != '\0';
}

/* Convert a string to lowercase. */
void convert_to_lower(char *dest, char *src) {
    for (; *src; ++src)
        *dest++ = tolower(*src);
    *dest = '\0';
}


int main(int argc, char *argv[]) {
    unsigned int table_size;
    int bytes_read, count, typo, length;
    FILE *wordfile, *textfile;
    char *buf, *copy, *textbuffer, *word, *lowercase;
    hash_t *table;

    /* Shared token to store for every word in the hash table. */
    void *placeholder = malloc(1);
    * (char *) placeholder = 'a';

    if ( !(argc == 4 ) ) {
        printf("Usage: %s <wordfile> <text> <size>\n", argv[0]);
        exit (EXIT_FAILURE);
    }
    table_size = atoi(argv[3]);
    printf("Selected table size: %d\n", table_size);

    // Setup input files wordlist file and textfile to check.
    wordfile = fopen (argv[1], "r");
    if (!wordfile) {
        perror("Cannot open wordfile");
        exit (EXIT_FAILURE);
    }
    textfile = fopen (argv[2], "r");
    if (!textfile) {
        perror("Cannot open textfile");
        exit (EXIT_FAILURE);
    }

    table = hash_table_new(table_size);

    /* Read wordfile, and insert every word into the hash table. */
    buf = malloc(BUF_SIZE);
    while ( fgets(buf, BUF_SIZE, wordfile) ) {
        length = strlen(buf);
        buf[length - 1] = '\0'; // cut-off newline
        copy = malloc (length + 1); // add space for \0
        convert_to_lower(copy, buf);
        hash_table_insert(table, copy, placeholder);
    }
    fclose(wordfile);
    printf("Hash table contains %d words\n", hash_table_fill(table));
    printf("Hash table load factor %f\n",
            (double)hash_table_fill(table)/hash_table_size(table));


    // Read text file, and lookup every word in the hash table.
    textbuffer = malloc (TEXT_SIZE); // fixed max size
    assert (textbuffer);
    bytes_read = fread (textbuffer, 1, TEXT_SIZE, textfile);
    printf("bytes read %d\n", bytes_read);

    word = strtok (textbuffer, DELIM); // prime strtok with textbuffer
    count = typo = 0;
    lowercase = malloc (BUF_SIZE); // temporary buffer for lowercase word
    do {
        convert_to_lower(lowercase, word);
        /* Don't lookup words with numbers in them. */
        if (!contains_numbers(lowercase) &&
                !hash_table_lookup(table, lowercase)) {
            /* No printing when measuring execution time. */
            //printf("Not found: [%s]\n", lowercase);
            typo++;
        }
        count++;
    } while ( (word = strtok( NULL, DELIM)) );
    fclose(textfile);

    printf("words read %d\n", count);
    printf("typo's %d\n", typo);

    /* Cleanup. */
    hash_table_destroy (table);
    free (buf);
    free (textbuffer);
    free (placeholder);


    return 0;
}
