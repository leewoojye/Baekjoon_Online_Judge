#include <stdio.h>

#define SIZE 8 

void Merge(int a[], int b[], int c[], int length); 
void PrintArray(int a[], int length) { 
    int i; 
    for (i = 0; i < length; i++) printf("%d ", a[i]); 
    printf("\n"); 
} 

int main() { 
    int a[SIZE] = {5, 3, 6, 1, 7, 2, 0, 4}, b[SIZE]; 
    PrintArray(a, SIZE); 
    
    // length 1 --> 2 
    Merge(b + 0, a + 0, a + 1, 1); 
    Merge(b + 2, a + 2, a + 3, 1); 
    Merge(b + 4, a + 4, a + 5, 1); 
    Merge(b + 6, a + 6, a + 7, 1); // 원본 코드 에 누락된 부분
    PrintArray(b, SIZE); 
    
    // length 2 --> 4 
    Merge(a + 0, b + 0, b + 2, 2); 
    Merge(a + 4, b + 4, b + 6, 2); // 원본 코드 에 누락된 부분
    PrintArray(a, SIZE); 
    
    // length 4 --> 8 
    Merge(b + 0, a + 0, a + 4, 4); 
    PrintArray(b, SIZE); 
    
    return 0; 
} 

void Merge(int a[], int b[], int c[], int length) { // Merge two sorted lists 
    int i, j, k; 
    for (i = j = k = 0; i < 2 * length; i++) { 
        if (j == length) 
            a[i] = c[k++]; 
        else if (k == length) 
            a[i] = b[j++]; // 빈 칸 채우기
        else if (b[j] > c[k]) // 내림차순 (descending) 
            a[i] = b[j++]; 
        else 
            a[i] = c[k++]; 
    } 
}