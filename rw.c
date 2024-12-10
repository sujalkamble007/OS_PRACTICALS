
//------------------------------------
// #include <stdio.h> 
// #include <stdlib.h> 
// #include <pthread.h> 
// #include <semaphore.h> 
// #include <unistd.h>

// #define R 3  // Updated number of readers
// #define W 2  // Updated number of writers

// int readcount; 
// int writecount; 
// //sem_t y, z; 
// pthread_mutex_t x; 
// sem_t wsem, rsem;  // mutual exclusion semaphores
// int s = 10;  // shared resource with updated initial value

// void *reader1(void *a); 
// void *writer1(void *a); 

// int main() {
//     int i, op; 
//     pthread_t thread_read[R], thread_write[W]; 
    
//     // Initialize mutex and semaphores
//     pthread_mutex_init(&x, NULL); 
//     sem_init(&wsem, 0, 1); 
//    // sem_init(&y, 0, 1); 
//     sem_init(&rsem, 0, 1); 
//     //sem_init(&z, 0, 1);

//     do { 
//         printf("Menu : 1. Readers have priority\n2. Exit\n"); 
//         scanf("%d", &op); 
        
//         switch(op) { 
//             case 1:
//                 readcount = 0; 
//                 // Create writer threads
//                 for (i = 0; i < W; i++) { 
//                     pthread_create(&thread_write[i], NULL, writer1, (void *)(intptr_t)i); 
//                 }
//                 // Create reader threads
                // for (i = 0; i < R; i++) { 
                //     pthread_create(&thread_read[i], NULL, reader1, (void *)(intptr_t)i); 
                // }
//                 // Join writer threads
//                 for (i = 0; i < W; i++) { 
//                     pthread_join(thread_write[i], NULL); 
//                 }
//                 // Join reader threads
//                 for (i = 0; i < R; i++) { 
//                     pthread_join(thread_read[i], NULL); 
//                 }
//                 break; 
            
//             case 2: 
//                 exit(1); 
//         }
//     } while (op != 3);  // Loop until option 2 is chosen
    
//     return 0;
// } 

// void *reader1(void *a) { 
//     int r = (intptr_t)a; 
//     int i = 0; 

//     while (i < 3) {  // Updated to read 3 times
//         pthread_mutex_lock(&x); 
//         readcount++; 
//         if (readcount == 1) 
//             sem_wait(&wsem);  // First reader locks the writer semaphore
//         pthread_mutex_unlock(&x); 

//         printf("\t\tReader %d is reading: %d\n", r, s); 

//         pthread_mutex_lock(&x); 
//         readcount--; 
//         if (readcount == 0) 
//             sem_post(&wsem);  // Last reader unlocks the writer semaphore
//         pthread_mutex_unlock(&x); 
        
//         sleep(rand() % 10);  // Simulate reading time
//         i++; 
//     }
    
//     return NULL;
// } 

// void *writer1(void *a) { 
//     int w = (intptr_t)a; 
//     int i = 0; 

//     while (i < 4) {  // Updated to write 4 times
//         sem_wait(&wsem);  // Writer acquires semaphore to start writing
//         s += 10;  // Modify the shared resource with updated increment value
//         printf("Writer %d is writing: %d\n", w, s); 
//         sem_post(&wsem);  // Writer releases semaphore
        
//         sleep(rand() % 10);  // Simulate writing time
//         i++; 
//     }
    
//     return NULL;
// }

//-----------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define R 3 
#define W 2

int readcount;
int writecount;
pthread_mutex_t x;
sem_t wsem,rsem;
int s=10;

void *reader(void *a);
void *writer(void *a);

int main(){ 
    int op,i;
    pthread_t thread_write[W],thread_read[R];
    pthread_mutex_init(&x,NULL);
    sem_init(&wsem,0,1);
    sem_init(&rsem,0,1);

    do{
        printf("Menu . 1.Reader has priority \n 2. Exit \n");
        scanf("%d",&op);

        switch(op){
            case 1: 
                    readcount=0;
                    for(i=0;i<W;i++){
                        pthread_create(&thread_write[i],NULL, writer ,(void*)(intptr_t)i);
                    }

                    for(i=0;i<R;i++){
                        pthread_create(&thread_read[i],NULL, reader ,(void*)(intptr_t)i);
                    }
                    for(i=0;i<W;i++){
                        pthread_join(&thread_write[i],NULL);
                    }
                    for(i=0;i<R;i++){
                        pthread_join(&thread_read[i],NULL);
                    }
                    break;
            
            case 2: exit(1);
                  
         
        }
    }while(op!=3);


    return 0;

}

void *reader(void *a){
    int r =(intptr_t)a;
    int i=0;

    while(i<3){

        pthread_mutex_lock(&x);
        readcount++;
        if(readcount==1){
            sem_wait(&wsem);
        }
        pthread_mutex_unlock(&x);

        printf("\t\t\tReader %d is Reading %d \n",r,s);

        pthread_mutex_lock(&x);
        readcount--;
        if(readcount==0)
            sem_post(&wsem);
        pthread_mutex_unlock(&x);

        sleep(rand() % 10);

        i++;
    }
    
    return NULL;
    
    }

    void *writer(void *a){
        int w=(intptr_t)a;
        int i=0;
        while(i<4){
            sem_wait(&wsem);
            s+=10;
          printf("Writer %d is Writing %d \n",w,s);
            sem_post(&wsem);


            sleep(rand() %10);
            i++;
        }



        return NULL;
    }