int RQ(int);
void RL(int);
void run();
void asterisk();
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
        
        for(i=1;i < argc; i++){
            available[index]=atoi(argv[i]);
            index++;
        }

    }else{
        printf("you need to enter an arugment\n");
    }


    //READ FILE
    char* fileName = "sample.txt";

    int result = read_file(fileName,maximum[0]);
    printf("READ: %d\n\n", result);


}
int RQ(int customer_number){ //we need to request the resources
    //PSUEDO Code:
    for(int i=0; i < 4;i++){
        if(request[i] > maximum[customer_number][i]){
            return -1;
        }
        else if(request[i] > available[i]){
            return -1;
        }
    }
    //If does not meet safety algo standards
    if(!safetyAlgorithm(customer_number, request)){
        return -1;
    }

    for(int i = 0; i < 4; i++){
        allocation[customer_number][i] += request[i];
        available[i] -= request[i];
    }

    return 0;
}
void RL(int customer_number){}
void run(){}
void asterisk(){}
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