#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <numeric>
using namespace std;

const unsigned int N = pow(10, 9);
const unsigned int DATA_SIZE = pow(10, 4);

int main() {

    // 1. Uniform random
    srand(time(0));
    ofstream outFile;
    outFile.open("uniform.txt");
    for (int i = 0; i < DATA_SIZE; i++) {
        outFile << rand() % N + 1 << " ";
    }
    outFile.close();

    // 2. Sequential
    outFile.open("sequential.txt");
    for (int i = 0; i < DATA_SIZE; i++) {
        outFile << i << " ";
    }
    outFile.close();

    // 3. Sequential even numbers
    outFile.open("sequentialEven.txt");
    for (int i = 0; i < DATA_SIZE; i++) {
        outFile << i * 2 << " ";
    }
    outFile.close();
}