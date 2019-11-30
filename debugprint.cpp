#include "debugprint.h"
#include <QString>
#include <fstream>
#include <iostream>

using namespace std;

void debugprint (const char * str)
{
  ofstream outfile ( "eggemesg.debug", ios::app);
  outfile << str << endl;
  outfile.close();
}

void debugprint (const QString & str)
{
  ofstream outfile ( "eggemesg.debug", ios::app);
  outfile << str.toStdString() << endl;
  outfile.close();
}
