#include <iostream>
#include <ctime>
#include <stack>
#include <queue>

using namespace std;

//Orders(order queue):
class Order{
public:
    char type;
    int processingTime;
};

//Trucks(truck stack):
class Truck{
public:
    int truckID;
    char type;
};

//Order Records(order history table)
class OrderLog{
public:
    int iteration;
    char type;
    int processingTime;
};

//Queue printing function declaration:
void printOrderQueue(queue<Order> queuedOrders);

//Truck stack printing function declaration:
void printTruckStack(stack<Truck> stackedTrucks);


int main(){

    //Order queues
    queue<Order> queueS;
    queue<Order> queueM;
    queue<Order> queueB;
    //TruckStack
    stack<Truck> truckStack;

    //Variables for tracking standby truck capacity out of 5 by type:
    int processedS = 0;
    int processedM = 0;
    int processedB = 0;
    //Variables for identifying dispatched trucks by type
    int truckS = 0;
    int truckM = 0;
    int truckB = 0;

    const int MAX_ITERATIONS = 50;//Number of days simulated
    const int TRUCK_CAPACITY = 5;
    srand(time(NULL));
    OrderLog orderHistory[1000]; //Array for storing order records, set to 1000 so that all orders can be accounted for
    int orderHistoryCount = 0; //Used as a counter for the orderHistory array
    int newOrderCount;
    int numNewOrders; // variable used in for loop for RNG for number of new orders in an iteration
    char newOrders[3]; //Array allocation for total possible daily orders

    for (int iteration = 1; iteration <= MAX_ITERATIONS; iteration++){         //for loop to run simulation for all 50 iterations --50 days

        newOrderCount = 0; //Variable used to count the number of each itration's new orders
        numNewOrders = rand() % 4;  //RNG for number of new orders in an iteration

        for (int i = 0; i < numNewOrders; i++) {
            char orderTypeChoices[3] = {'S', 'M', 'B'};
            char typeOrdered = orderTypeChoices[rand() % 3];   //RNG for order type

            int processingTime = (rand() % 4) + 1; //RNG for time to process

            Order newOrder;
                newOrder.type = typeOrdered;
                newOrder.processingTime = processingTime;

            // Allocating order types to their respective queues:
            if (typeOrdered == 'S'){
                queueS.push(newOrder);
            }
            else if (typeOrdered == 'M'){
                queueM.push(newOrder);
            }
            else if (typeOrdered == 'B'){
                queueB.push(newOrder);
            }

            // Save order history
            OrderLog log;
            log.iteration = iteration;
            log.type = typeOrdered;
            log.processingTime = processingTime;
            orderHistory[orderHistoryCount] = log; // Stores the object and by virtue its data entries during an iteration to the orderHistory index in the array matching history count at that specific iteration
            orderHistoryCount++;

            // Save new order for display
            newOrders[newOrderCount] = typeOrdered;  // Stores the types in an array that will be used to display orders placed at each iteration. -->Values stored in the indexes reset after each iteration
            newOrderCount++;
        }

            //Type S Order queue processing
            if (!queueS.empty()){
                queueS.front().processingTime--;

                if (queueS.front().processingTime == 0){

                    queueS.pop();
                    processedS++;

                    if (processedS == TRUCK_CAPACITY){
                        truckS++;

                        Truck newTruck;
                        newTruck.truckID = truckS;
                        newTruck.type = 'S';

                        truckStack.push(newTruck);

                        processedS = 0;
                    }
                }
            }

            //Type M Order queue processing
            if (!queueM.empty()){
                queueM.front().processingTime--;

                if (queueM.front().processingTime == 0){

                    queueM.pop();

                    processedM++;

                    if (processedM == TRUCK_CAPACITY){
                        truckM++;

                        Truck newTruck;
                        newTruck.truckID = truckM;
                        newTruck.type = 'M';

                        truckStack.push(newTruck);

                        processedM = 0;
                    }
                }
            }

            //Type B Order queue processing
            if (!queueB.empty()){
                queueB.front().processingTime--;

                if (queueB.front().processingTime == 0){

                    queueB.pop();

                    processedB++;

                    if (processedB == TRUCK_CAPACITY){

                        truckB++;

                        Truck newTruck;
                        newTruck.truckID = truckB;
                        newTruck.type = 'B';

                        truckStack.push(newTruck);

                        processedB = 0;
                    }
                }
            }

        //New and pending Order entries per iteration:
        cout << "Day: " << iteration << endl;
        cout << "New Orders: ";

        if (newOrderCount == 0){
            cout << "None";
        }
        else{
            for (int i = 0; i < newOrderCount; i++) {
                cout << "|" << newOrders[i] << "|";               // Prints out new orders for the iteration
            }
        }
        cout << endl;

        //Calling the order queue printing function
        cout << "Queue S: ";
        printOrderQueue(queueS);
        cout << endl;

        cout << "Queue M: ";
        printOrderQueue(queueM);
        cout << endl;

        cout << "Queue B: ";
        printOrderQueue(queueB);
        cout << endl;

        //Printing orders ready and waiting for truck departure
        cout << "Truck fill progress until departure:" << endl;
        cout << "S: " << processedS << "/5" << endl;
        cout << "M: " << processedM << "/5" << endl;
        cout << "B: " << processedB << "/5" << endl;

        //Calling the truck stack function to print out dispatched trucks
        cout << "Dispatched Trucks:" << endl;
        printTruckStack(truckStack);
        cout << endl;
    }

    // Order record:
    cout << "-------------------" << endl;
    cout << "Order record table:" << endl;
    cout << "-------------------" << endl;

    cout << "|Day|Type|Processing time|" << endl;
    cout << "--------------" << endl;

    for (int i = 0; i < orderHistoryCount; i++){
        cout << "| " << orderHistory[i].iteration << " | " << orderHistory[i].type << " | " << orderHistory[i].processingTime << " | " << endl;
        cout << "--------------" << endl;
    }

    return 0;
}


//Queue printing function defined:
void printOrderQueue(queue<Order> queuedOrders){
    if (queuedOrders.empty()){
        cout << "No orders processing";

        return;
    }

    while (!queuedOrders.empty()){
        cout << "|" << queuedOrders.front().type << "[" << queuedOrders.front().processingTime << "]" << "|";

        queuedOrders.pop();
    }
}

//Truck stack printing function defined:
void printTruckStack(stack<Truck> stackedTrucks){

    if (stackedTrucks.empty()){
        cout << "No trucks dispatched" << endl;
        return;
    }
    cout << endl;

    while (!stackedTrucks.empty()){
        cout << "Truck"
             << stackedTrucks.top().truckID << "[" << stackedTrucks.top().type << "]" << endl;
        stackedTrucks.pop();
    }
}
