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

  for (int row = 0; row < data.size(); row++) {
    cout << data[row][0] << " " << data[row][1] << " " << data[row][2];
    cout << endl;
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
