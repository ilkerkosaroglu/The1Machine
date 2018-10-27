#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct sequence{
  char* numbers;
  char* yedek;
  int length;
};

struct sequence generate(){

  char* seq;
  char* seq2;
  int elementno, i, random,k;
  struct sequence x;
  elementno = (rand() % 10) + 25;
  seq = (char*)malloc(sizeof(char)*(elementno)+1);
  memset(seq, 0, sizeof(char)*(elementno));
  seq2 = (char*)malloc(sizeof(char)*(elementno)+1);
  memset(seq2, 0, sizeof(char)*(elementno));
  for(i = 0; i < elementno; i++){
    if(elementno - i <= rand()%4 ){
      seq[i] = 0;
      break;
    }
    seq[i] = rand() % 49 + 1;
    random = rand() % 10;
    if(random < 9 && i > 20){
      seq[i] %= 16;
    }
    else if(random < 9){
      seq[i] = (seq[i] % 15) + 1;
    }
  }
  for (k=0;k<elementno;k++){
    seq2[k]=seq[k];
  }
  x.numbers = seq;
  x.yedek   = seq2;
  x.length  = elementno;
  return x;
}
int solve(char* seq){
  int r1 = 0, r2 = 0;
  int i = 0;
  int a = 0, b = 0, length;
  for(r1 = 0, r2 = 0, i = 0; seq[i] < 17; b++){
    if(b > 50){
      //printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nThis is cycle %d. Possible loop or just bad numbers.\n", b);
      goto git;
    }
    //printf("CYCLE %d\n", b+1);
    if (seq[i]<0) {break;}
    if (r1<-127 || r1>127){break;}
    if (r2<-127 || r2>127){break;}
    switch(seq[i]){
      case 0: goto git;
      case 1: r1 = seq[i+1]; i += 2;  break;
      case 2: r2 = seq[i+1]; i += 2;  break;
      case 3: r1 = seq[seq[i+1]]; if(seq[i+1]>length||seq[i+1]<0){goto git;} i += 2;  break;
      case 4: r2 = seq[seq[i+1]]; if(seq[i+1]>length||seq[i+1]<0){goto git;} i += 2;  break;
      case 5: r1 = r2; i+=1; break;
      case 6: r1 = seq[r2]; i+=1; break;
      case 7: seq[r1] = r2;       if(seq[r1]>127||seq[r1]<-127){b=80;goto git;} i += 1; break;
      case 8: seq[seq[i+1]] = r1; if(seq[seq[i+1]]>127||seq[seq[i+1]]<-127){b=80;goto git;} i += 2; break;
      case 9: i = seq[i+1];  break;
      case 10: if(r1 == 0){ i += 2; } else{ i = seq[i+1]; }  break;
      case 11: r1 = r1 + r2; i += 1;  break;
      case 12: r1 = r1 - r2; i += 1;  break;
      case 13: r1 = r1 * r2; i += 1;  break;
      case 14: if (r2==0){b=0;goto git;} r1 = r1/r2 ; i += 1;  break;
      case 15: r1 *= -1; i += 1;  break;
      case 16: if(r1 == r2){ r1 = 0; } else if(r1 > r2){ r1 = 1; } else{ r1 = -1; } i += 1;  break;
      default: goto git;
    }
  }
  //printf("Out of boundaries! Halt..\n");
  b=80;
  git:
  //printf("%d ",b);
  return b;
}
