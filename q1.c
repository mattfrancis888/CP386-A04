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
int safetyAlgorithm(int customer_number, int* request){}
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