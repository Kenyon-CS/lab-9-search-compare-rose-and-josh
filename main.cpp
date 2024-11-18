#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Sequential search
int seq_search(vector<int> &keys, int key, int &numCmp) {
    numCmp=0;
    for (size_t i=0; i<keys.size(); ++i) {
        ++numCmp;
        if (keys[i]==key) {
            return i; // Found key
        }
    }
    return -1; // Key not found
}

// Sequential search with start and stop range
int seq_search(vector<int> &keys, int key, int start, int stop, int &numCmp) {
    for (int i=start; i<=stop;++i) {
        ++numCmp;
        if (keys[i]==key) {
            return i; // Found key
        }
    }
    return -1; // Key not found
}

// Binary search
int bin_search(vector<int> &keys, int key, int &numCmp) {
    int left=0, right=keys.size() - 1;
    numCmp=0;
    while (left<=right) {
        ++numCmp;
        int mid=left+(right-left) / 2;
        if (keys[mid]==key) {
            return mid; // Found key
        } else if (keys[mid] < key) {
            left=mid+1;
        } else {
            right=mid-1;
        }
    }
    return -1; // Key not found
}

// Enhanced binary search: switches to sequential search if remaining range is < 15
int bin2_search(vector<int> &keys, int key, int &numCmp) {
    int left=0, right=keys.size() - 1;
    numCmp=0;

    while (right-left>15) {
        ++numCmp;
        int mid=left+(right-left)/2;
        if (keys[mid]==key) {
            return mid; // Found key
        } else if (keys[mid]<key) {
            left=mid+1;
        } else {
            right=mid-1;
        }
    }
    return seq_search(keys, key, left, right, numCmp);
}

// Test the search algorithms
int main() {
    // Initialize random seed
    srand(time(NULL));

    // Create a vector of 100,000 integers
    vector<int> data(100000);
    for (auto &num : data) {
        num=rand()%10000000;
    }

    // Sort the vector using STL sort
    sort(data.begin(), data.end());

    // Generate 50 random numbers from the data (guaranteed to be in the array)
    vector<int> present_keys;
    for (int i=0; i<50; ++i) {
        present_keys.push_back(data[rand() % data.size()]);
    }

    // Generate 50 random numbers (may or may not be in the array)
    vector<int> random_keys;
    for (int i=0; i<50; ++i) {
        random_keys.push_back(rand() % 10000000);
    }

    // Print headers for the table
    cout << "Search\t\tFound\t\tSeq.search\tBin search\tEnhanced search" << endl;

    // Print the results for present_keys and random_keys
    for (const auto &key : present_keys) {
        int numCmp1, numCmp2, numCmp3;

        // Find the key using the different search algorithms
        seq_search(data, key, numCmp1);
        bin_search(data, key, numCmp2);
        bin2_search(data, key, numCmp3);

        // Output the results in the desired format
        cout<<key<<"\t\t"<<key<<"\t\t"<< numCmp1<<"\t\t"<< numCmp2<<"\t\t"<< numCmp3<<endl;
    }

    for (const auto &key : random_keys) {
        int numCmp1, numCmp2, numCmp3;

        // Find the key using the different search algorithms
        seq_search(data, key, numCmp1);
        bin_search(data, key, numCmp2);
        bin2_search(data, key, numCmp3);

        // Output the results in the desired format (for not found keys, display -1)
        cout<<key<<"\t\t"<<-1<<"\t\t"<<numCmp1<<"\t\t"<< numCmp2<<"\t\t"<< numCmp3<<endl;
    }

    return 0;
}
