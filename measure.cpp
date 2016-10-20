// reading a text file
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>
#include "measure.h"
using namespace std;




int main () {
  vector <vector <string> > data;
  // Read in the data from the packets
  ifstream myfile ( "packetsBig.txt" );
  while (myfile.is_open())
  {
    string s;
    if (!getline( myfile, s )) break;

    istringstream ss( s );
    vector <string> record;

    // remove the flow id
    getline( ss, s, ',' );

    while (ss)
    {
      string s;
      if (!getline( ss, s, ',' )) break;
      record.push_back( s );
    }

    data.push_back( record );
  }
  if (!myfile.eof())
  {
    cerr << "Done reading file!" << endl;
  }

  // Add the counted index to the data
  for (int flowNumber = 0; flowNumber < data.size(); flowNumber++) {
    data[flowNumber].push_back("0");
  }

  // True counting
  //   clear the file
  ofstream myTrueFile;
  myTrueFile.open ("trueCount.txt");
  myTrueFile.close();
  trueCount(data);
  // Do the first algorithm
  ofstream myProbFile;
  myProbFile.open ("probCount.txt");
  myProbFile.close();
  probCounting(data);
  // Do the second algorithm
  ofstream myVirtFile;
  myVirtFile.open ("virtBitmapCount.txt");
  myVirtFile.close();
  virtBitmap(data);


  cout << "Done" <<endl;
  cout << data[0][0] << " " << hashFunction(data[0][0])%997 <<endl;
  return 0;
}
