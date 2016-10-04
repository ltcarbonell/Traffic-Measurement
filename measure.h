#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <math.h>
#include <stdlib.h>
using namespace std;

unsigned long hashFunction(string str) {
  unsigned long hash = 5381;
  int c;

  for (int i = 0; i < str.size(); i++) {
    c = str.at(i);
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
}

void trueCount(vector<vector <string> > data) {
  unordered_map<string, int> occurrences;
  ofstream myfile;
  myfile.open ("trueCount.txt");

  for (int row = 0; row < data.size(); row++) {
    ++occurrences[data[row][1]]; // increment the count for x
  }

  // print results
  for (const auto& pr : occurrences) {
    myfile << pr.first << "\t" << pr.second<< endl;
  }
  cout << "Counted " << occurrences.size() << " distinct sources." << endl;
  myfile.close();
}

void probCounting(vector<vector <string> > data) {
  int SOURCE = 1;
  int DESTINATION = 2;
  int COUNTED = 3;
  double e = 2.7182818285;


  vector<int> Un;

  for (int flow = 0; flow < data.size(); flow++) {
    if (data[flow][COUNTED] == "0" ) {
      vector<int> bitMap(997, 0);
      for (int index = 0; index < data.size(); index++) {
        if (data[index][SOURCE] == data[flow][SOURCE]) {
          int hash_value = rand() % 997;
          bitMap[hash_value] = 1;
          data[index][COUNTED] = "1";
        }
      }
      int numOf0s = 0;
      for (int index = 0; index < bitMap.size(); index++) {
        if (bitMap[index] == 0) {
          numOf0s += 1;
        }
      }
      Un.push_back(numOf0s);
    }

  }


  for (int counts = 0; counts < Un.size(); counts++) {
    cout << "U " << Un[counts] << endl;
    cout << -997.00*log(Un[counts]/997.00) << endl;
  }
}

void virtBitmap(vector<vector <string> > data) {

}
