#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

void trueCount(vector<vector <string> > data) {
  unordered_map<string, int> occurrences;


  for (int row = 0; row < data.size(); row++) {
    ++occurrences[data[row][1]]; // increment the count for x
  }

    // print results
    for (const auto& pr : occurrences) {
        cout << pr.first << " appears " << pr.second << " times." << endl;
    }
}

void probCounting(vector<vector <string> > data) {

}

void virtBitmap(vector<vector <string> > data) {

}
