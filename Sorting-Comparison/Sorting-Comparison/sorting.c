//
//  sorting.c
//  ece368_P1
//
//  Created by Jack on 2019/9/15.
//  Copyright © 2019 Jack. All rights reserved.
//

#include "sorting.h"
#include <math.h>

long *Load_File(char *Filename, int *Size){
    FILE *pFile;
    pFile = fopen(Filename, "r");
    fscanf(pFile, "%d", Size);
    long * LongFileArr = (long *)malloc(sizeof(long) * ((long)*Size-1));
    for(long i = 0; i < *Size; i++){
        fscanf(pFile, "%lu", &LongFileArr[i]);
    }
    fclose(pFile);
    return LongFileArr;
    //free LongFileArr malloc
}

int Save_File(char *Filename, long *Array, int Size){
    FILE *fp;

    fp = fopen(Filename,"w");
    for(int n = 0; n < Size; n++) {
        fprintf(fp,"%ld\n", Array[n]);
    }
    fclose(fp);
    return Size;
}

void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move){
    //Produce 2p3q sequence and store in gapNum
    double NumComp = 0;
    double NumMov = 0;
    long BiggestNum = 0;
    for(int i = 0; i < Size; i++){
        NumComp++;
        if(Array[i] > BiggestNum){
            BiggestNum = Array[i];
        }
    }
    //************Generate seqeunce*************//
    long res[Size];
    res[0] = 1;
    int p2 = 0;
    int p3 = 0;
    int i = 1;
    int ArrLen = 0;;
    for(i = 1; i < 1000; i++){
        int trigger = 0;
        if (res[p2] * 2 == res[i - 1])
            p2 += 1;
        if (res[p3] * 3 == res[i - 1])
            p3 += 1;
        long u2 = res[p2] * 2;
        long u3 = res[p3] * 3;
        if (u2 < u3){
            p2 += 1;
            if(u2 >= BiggestNum)
                trigger = 1;
            else
                res[i] = u2;
        }
        else{
            p3 += 1;
            if(u3 >= BiggestNum)
                trigger = 1;
            else
                res[i] = u3;
        }
        if(trigger == 1) {
            ArrLen = i;
            break;
        }
    }
    long finalSeq[ArrLen];
    for(int i = 0; i < ArrLen; i++){
        finalSeq[i] = res[i];
    }
    //************Generate seqeunce*************//
    
    //************Shell Sort*************//
    int ArrLenTemp = ArrLen-1;
    
    for (long gap = finalSeq[ArrLenTemp]; ArrLenTemp >= 0; gap = finalSeq[--ArrLenTemp])
    {
        for (long i = gap; i < Size; i += 1)
        {
            long temp = Array[i];
            NumMov++;
            long j = i;
            NumComp++;
            for (j = i; j >= gap && Array[j - gap] > temp; j -= gap){
                Array[j] = Array[j - gap];
                NumMov++;
                NumComp++;
            }
            Array[j] = temp;
            NumMov++;
        }
    }
    
    *N_Comp = NumComp;
    *N_Move = NumMov;
    //************Shell Sort*************//
}
void Improved_Bubble_Sort(long *Array, int Size, double *N_Comp, double *N_Move){
    
//    {N1=N/1.3, N2=N1/1.3, N3=N2/1.3, …, 1}, where N is the size of the array to be sorted. In other words, the next value in the gap sequence is the floor value of the previous integer gap divided by 1.3. However, if any value in this sequence becomes 9 or 10, it is replaced by a value of 11. We shall refer to this sequence as Seq2. Note that since the gap value has to be an integer, you will need to take the floor of the gap value computed above.
    double NumComp = 0;
    double NumMov = 0;
    //************Generate seqeunce*************//
    double Seq2[1000];
    int Seq2Size = 0;
    double TempSize = Size;
    for(int i = 0; i < 1000; i++){
        Seq2[i] = floor(TempSize/1.3);
        if(Seq2[i] == 9 || Seq2[i] == 10){
            Seq2[i] = 11;
        }
        if(Seq2[i] == 1){
            Seq2Size = i+1;
            break;
        }
        TempSize = floor(TempSize/1.3);
    }
    double finalSeq2[Seq2Size];
    for(int i = 0; i < Seq2Size; i++){
        finalSeq2[i] = Seq2[i];
    }
    //************Bubble Sort*************//
    for (long k = 0; k < Seq2Size; k++)
    {
        long gap = finalSeq2[k];
        for (long i = gap; i < Size; i += 1)
        {
            NumComp++;
            for (long j = i; j >= gap && Array[j - gap] > Array[j]; j -= gap){
                long temp = Array[j];
                Array[j] = Array[j - gap];
                Array[j - gap] = temp;
                NumMov++;
                NumComp++;
            }
        }
    }
    *N_Comp = NumComp;
    *N_Move = NumMov;
    //************Bubble Sort*************//
    
}

