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

}
int RQ(int customer_number){}
void RL(int customer_number){}
void run(){}
void asterisk(){}
int safetyAlgorithm(int customer_number, int* request){}
int read_file(char* fileName, int* maximum){

}