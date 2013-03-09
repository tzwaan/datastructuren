/*
 * File: opgave2.c
 *
 * Decriptie programma dat een verschuiving in text kan
 * terugzetten mits er een frequentietabel wordt meegegeven
 *
 * auteur: Tijmen Zwaan
 * UvA-id: 10208917
 */


#include <stdio.h>
#include <stdlib.h>

double freqtable[26];

void printtext(char *array, int counter){
   for(int i = 0; i<counter; i++){
      printf("%c", array[i]);
   }
   printf("\n");
}

void input_to_freqtable(char *letters, double *freq){
   for(int i=0; i<26; i++){
      freqtable[letters[i]-97] = freq[i];
   }
}

void printfreqtable(double *table){
   for(int i=0; i<26; i++){
      printf("%c = %2.3f\n", i+97, table[i]);
   }
}

void printfreqtable2(int *table){
   for(int i=0; i<26; i++){
      printf("%c = %d\n", i+97, table[i]);
   }
}

int main(int argc, char *argv[]){
   int i, j, counter=0, temp[26]={0}, dinges=0;
   char letters[26];
   double freq[26], text_freqtable[26], deviation[26]={0.0};
   FILE *freqpointer;
   FILE *scrambled_counter;
   FILE *scrambled_read;


   printf("\nbericht: %s\nfrequentietabel: %s\n", argv[1], argv[2]);
   if((freqpointer = fopen(argv[2], "r")) == NULL){
      perror("fopen");
      exit(0);
   }
   if((scrambled_counter = fopen(argv[1], "r")) &&
      (scrambled_read    = fopen(argv[1], "r")) == NULL){
      perror("fopen");
      exit(0);
   }

   while(fgetc(scrambled_counter) != EOF) {counter++;}
   printf("number of characters=%d\n",counter);
   char scrambled_text[counter];

   for(i=0; i<counter; i++){
      scrambled_text[i] = fgetc(scrambled_read);
      if(scrambled_text[i] !=32){
         temp[scrambled_text[i]-97]++;
      }
   }

   for(i=0;i<26;i++){
      text_freqtable[i]=(((double)temp[i]/(double)counter)*100);
   }

   for(i=0; i<26; i++){
      fscanf(freqpointer, "%c %lf\n", &letters[i], &freq[i]);
   }

   input_to_freqtable(letters, freq);

   printf("\nthe encrypted text:\n");
   printtext(scrambled_text, counter);
   printf("\n\ndutch frequency table:\n");
   printfreqtable(freqtable);
   printf("\n\nfrequency table of the current text:\n");
   printfreqtable(text_freqtable);

   for(i=0;i<26;i++){
      for(j=0;j<26;j++){
         if(freqtable[i]-text_freqtable[(i+j) % 26] > 0){
            deviation[j] += freqtable[i]-text_freqtable[(i+j) % 26];
         }
         if(freqtable[i]-text_freqtable[(i+j) % 26] <= 0){
            deviation[j] -= freqtable[i]-text_freqtable[(i+j) % 26];
         }
      }
   }

   for(i=0;i<26;i++){
      if(deviation[dinges] > deviation[i]){
         dinges=(i);
      }
   }

   dinges = 26 - dinges;
   for(i=0;i<counter;i++){
      if(scrambled_text[i] != 32){
         scrambled_text[i] = ((scrambled_text[i] - 97 + dinges) % 26) + 97;
      }
   }

   printf("\n\ndecrypted text:\n");
   printtext(scrambled_text, counter);

}
