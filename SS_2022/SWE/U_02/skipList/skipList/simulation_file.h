#ifndef SIMULATIONFILE_H
#define SIMULTAIONFILE_H

#include <chrono>
#include <iostream>
#include<sstream>
#include<fstream>
#include<iomanip>

#include <set>

#include "skipSet.h";


using namespace std;
using namespace std::chrono;



void simulate_own_set_int(int n){
  
  cout << "----- Start Run with n ( " << n << " ) random integers in skip set -----" << endl;
  Skip_set<int> s(0, 0.5);

  auto start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.insert(rand());
  }
  auto end = high_resolution_clock::now();
  duration<double> diff_ins = end-start;
  cout << "Time Insert: " << (diff_ins).count() << endl;

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.find(rand());
  }
  end = high_resolution_clock::now();
  duration<double> diff_find = end - start;
  cout << "Time Search: " << (diff_find).count() << endl;

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.erase(rand());
  }
  end = high_resolution_clock::now();
  duration<double> diff_erase = end - start;
  cout << "Time Erase: " << (diff_erase).count() << endl;
  cout << "----- End Run with n ( " << n << " ) random integers in skip set -----" << endl;
  cout << endl;

  std::ofstream ofile;
  std::setprecision(6);
  ofile.open("results_int_self.txt", std::ios::app); //app is append which means it will put the text at the end

   ofile << "ins;" << n << ";" << (diff_ins).count() << endl;
   ofile << "find;" << n << ";" << (diff_find).count() << endl;
   ofile << "erase;" << n << ";" << (diff_erase).count() << endl;

  ofile.close();

}

string generate_rand_string(int len) {
  static const char alphanum[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
  std::string tmp_s;
  tmp_s.reserve(len);

  for (int i = 0; i < len; ++i) {
    tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
  }

  return tmp_s;
}

void simulate_own_set_string(int n) {

  cout << "----- Start Run with n ( " << n << " ) random strings in skip set -----" << endl;
  Skip_set<string> s("", 0.5);

  auto start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.insert(generate_rand_string(rand()));
  }
  auto end = high_resolution_clock::now();
  duration<double> diff_ins = end - start;
  cout << "Time Insert: " << (diff_ins).count() << endl;

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.find(generate_rand_string(rand()));
  }
  end = high_resolution_clock::now();
  duration<double> diff_find = end - start;
  cout << "Time Search: " << (diff_find).count() << endl;

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.erase(generate_rand_string(rand()));
  }
  end = high_resolution_clock::now();
  duration<double> diff_erase = end - start;
  cout << "Time Erase: " << (diff_erase).count() << endl;
  cout << "----- End Run with n ( " << n << " ) random strings in skip set -----" << endl;
  cout << endl;

  std::ofstream ofile;
  std::setprecision(6);
  ofile.open("results_string_self.txt", std::ios::app); //app is append which means it will put the text at the end

  ofile << "ins;" << n << ";" << (diff_ins).count() << endl;
  ofile << "find;" << n << ";" << (diff_find).count() << endl;
  ofile << "erase;" << n << ";" << (diff_erase).count() << endl;

  ofile.close();
}


void simulate_set_int(int n) {

  cout << "----- Start Run with n ( " << n << " ) random integers in STL set -----" << endl;
  set<int> s;

  auto start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.insert(rand());
  }
  auto end = high_resolution_clock::now();
  duration<double> diff_ins = end - start;
  cout << "Time Insert: " << (diff_ins).count() << endl;

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.find(rand());
  }
  end = high_resolution_clock::now();
  duration<double> diff_find = end - start;
  cout << "Time Search: " << (diff_find).count() << endl;

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.erase(rand());
  }
  end = high_resolution_clock::now();
  duration<double> diff_erase = end - start;
  cout << "Time Erase: " << (diff_erase).count() << endl;
  cout << "----- End Run with n ( " << n << " ) random integers in STL set -----" << endl;
  cout << endl;

  std::ofstream ofile;
  std::setprecision(6);
  ofile.open("results_int_set.txt", std::ios::app); //app is append which means it will put the text at the end

  ofile << "ins;" << n << ";" << (diff_ins).count() << endl;
  ofile << "find;" << n << ";" << (diff_find).count() << endl;
  ofile << "erase;" << n << ";" << (diff_erase).count() << endl;

  ofile.close();

}

void simulate_set_string(int n) {

  cout << "----- Start Run with n ( " << n << " ) random strings in STL set -----" << endl;
  set<string> s;

  auto start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.insert(generate_rand_string(rand()));
  }
  auto end = high_resolution_clock::now();
  duration<double> diff_ins = end - start;
  cout << "Time Insert: " << (diff_ins).count() << endl;

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.find(generate_rand_string(rand()));
  }
  end = high_resolution_clock::now();
  duration<double> diff_find = end - start;
  cout << "Time Search: " << (diff_find).count() << endl;

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.erase(generate_rand_string(rand()));
  }
  end = high_resolution_clock::now();
  duration<double> diff_erase = end - start;
  cout << "Time Erase: " << (diff_erase).count() << endl;
  cout << "----- End Run with n ( " << n << " ) random STL in skip set -----" << endl;
  cout << endl;

  std::ofstream ofile;
  std::setprecision(6);
  ofile.open("results_string_int.txt", std::ios::app); //app is append which means it will put the text at the end

  ofile << "ins;" << n << ";" << (diff_ins).count() << endl;
  ofile << "find;" << n << ";" << (diff_find).count() << endl;
  ofile << "erase;" << n << ";" << (diff_erase).count() << endl;

  ofile.close();
}

#endif // !SIMULATIONFILE_H

