#include <stdio.h>
#include <stdlib.h>
#include "generate.c"

int main(){
  time_t t;
  srand((unsigned) time(&t));
  int r1 = 0, r2 = 0;
  int i = 0,k,sizeSequence;
  int a = 0, b = 0, length,steps;
  /*char seq[26] = {9, 6, 12, 27, 39, 99, 3, 2, 4, 3, 11, 4, 4, 16, 10, 20, 2, 1, 9, 22, 2, 0, 1, 5, 7, 0};*/
  int* seq;
  printf("The size of the sequence:");
  scanf("%d",&sizeSequence);
  seq = (int*)malloc(sizeof(char)*(sizeSequence)+1);
  memset(seq, 0, sizeof(char)*(sizeSequence));
  printf("Enter each number in the sequence:\n" );
  for(k=0;k<sizeSequence;k++){
    scanf("%d",&seq[k] );
  }
  basa:
  length=sizeSequence;

  printf("\n-----\n");
  printf("The initial sequence is:\n");
  for(a = 0; a < length; a++){
    printf("%3d|", seq[a]);
  }
  printf("\n");
  for(a = 0; a < length; a++){
    printf("%3d.", a);
  }
  printf("\n-----\n");
  printf("\nPress ENTER to start solving step by step.\n");
  getchar();
  printf("\n");
  for(r1 = 0, r2 = 0, i = 0; seq[i] < 17; b++){
    if(b == 50){
      printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nThis is cycle %d. Possible loop or just bad numbers.\n", b);
    }
    if (seq[i]<0) {b=0;break;}
    if (r1<-127 || r1>127){r1=52;break;}
    if (r2<-127 || r2>127){r1=52;break;}
    printf("CYCLE %d, I=%d\n", b+1,i);
    switch(seq[i]){
      case 0: printf("Instruction 0. Halt the process.\n"); goto git;
      case 1: r1 = seq[i+1]; i += 2; printf("Instruction 1. Load R1 with the next number in the sequence. R1 <- [I+1],I <- I+2\n"); break;
      case 2: r2 = seq[i+1]; i += 2; printf("Instruction 2. Load R2 with the next number in the sequence. R2 <- [I+1],I <- I+2\n"); break;
      case 3: r1 = seq[seq[i+1]];  if(seq[i+1]>length||seq[i+1]<0){printf("Out of boundaries! Halt!\n");goto git;}i += 2;printf("Instruction 3. Load R1 with the sequence element which is at the position given as the next number in the sequence. R1 <- [[I+1]], I <- I+2\n"); break;
      case 4: r2 = seq[seq[i+1]];  if(seq[i+1]>length||seq[i+1]<0){printf("Out of boundaries! Halt!\n");goto git;}i += 2;printf("Instruction 4. Load R2 with the sequence element which is at the position given as the next number in the sequence. R2 <- [[I+1]], I <- I+2\n"); break;
      case 5: r1 = r2; i+=1; printf("Instruction 5. Load R1 with the content of R2. R1 <- R2 ,I <- I+1\n"); break;
      case 6: r1 = seq[r2]; i+=1; printf("Instruction 6. Load R1 with the sequence element which is at the position R2. R1 <- [R2], I <- I+1\n"); break;
      case 7: seq[r1] = r2;       if(seq[r1]>127||seq[r1]<-127){printf("Out of boundaries! Halt!\n");goto git;} i += 1; printf("Instruction 7. Change the sequence element which is at the position R1 to be the content of R2. [R1] <- R2, I <- I+1\n"); break;
      case 8: seq[seq[i+1]] = r1; if(seq[seq[i+1]]>127||seq[seq[i+1]]<-127){printf("Out of boundaries! Halt!\n");goto git;} i += 2; printf("Instruction 8. Change the sequence element which is at the position given as the next number in the sequence to the content of R1. [[I+1]] <- R1 , I <- I+2\n"); break;
      case 9: i = seq[i+1]; printf("Instruction 9. Take the sequence element which is at the position given as the next number in the sequence as the next instruction to be performed. I <- [I+1]\n"); break;
      case 10: if(r1 == 0){ i += 2; } else{ i = seq[i+1]; } printf("Instruction 10. If R1 contains zero continue with the sequence element following the next one as the next instruction to be performed, otherwise act like the instruction 9.\n if R1 = 0 : I <- I+2\notherwise : I <- [I+1]\n"); break;
      case 11: r1 = r1 + r2; i += 1; printf("Instruction 11. Increment R1 by the content of R2. R1 <- R1+R2, I <- I+1\n"); break;
      case 12: r1 = r1 - r2; i += 1; printf("Instruction 12. Decrement R1 by the content of R2. R1 <- R1-R2, I <- I+1\n"); break;
      case 13: r1 = r1 * r2; i += 1; printf("Instruction 13. Multiply R1 by the content of R2. R1 <- R1*R2, I<- I+1\n"); break;
      case 14: if(r2 == 0){printf("Divide by 0! Halt..\n");goto git;}r1 = r1/r2 ; i += 1; printf("Instruction 14. Divide R1 by the content of R2 (integer division). R1 <- R1/R2, I <- I+1\n"); break;
      case 15: r1 *= -1; i += 1; printf("Instruction 15. Change the sign of the value in R1. R1 <- -R1, I <- I+1\n"); break;
      case 16: if(r1 == r2){ r1 = 0; } else if(r1 > r2){ r1 = 1; } else{ r1 = -1; } i += 1; printf("Instruction 16. Compare the content of R1 with the content of R2. \nIf R1 = R2 : R1 <- 0 \nelse if R1 > R2 : R1 <- 1\notherwise: R1 <- -1\nalways I <- I+1\n"); break;
      default: break;
    }
    printf("-----\nThe sequence is: \n");
    for(a = 0; a < length; a++){
      printf("%3d|", seq[a]);
    }
    printf("\n");
    for(a = 0; a < length; a++){
      printf("%3d.", a);
    }
    printf("\n\n R1:    R2:    I:\n-----  -----  -----\n|");
    printf("%3d|  |%3d|  |%3d|\n", r1, r2, i);
    printf("-----  -----  -----\nPress ENTER to continue...\n\n");
    getchar();
  }
  printf("Out of boundaries! Halt..\n\n");
  b-=1;
  git:
  printf("-----\nFINAL CYCLE is %d\nThe final sequence is: \n", b+1);
  for(a = 0; a < length; a++){
    printf("%3d|", seq[a]);
  }
  printf("\n");
  for(a = 0; a < length; a++){
    printf("%3d.", a);
  }
  printf("\nFinal R1: %d Final R2: %d Final I: %d\n\n", r1, r2, i);
  printf("Sincerely, by \n-Yigit Soylu\n-Ilker Kosaroglu\n");
  getchar();

  return 0;
}
