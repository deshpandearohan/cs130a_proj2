// Author: Arohan Deshpande
// Created Nov 12 2025
// bloomfilters.cpp

#include <iostream>
#include <cassert>
#include <vector>
#include <random>
#include <fstream>

// *** GLOBAL CONSTANTS ***
const unsigned int k = 2; // Number of hash functions
const unsigned long int N = std::pow(10, 9); // Universe size
const unsigned int m = std::pow(10, 4); // Hash table size
const unsigned int p = std::pow(2, 31) - 1; // Some prime p : p >= N
const std::vector<int> seeds = {38423, 43971}; // k fixed seeds

// *** SUBROUTINES ***
// Make random hash functions
void makehash1(std::vector<int> &a, std::vector<int> &b);
void part1();

// Hash functions
std::vector<int> hash1(const int &x, const std::vector<int> &a, const std::vector<int> &b);
std::vector<int> hash2(const int &x);

int main(int argc, char* argv[]) {

    // Bad command line arguments check
    if (!(argc == 2)) {
        std::cerr << "Usage: ./bloomfilters.cpp <part #: 1, 2, 3>" << std::endl;
        exit(1);
    }

    // Parts 1, 2, and 3 of testing
    switch (atoi(argv[1])) {
        case 1:
            part1();
            break;
        case 2:
            
            break;
        case 3:

            break;

        default:
            std::cerr << "Error: part # should be 1, 2, or 3" << std::endl;
            exit(1);
    }

    return 0;
}






void makehash1(std::vector<int> &a, std::vector<int> &b) {
    for (int i = 0; i < k; ++i) {
        std::mt19937 randgen(seeds.at(i));
        a[i] = randgen();
        b[i] = randgen();
    }
}






void part1() {
    // Check global constants
    assert(seeds.size() == k);
    assert(m < N);
    assert(p >= N);

    std::vector<int> a(k), b(k);
    makehash1(a, b);

    // Set up input data file ifstream
    std::ifstream inFile;
    std::string datafile;
    std::cout << "Data file: ";
    std::cin >> datafile;
    inFile.open(datafile);

    // Bad data file input check
    if (inFile.fail()) {
        std::cerr << "Could not open \"" << datafile << "\"" << std::endl;
        exit(1);
    }

    // Run hash1
    int x;
    std::ofstream outFile;
    outFile.open("results1.txt");
    while (inFile >> x) {
        for (auto h: hash1(x, a, b)) {
            outFile << h << " ";
        }
        outFile << std::endl;
    }
    std::cout << "Successfully hashed " << datafile << " to indices in results1.txt" << std::endl;
    inFile.close();
    outFile.close();

    // Run hash2;
    inFile.open(datafile);
    outFile.open("results2.txt");
    while (inFile >> x) {
        for (auto h: hash2(x)) {
            outFile << h << " ";
        }
        outFile << std::endl;
    }
    std::cout << "Successfully hashed " << datafile << " to indices in results2.txt" << std::endl;
    inFile.close();
    outFile.close();
}






std::vector<int> hash1(const int &x, const std::vector<int> &a, const std::vector<int> &b) {
    std::vector<int> hashes(k);
    for (int i = 0; i < k; ++i) {
        hashes[i] = ( (a.at(i) * x + b.at(i)) % p ) % m;
    }
    return hashes;
}






std::vector<int> hash2(const int &x) {
    std::vector<int> hashes(k);
    for (int i = 0; i < k; ++i) {
        std::mt19937 randgen(seeds.at(i) + x);
        std::uniform_int_distribution<int> dist(0, m - 1);
        hashes[i] = dist(randgen);
    }
    return hashes;
}