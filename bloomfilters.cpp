// Author: Arohan Deshpande
// Created Nov 12 2025
// bloomfilters.cpp

#include <iostream>
#include <ctime>
#include <cassert>
#include <vector>
#include <random>
#include <fstream>

// *** GLOBAL CONSTANTS ***
const unsigned int k = 2; // Number of hash functions
const unsigned int c = 2;
const unsigned long int N = std::pow(10, 9); // Universe size
const unsigned int n = 500; // Number of items in S to represent, i.e. |S|
const unsigned int m = 10000; // Hash table size
const unsigned int p = std::pow(2, 31) - 1; // Some prime p : p >= N
std::vector<unsigned int> seeds(k); // Fixed seeds created in createSeeds()
std::vector<unsigned int> a(k), b(k);

// *** SUBROUTINES ***
void makehash1(std::mt19937 &randgen, std::vector<unsigned int> &a, std::vector<unsigned int> &b);
void createSeeds(std::mt19937 &randgen, std::vector<unsigned int> &seeds);
void part1();
void part2();
void part3();
std::vector<int> hash1(const int &x);
std::vector<int> hash2(std::mt19937 &randgen, const int &x);

// *** CLASSES ***
class BloomFilters {
    public:
        BloomFilters();
        BloomFilters(const int &b_c, const int &b_k);
        void Add(std::mt19937 &randgen, const int &x);
        bool Contains(std::mt19937 &randgen, const int &x) const;
    private:
        unsigned int b_c;
        unsigned int b_k;
        unsigned int b_m;
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
            // No real testing required for part 2
            std::cout << "Yeah nothing really to be done here" << std::endl;
            break;
        case 3:
            part3();
            break;

        default:
            std::cerr << "Error: part # should be 1, 2, or 3" << std::endl;
            exit(1);
    }

    return 0;
}






void makehash1(std::mt19937 &randgen, std::vector<unsigned int> &a, std::vector<unsigned int> &b) {
    for (int i = 0; i < k; ++i) {
        // Clear a and b
        a = {};
        b = {};

        for (int i = 0; i < k; ++i) {
            std::uniform_int_distribution<int> dista(1, p - 1);
            std::uniform_int_distribution<int> distb(0, p - 1);
            a[i] = dista(randgen);
            b[i] = distb(randgen);
        }
    }
}







void createSeeds(std::mt19937 &randgen, std::vector<unsigned int> &seeds) {
    for (int i = 0; i < k; ++i) {
        seeds[i] = randgen();
    }
}






void part1() {
    std::mt19937 randgen(static_cast<unsigned int>(std::time(0)));

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
    makehash1(randgen, a, b);
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

    // Run hash2
    createSeeds(randgen, seeds);
    inFile.open(datafile);
    outFile.open("results2.csv");
    while (inFile >> x) {
        std::vector<int> hashes = hash2(randgen, x);
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
    return;
}






void part3() {
    for (int c = 8; c <= 10; ++c) {

    }
    BloomFilters table = BloomFilters();
    const int seed = time(0);
    std::vector<int> S(n);
    std::mt19937 randgen(seed);

    for (int i = 0; i < n; ++i) {
        int x = randgen();
        table.Add(randgen, x);
        S.push_back(x);
    }

    for (int i = 0; i < n; ++i) {
        
    }
}






double test(const int &b_c, const int &b_k) {
    BloomFilters table = BloomFilters(b_c, b_k);
    const int seed = time(0);
    std::vector<int> S(n);
    std::mt19937 randgen(seed);

    for (int i = 0; i < n; ++i) {
        int x = randgen();
        table.Add(randgen, x);
        S.push_back(x);
    }

    
}






std::vector<int> hash1(const int &x) {
    std::vector<int> hashes(k);
    for (int i = 0; i < k; ++i) {
        hashes[i] = ( (a[i] * x + b[i]) % p ) % m;
    }
    return hashes;
}






std::vector<int> hash2(std::mt19937 &randgen, const int &x) {
    std::vector<int> hashes(k);
    for (int i = 0; i < k; ++i) {
        randgen.seed(seeds.at(i) + x);
        hashes[i] = randgen() % m;
    }
    return hashes;
}






BloomFilters::BloomFilters() {
    T.resize(m);
    T = {0};
    b_c = c;
    b_k = k;
    b_m = b_c * n;
}






BloomFilters::BloomFilters(const int &b_c, const int &b_k) {
    T.resize(m);
    T = {0};
    this->b_c = b_c;
    this->b_k = b_k;
    b_m = this->b_c * n;
}






void BloomFilters::Add(std::mt19937 &randgen, const int &x) {
    std::vector<int> hashes = useHash1 ? hash1(x) : hash2(randgen, x);
    for (int h : hashes) {
        T[h] = 1;
    }
}






bool BloomFilters::Contains(std::mt19937 &randgen, const int &x) const {
    std::vector<int> hashes = useHash1 ? hash1(x) : hash2(randgen, x);
    for (int h : hashes) {
        if (T[h] == 0) return false;
    }
    return true;
}