
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>


int RQ(int);
void RL(int);
void run();
void astk();
int read_file(char* fileName, int* maximum);
int safetyAlgorithm(int, int* request);
#define NUM_OF_RES 4 //columns
#define NUM_OF_CUST 5 //rows
int request[NUM_OF_RES];
int release[NUM_OF_RES]; 
int available[4]; //available amount of each resource
int maximum[NUM_OF_CUST][NUM_OF_RES]; //max demand of each customer
int allocation[NUM_OF_CUST][NUM_OF_RES];//amount allocated to each customer
int need[NUM_OF_RES]; //need for each customer

int main(int argc, char* argv[]){
    int a,b,c,d;
    char command[4];
    int customer_number;
    int i;


    if(argc>0){

        int index=0;
        
        for(i=1; i < argc; i++){
            available[index] = atoi(argv[i]);
            index++;
        }

    }else{
        printf("you need to enter an arugment\n");
    }


    //READ FILE
    char* fileName = "sample.txt";
    

    int result = read_file(fileName,maximum[0]);
    printf("READ: %d\n\n", result);

    scanf("%s %d %d %d %d %d", command, &customer_number, &a,&b,&c,&d);
    
    printf("\n");
    printf("\n");
   
    if( strcmp(command, "RQ" ) == 0){  //HANDLE RQ 

        request[0]=a;
        request[1]=b;
        request[2]=c;
        request[3]=d;

        RQ(customer_number);

    }else if( strcmp(command,"*")==0 ){

        asterisk();

    }else if( strcmp(command, "RL" )==0 ){ //HANDLE Rl

        release[0]=a;
        release[1]=b;
        release[2]=c;
        release[3]=d;

        RL(customer_number);

    }


}


int RQ(int customer_number){

 
    // loop as long as i < 4
    for(int i=0;i<4;i++){
        // compare if requests at index i is less than avail res if thats the case, return  -1
        if(request[i]>available[i]){
            return -1;
        }
        if(request[i]>maximum[customer_number][i]){
            return -1;
        }
    }
    if(!safetyAlgorithm(customer_number, request)){
        return -1;
    }
    // request resources function
    for(int i=0; i < 4;i++){
        //decrement 
        available[i]-=request[i];
        //increment
        allocation[customer_number][i]+=request[i];
    }

    return 0;
}
void RL(int customer_number){
    for(int i=0; i < 4; i++){
        // increment release
        available[i]+=release[i];
        //decrement release at index i 
        allocation[customer_number][i]-=release[i];
    }
}

void astk(){

    printf("\n");
    //Display availble array here in this loop
    printf("available array\n");
    for(int i=0;i<4;i++){
        printf("%d ", available[i]);
    }
    printf("\n");
    // display max array
    printf("maximum array\n");
    for(int i=0; i <NUM_OF_CUST;i++){
        printf("\n");
        for(int j=0;j<NUM_OF_RES;j++){
            printf("%d\t",maximum[i][j]);
        }
    }
    printf("\n");
    //display allocated here
    printf("allocation\n");
    for(int i=0; i <NUM_OF_CUST;i++){
        printf("\n");
        for(int j=0;j<NUM_OF_RES;j++){
            printf("%d\t",allocation[i][j]);
        }
    }
    printf("\n");
    //display n here
    printf("need\n");
    for(int i=0;i<4;i++){
        printf("%d ", need[i]);
    }
    printf("\n");
}
int safetyAlgorithm(int customer_number, int* request){
    // declaring resources
    int copy_resources[4];
    int copy_allocation[NUM_OF_CUST][NUM_OF_RES];
     for(int i=0; i<4;i++){
        copy_resources[i]=available[i];
    }
      for(int i=0; i <NUM_OF_CUST;i++){
        for(int j=0;j<NUM_OF_RES;j++){
            copy_allocation[i][j]=allocation[i][j];
        }
    }

    for(int i=0; i <NUM_OF_RES;i++){
        if(*(request+i)>copy_resources[i]){
            return 0;
        }
    }

    for(int i=0; i < NUM_OF_RES;i++){
        copy_resources[i]-=*(request+i);
        copy_allocation[customer_number][i]+=*(request+i);
    }

    int finish[NUM_OF_CUST];
    for(int i=0; i <NUM_OF_CUST;i++){
        finish[i]=0;
    }

    for(int i=0; i < NUM_OF_CUST; i++){
        for(int j=0; j<NUM_OF_RES;j++){
            if(!finish[j]){
                for(int k = 0; k<4;k++){
                    if(!((maximum[j][k] - copy_allocation[j][k]) > copy_resources[k])){
                        finish[j]=1;
                        for(int l=0;l<4;l++){
                            copy_resources[l]+=copy_allocation[j][l];
                        }
                    }
                }
            }
        }
    }

    for(int i=0; i <4;i++){
        copy_allocation[customer_number][i]-=*(request+i);
    }

    for(int f = 0 ; f< NUM_OF_CUST;f++){
        if(!finish[f]){
            return 0;
        }
    }
    return 1;
}
int read_file(char* fileName, int* maximum){
  int array[n];
    int n=20; 
    //Open file:
    FILE* in = fopen(fileName,"r");


    if(!in){
         //if undefined
        printf("ERROR READING FILE \n");
        return -1;
        
    }else{
        int index=0; //STARTAT 0
        size_t count; 
        char* line = malloc(100);
        
        while(getline(&line,&count,in)!=-1){ //in each line
            char* token = NULL;
            token = strtok(line,",");
            //we need to handle what happens when
            //token is not null
            while(token!=NULL){ 
                array[index]=atoi(token);
                token=strtok(NULL,",");
                index++;
            }

        }
        //lets traverse the 2d matrix
        for(int i=0; i< NUM_OF_CUST;i++){ //row
            for(int j=0;j<NUM_OF_RES;j++){ //col
                *(maximum+i*NUM_OF_RES+j)=array[i*NUM_OF_RES+j];
            }
        }

        return 1;
    }
    return 0;
}