void Save_Seq1 (char *Filename, int N){
    long res[1000];
    res[0] = 1;
    int p2 = 0;
    int p3 = 0;
    int i = 1;
    int ArrLen = 0;;
    for(i = 1; i < 1000; i++){
        int trigger = 0;
        if (res[p2] * 2 == res[i - 1])
            p2 += 1;
        if (res[p3] * 3 == res[i - 1])
            p3 += 1;
        long u2 = res[p2] * 2;
        long u3 = res[p3] * 3;
        if (u2 < u3){
            p2 += 1;
            if(u2 >= N)
                trigger = 1;
            else
                res[i] = u2;
        }
        else{
            p3 += 1;
            if(u3 >= N)
                trigger = 1;
            else
                res[i] = u3;
        }
        if(trigger == 1) {
            ArrLen = i;
            break;
        }
    }
    long finalSeq[ArrLen];
    for(int i = 0; i < ArrLen; i++){
        finalSeq[i] = res[i];
    }
    
    FILE *fp;
    
    fp = fopen(Filename,"w");
    for(int n = 0; n < ArrLen; n++) {
        fprintf(fp,"%ld\n",finalSeq[n]);
    }
    fclose(fp);
}

void Save_Seq2 (char *Filename, int N){
    double Seq2[1000];
    int Seq2Size = 0;
    double TempSize = N;
    for(int i = 0; i < 1000; i++){
        Seq2[i] = floor(TempSize/1.3);
        if(Seq2[i] == 9 || Seq2[i] == 10){
            Seq2[i] = 11;
        }
        if(Seq2[i] == 1){
            Seq2Size = i+1;
            break;
        }
        TempSize = floor(TempSize/1.3);
    }
    double finalSeq2[Seq2Size];
    for(int i = 0; i < Seq2Size; i++){
        finalSeq2[i] = Seq2[i];
    }
    
    FILE *fp;
    
    fp = fopen(Filename,"w");
    for(int n = Seq2Size-1; n >= 0; n--) {
        fprintf(fp,"%.0f\n",finalSeq2[n]);
    }
    fclose(fp);
}


//Users//jack//Desktop//ece368_P1//ece368_P1//1000.txt
//Users//jack//Desktop//ece368_P1//ece368_P1//shell1000.txt
//Users//jack//Desktop//ece368_P1//ece368_P1//bubble1000.txt

//Users//jack//Desktop//ece368_P1//ece368_P1//10000.txt
//Users//jack//Desktop//ece368_P1//ece368_P1//shell10000.txt
//Users//jack//Desktop//ece368_P1//ece368_P1//bubble10000.txt

//Users//jack//Desktop//ece368_P1//ece368_P1//100000.txt
//Users//jack//Desktop//ece368_P1//ece368_P1//shell100000.txt
//Users//jack//Desktop//ece368_P1//ece368_P1//bubble100000.txt

//Users//jack//Desktop//ece368_P1//ece368_P1//1000000.txt
//Users//jack//Desktop//ece368_P1//ece368_P1//shell1000000.txt
//Users//jack//Desktop//ece368_P1//ece368_P1//bubble1000000.txt
