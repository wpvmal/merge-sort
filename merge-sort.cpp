#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <time.h>

using namespace std;
using namespace this_thread;

#define SCREEN_CLEANER cout<<"\033[2J\033[3J\033[H\e[?25l"; cout.flush();
#define MAX_NUMBER 32
#define DELAY 4

void printBar(int size, int line, bool firstPrint){
    cout << "\033[" << (line + 1) << ";100H\033[2K\033[100D";

    for(int i = 0; i < size; i++){
        if(!firstPrint){
            sleep_for(chrono::milliseconds(DELAY));
        }
        
        if(line % 2 == 0){
            cout << "\033[48;2;204;153;255m \033[0m"; cout.flush();
        }
        else{
            cout << "\033[48;2;153;255;204m \033[0m"; cout.flush();
        }
    }
}

void deleteBar(int size, int line){
    cout << "\033[" << (line + 1) << ";" << (size) << "H";

    for(int i = 0; i < size; i++){
        sleep_for(chrono::milliseconds(DELAY)); 
        cout << "\033[1D\033[K\033[0m"; cout.flush();
    }
}

void merge(vector<int>* numbers, int start, int end, int mid){
    int lastFromLeft = mid - start + 1;
    int lastFromRight = end - mid;
    vector<int> leftVector, rightVector;

    for(int i = 0; i < lastFromLeft; i++){
        leftVector.push_back((*numbers)[start + i]);
    }
    for(int i = 0; i < lastFromRight; i++){
        rightVector.push_back((*numbers)[mid + i + 1]);
    }

    int i = 0, j = 0, k = start;

    while (i < lastFromLeft && j < lastFromRight){
        if (leftVector[i] <= rightVector[j]){
            (*numbers)[k] = leftVector[i];
            deleteBar((*numbers)[k], k);
            printBar((*numbers)[k], k, false);
            i++;
        }
        else {
            (*numbers)[k] = rightVector[j];
            deleteBar((*numbers)[k], k);
            printBar((*numbers)[k], k, false);
            j++;
        }
        k++;
    }

    while (i < lastFromLeft){
        (*numbers)[k] = leftVector[i];
        deleteBar((*numbers)[k], k);
        printBar((*numbers)[k], k, false);
        i++;
        k++;
    }

    while (j < lastFromRight){
        (*numbers)[k] = rightVector[j];
        deleteBar((*numbers)[k], k);
        printBar((*numbers)[k], k, false);
        j++;
        k++;
    }
}

void mergeSort(vector<int>* numbers, int start, int end){

    if(start < end){
        int mid = (start + end - 1)/2;
        mergeSort(numbers, start, mid);
        mergeSort(numbers, (mid + 1), end);
        merge(numbers, start, end, mid);
    }
}


int main(){
    SCREEN_CLEANER
    sleep_for(chrono::milliseconds(300));

    vector<int> numbers;
    srand(time(0));

    for(int i = 0; i < MAX_NUMBER; i++){
        numbers.push_back((rand() % MAX_NUMBER + 1));
    }

    bool firstPrint = true;
    for (int i = 0; i < MAX_NUMBER; i++){
        printBar(numbers[i], i, firstPrint);
    }
    
    mergeSort(&numbers, 0, (numbers.size() - 1));
    
    cout << endl;
    return 0;
}

