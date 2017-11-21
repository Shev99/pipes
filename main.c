#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(){

  int bigPipe[2], smallPipe[2];
  pipe(bigPipe);
  pipe(smallPipe);

  if (fork()==0){

    close(bigPipe[1]);
    int i;
    read(bigPipe[0],&i,sizeof(int));
    printf("Child does a switcheroo\n");
    i = i + 3087;
    close(smallPipe[0]);
    write(smallPipe[1],&i, sizeof(int));

  }
  
  else{
    
    close(bigPipe[0]);
    int i = 1234;
    printf("Parent's number is 1234\n");
    write(bigPipe[1],&i,sizeof(int));
    printf("Parent sedning number to child\n");
    close(smallPipe[1]);
    int new;
    read(smallPipe[0],&new,sizeof(int));
    printf("New number of parent is %d\n", new);
    

  }

}
