/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation, 
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file utilities.ccp
 * @author Frank Dellaert
 **/

#include <iostream>
#include <fstream>

#include <boost/date_time/gregorian/gregorian.hpp>

#include "utilities.h"

using namespace std;
using namespace boost::gregorian;

/* ************************************************************************* */
string file_contents(const string& filename, bool skipheader) {
  ifstream ifs(filename.c_str());
  if(!ifs) throw CantOpenFile(filename);

  // read file into stringstream
  stringstream ss;
  if (skipheader) ifs.ignore(256,'\n');
  ss << ifs.rdbuf();
  ifs.close();

  // return string
  return ss.str();
}

/* ************************************************************************* */
bool assert_equal(const std::string& expected, const std::string& actual) {
	if (expected == actual)
		return true;
	printf("Not equal:\n");
	std::cout << "expected: [" << expected << "]\n";
	std::cout << "actual: [" << actual << "]" << std::endl;
	return false;
}

/* ************************************************************************* */
bool files_equal(const string& expected, const string& actual, bool skipheader) {
  try {
    string expected_contents = file_contents(expected, skipheader);
    string actual_contents   = file_contents(actual, skipheader);
    bool equal = actual_contents == expected_contents;
    if (!equal) {
      stringstream command;
      command << "diff " << actual << " " << expected << endl;
      system(command.str().c_str());
    }
    return equal;
  }
  catch (const string& reason) {
    cerr << "expection: " << reason << endl;
    return false;
  }
  return true;
}

/* ************************************************************************* */
void emit_header_comment(ofstream& ofs, const string& delimiter) {
  date today = day_clock::local_day();
  ofs << delimiter << " automatically generated by wrap on " << today << endl;
}

/* ************************************************************************* */
