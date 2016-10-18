#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <math.h>
#include <stdlib.h>
using namespace std;

#define SOURCE 0
#define DESTINATION  1
#define COUNTED  2
#define NUMOFBITS 997
#define NUMOFVIRTBITS 97

unsigned long hashFunction(string str) {
  unsigned long hash = 5381;
  int c;

  for (int i = 0; i < str.size(); i++) {
    c = str.at(i);
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
}


// Get the correct values of the counting
void trueCount(vector<vector <string> > data) {
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
      ofstream myfile;
      myfile.open ("trueCount.txt", ios::app);
      myfile << data[flow][SOURCE] << "\t" << flowCount << endl;
      myfile.close();
    }
  }
  cout << "Done counting using true counting." << endl;
}

// Count using probabalistic counting
void probCounting(vector<vector <string> > data) {
  for (int flow = 0; flow < data.size(); flow++) {
    if (data[flow][COUNTED] == "0" ) {
      vector<int> bitMap(NUMOFBITS, 0);
      for (int index = 0; index < data.size(); index++) {
        if (data[index][SOURCE] == data[flow][SOURCE]) {
          unsigned long hash_value = hashFunction(data[index][DESTINATION]);
          hash_value = hash_value % NUMOFBITS;
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

      ofstream myfile;
      myfile.open ("probCount.txt", ios::app);
      myfile << data[flow][SOURCE] << "\t" << -(double)NUMOFBITS*log(numOf0s/(double)NUMOFBITS) << endl;
      myfile.close();
    }
  }
  cout << "Estimated using probabalistic counting." << endl;

}

void virtBitmap(vector<vector <string> > data) {
  vector<int> bitMap(NUMOFBITS, 0);
  vector<int> virtBitmap(NUMOFVIRTBITS, 0);
  vector<int> randomArray(NUMOFVIRTBITS);


  // First create an instance of an engine.
  random_device rnd_device;
  // Specify the engine and distribution.
  mt19937 mersenne_engine(rnd_device());
  uniform_int_distribution<int> dist(1, NUMOFBITS);

  auto gen = std::bind(dist, mersenne_engine);
  generate(begin(randomArray), end(randomArray), gen);

  

  for (int flow = 0; flow < data.size(); flow++) {
    if (data[flow][COUNTED] == "0" ) {
      // int i_star = hashFunction(data[flow][DESTINATION])%NUMOFVIRTBITS;
      int src = atoi(data[flow][SOURCE].c_str());
      unsigned long hash_value = hashFunction(to_string(src^randomArray[hashFunction(data[flow][DESTINATION]) % NUMOFVIRTBITS]));
      hash_value = hash_value % NUMOFVIRTBITS;
      bitMap[hash_value] = 1;
    }
  }

  for (int index = 0; index < bitMap.size(); index++) {
    cout << bitMap[index] << endl;
  }




  ofstream myfile;
  myfile.open ("virtBitmapCount.txt");

  myfile.close();

}
