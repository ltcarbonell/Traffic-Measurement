#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <math.h>
#include <stdlib.h>
using namespace std;

#define SOURCE 1
#define DESTINATION  2
#define COUNTED  3

// Get the correct values of the counting
void trueCount(vector<vector <string> > data) {

  vector<int> counts;
  vector<string> sourceAddresses;

  // Remove duplicates from the destination addresses
  sort( data.begin(), data.end() );
  data.erase( unique( data.begin(), data.end() ), data.end() );


  for (int flow = 0; flow < data.size(); flow++) {
    int flowCount = 0;
    if (data[flow][COUNTED] == "0" ) {
      for (int index = 0; index < data.size(); index++) {
        if (data[index][SOURCE] == data[flow][SOURCE]) {
          flowCount+=1;
          data[index][COUNTED] = "1";
        }
      }
      counts.push_back(flowCount);
      sourceAddresses.push_back(data[flow][SOURCE]);
    }
  }
  ofstream myfile;
  myfile.open ("trueCount.txt");

  for (int index = 0; index < sourceAddresses.size(); index++) {
    myfile << sourceAddresses[index] << "\t" << counts[index] << endl;
  }

  cout << "Counted " << sourceAddresses.size() << " distinct sources." << endl;
  myfile.close();
}

// Count using probabalistic counting
void probCounting(vector<vector <string> > data) {

  int numberOfBits = 100003;

  vector<int> Un;
  vector<string> sourceAddresses;

  for (int flow = 0; flow < data.size(); flow++) {
    if (data[flow][COUNTED] == "0" ) {
      vector<int> bitMap(numberOfBits, 0);
      for (int index = 0; index < data.size(); index++) {
        if (data[index][SOURCE] == data[flow][SOURCE]) {
          int hash_value = rand() % numberOfBits;
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
      sourceAddresses.push_back(data[flow][SOURCE]);
    }
  }

  ofstream myfile;
  myfile.open ("probCount.txt");

  for (int counts = 0; counts < Un.size(); counts++) {
    myfile << sourceAddresses[counts] << "\t" << -(double)numberOfBits*log(Un[counts]/(double)numberOfBits) << endl;
  }

  cout << "Counted " << Un.size() << " distinct sources." << endl;
  myfile.close();

}

void virtBitmap(vector<vector <string> > data) {




  ofstream myfile;
  myfile.open ("virtBitmapCount.txt");

  myfile.close();

}
