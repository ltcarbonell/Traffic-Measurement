// reading a text file
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "measure.h"
using namespace std;




int main () {
  vector <vector <string> > data;
  // Read in the data from the packets
  ifstream myfile ( "packets.txt" );
  while (myfile.is_open())
  {
    string s;
    if (!getline( myfile, s )) break;

    istringstream ss( s );
    vector <string> record;

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
  trueCount(data);
  // Do the first algorithm
  probCounting(data);
  // Do the second algorithm
  virtBitmap(data);


  cout << "Done" <<endl;
  return 0;
}
