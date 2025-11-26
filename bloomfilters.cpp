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
const unsigned int n = 5000; // Number of items in S to represent, i.e. |S|
const unsigned int m = std::pow(10, 4); // Hash table size
const unsigned int p = std::pow(2, 31) - 1; // Some prime p : p >= N
const std::vector<int> seeds = {38423, 43971}; // k fixed seeds
std::vector<int> a(k), b(k);

// *** SUBROUTINES ***

void makehash1(std::vector<int> &a, std::vector<int> &b);
void part1();
void part2();
std::vector<int> hash1(const int &x);
std::vector<int> hash2(const int &x);

// *** CLASSES ***
class BloomFilters {
    public:
        BloomFilters();
        void Add(const int &x);
        bool Contains(const int &x) const;
    private:
        bool useHash1 = true;
        std::vector<int> T;

};

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
    outFile.open("results1.csv");
    while (inFile >> x) {
        std::vector<int> hashes = hash1(x);
        for (int i = 0; i < k; ++i) {
            if (i == k - 1) outFile << hashes[i];
            else outFile << hashes[i] << ", ";
        }
        outFile << std::endl;
    }
    std::cout << "Successfully hashed " << datafile << " to indices in results1.csv" << std::endl;
    inFile.close();
    outFile.close();

    // Run hash2;
    inFile.open(datafile);
    outFile.open("results2.csv");
    while (inFile >> x) {
        std::vector<int> hashes = hash2(x);
        for (int i = 0; i < k; ++i) {
            if (i == k - 1) outFile << hashes[i];
            else outFile << hashes[i] << ", ";
        }
        outFile << std::endl;
    }
    std::cout << "Successfully hashed " << datafile << " to indices in results2.csv" << std::endl;
    inFile.close();
    outFile.close();
}






void part2() {
    
}






std::vector<int> hash1(const int &x) {
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






BloomFilters::BloomFilters() {
    T.resize(m);
    T = {0};
}






void BloomFilters::Add(const int &x) {
    std::vector<int> hashes = useHash1 ? hash1(x) : hash2(x);
    for (int h : hashes) {
        T[h] = 1;
    }
}






bool BloomFilters::Contains(const int &x) const {
    std::vector<int> hashes = useHash1 ? hash1(x) : hash2(x);
    for (int h : hashes) {
        if (T[h] == 0) return false;
    }
    return true;
}