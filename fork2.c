#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void ascending_sort(int arr[], int n) {
  int i, j;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }
}

void descending_sort(int arr[], int n) {
  int i, j;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (arr[j] < arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }
}

int main() {
  int pid, i = 0, n;
  int *arr;
  int p;
  printf("Enter the number of integers: ");
  if (scanf("%d", &n) != 1) {
    printf("Invalid input for number of integers.\n");
    return 1;
  }

  arr = (int *)malloc(n * sizeof(int));
  printf("Enter the integers: ");
  for (i = 0; i < n; i++) {
    if (scanf("%d", &arr[i]) != 1) {
      printf("Invalid input at index %d.\n", i);
      return 1;
    }
  }
  printf("Hello, my PID is %d and my Parent PID is %d\n", getpid(), getppid());

  p = fork();
  printf("\nfork Started\n");
  if (p < 0) {
    printf("Error, failed to fork.\n");
    exit(1);
  } else if (p == 0) {
    // Child process
    descending_sort(arr, n);
    for (i = 0; i < n; i++) {
      printf("\t\t i=%d , arr[i]=%d, p=%d, pid=%d, ppid=%d \n", i, arr[i], p, getpid(), getppid());
      sleep(1);
    }
    printf("\n");
    printf("Child Process completed\n");
  } else {
    // Parent process
    ascending_sort(arr, n);
    printf("PID:%d, PPID:%d\n", getpid(), getppid());
  
    for (i = 0; i < n; i++) {
      printf("i=%d arr[i]=%d, p=%d, pid=%d, ppid=%d \n", i, arr[i], p, getpid(),getppid());
      sleep(5);
    }
  }

  printf("Bye. I am the parent. My PID is %d and Parent PID is: %d\n", getpid(),
         getppid());
  return 0;
}


//--------------------------------------------------------------------------------------------------------------------
// #include<stdio.h>
// #include<stdlib.h>
// #include<sys/wait.h>
// #include<unistd.h>

// void swap(int *a,int *b){
//   int temp=*a;
//   *a=*b;
//   *b=temp;
// }

// void ascending_sort(int arr[],int n){
//   int i,j;
//   for(i=0;i<n-1;i++){
//     for(j=0;j<n-i-1;j++){
//       if(arr[j]>arr[j+1])
//         swap(&arr[j],&arr[j+1]);
//     }
//   }
// }
// void decending_sort(int arr[],int n){
//   int i,j;
//   for(i=0;i<n-1;i++){
//     for(j=0;j<n-i-1;j++){
//       if(arr[j]<arr[j+1])
//         swap(&arr[j],&arr[j+1]);
//     }
//   }
// }

// int main(){
//   int p,pid,n,i=0;
//   int *arr;

//   printf("\nEnter the Integer :\n");
//   scanf("%d",&n);

//   arr=(int *)malloc(n*sizeof(int ));
//   printf("\nEnter the integers : ");
//   for(i=0;i<n;i++){
//     scanf("%d",&arr[i]);
//   }
//   printf("\nHello , My pid is %d and my parent id is %d",getpid(),getppid());

//   p=fork();
//   printf("\nFork Started");

//   if(p<0){
//     printf("\nError , Failed to fork ");
//     exit(1);

//   }else if(p==0 ){
//     decending_sort(arr,n);
//     for(i=0;i<n;i++){
//     printf("\n\t\t\ti=%d,arr[i]=%d,p=%d,pid=%d,ppid=%d",i,arr[i],p,getpid(),getppid());
//     sleep(1);
//     }

//     printf("\nChild process completed ..");

//   }else {
//     ascending_sort(arr,n);
//      printf("\nPID:%d, PPID:%d\n", getpid(), getppid());
//     for(i=0;i<n;i++){
//       printf("\ni=%d,arr[i]=%d,p=%d,pid=%d,ppid=%d",i,arr[i],p,getpid(),getppid());
//       sleep(5);
//     }
//     printf("\nParent process completed ..");
//   }


//   printf("\nBye ,I am parent and My pid =%d and ppid=%d\n",getpid(),getppid());


// return 0;


// }