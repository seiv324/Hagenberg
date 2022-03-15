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


/// <summary>
/// Simulate Insert/Find/Erase of n random integers for skip_set implementation
/// </summary>
/// <param name="n"> number of random integers </param>
void simulate_own_set_int(int n){
  
  /*cout << "----- Start Run with n ( " << n << " ) random integers in skip set -----" << endl;*/
  Skip_set<int> s(0, 0.5);

  auto start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.insert(rand());
  }
  auto end = high_resolution_clock::now();
  duration<double> diff_ins = end-start;
  
  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.find(rand());
  }
  end = high_resolution_clock::now();
  duration<double> diff_find = end - start;
  

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.erase(rand());
  }
  end = high_resolution_clock::now();
  duration<double> diff_erase = end - start;

  //cout << "Time Insert: " << (diff_ins).count() << endl;
  //cout << "Time Search: " << (diff_find).count() << endl;
  //cout << "Time Erase: " << (diff_erase).count() << endl;
  //cout << "----- End Run with n ( " << n << " ) random integers in skip set -----" << endl;
  //cout << endl;

  std::ofstream ofile;
  std::setprecision(6);
  ofile.open("results_int_self.txt", std::ios::app); //app is append which means it will put the text at the end

   ofile << "ins;" << n << ";" << (diff_ins).count() << endl;
   ofile << "find;" << n << ";" << (diff_find).count() << endl;
   ofile << "erase;" << n << ";" << (diff_erase).count() << endl;

  ofile.close();

}

/// <summary>
/// Generate a string of provided length from an array 
/// of all letters 
/// </summary>
/// <param name="len"> length of randomly assembled string </param>
/// <returns></returns>
string generate_rand_string(int len) {
  static const char alphanum[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
  std::string tmp_s;
  int tmp_len = len;
  if (len > 150) {
    tmp_len = 150;
  }
  tmp_s.reserve(tmp_len);
  for (int i = 0; i < tmp_len; i++) {
    tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
  }

  return tmp_s;
}

/// <summary>
/// Simulate Insert/Find/Erase of n random strings for skip_set implementation
/// </summary>
/// <param name="n"> number of random strings </param>
void simulate_own_set_string(int n) {

  /*cout << "----- Start Run with n ( " << n << " ) random strings in skip set -----" << endl;*/
  Skip_set<string> s("", 0.5);

  auto start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.insert(generate_rand_string(rand()));
  }
  auto end = high_resolution_clock::now();
  duration<double> diff_ins = end - start;
  
  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.find(generate_rand_string(rand()));
  }
  end = high_resolution_clock::now();
  duration<double> diff_find = end - start;
  
  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.erase(generate_rand_string(rand()));
  }
  end = high_resolution_clock::now();
  duration<double> diff_erase = end - start;
  //cout << "Time Insert: " << (diff_ins).count() << endl;
  //cout << "Time Search: " << (diff_find).count() << endl;
  //cout << "Time Erase: " << (diff_erase).count() << endl;
  //cout << "----- End Run with n ( " << n << " ) random strings in skip set -----" << endl;
  //cout << endl;

  std::ofstream ofile;
  std::setprecision(6);
  ofile.open("results_string_self.txt", std::ios::app); //app is append which means it will put the text at the end

  ofile << "ins;" << n << ";" << (diff_ins).count() << endl;
  ofile << "find;" << n << ";" << (diff_find).count() << endl;
  ofile << "erase;" << n << ";" << (diff_erase).count() << endl;

  ofile.close();
}

/// <summary>
/// Simulate Insert/Find/Erase of n random integers STL set implementation
/// </summary>
/// <param name="n"> number of random integers </param>
void simulate_set_int(int n) {

  //cout << "----- Start Run with n ( " << n << " ) random integers in STL set -----" << endl;
  set<int> s;

  auto start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.insert(rand());
  }
  auto end = high_resolution_clock::now();
  duration<double> diff_ins = end - start;

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.find(rand());
  }
  end = high_resolution_clock::now();
  duration<double> diff_find = end - start;

  start = high_resolution_clock::now();
  for (int i = 0; i < n; i++) {
    s.erase(rand());
  }
  end = high_resolution_clock::now();
  duration<double> diff_erase = end - start;
  //cout << "Time Insert: " << (diff_ins).count() << endl;
  //cout << "Time Search: " << (diff_find).count() << endl;
  //cout << "Time Erase: " << (diff_erase).count() << endl;
  //cout << "----- End Run with n ( " << n << " ) random integers in STL set -----" << endl;
  //cout << endl;

  std::ofstream ofile;
  std::setprecision(6);
  ofile.open("results_int_set.txt", std::ios::app); //app is append which means it will put the text at the end

  ofile << "ins;" << n << ";" << (diff_ins).count() << endl;
  ofile << "find;" << n << ";" << (diff_find).count() << endl;
  ofile << "erase;" << n << ";" << (diff_erase).count() << endl;

  ofile.close();

}


/// <summary>
/// Simulate Insert/Find/Erase of n random strings STL set implementation
/// </summary>
/// <param name="n"> number of random strings </param>
void simulate_all(int n) {
  std::ofstream ofile1;
  std::ofstream ofile2;
  std::ofstream ofile3;
  std::ofstream ofile4;

  int counter = 50000;
  int counter_raise = 10000;

  ofile1.open("results_int_self.txt", std::ios::app);
  ofile2.open("results_int_set.txt", std::ios::app);
  ofile3.open("results_string_self.txt", std::ios::app);
  ofile4.open("results_string_set.txt", std::ios::app);

  std::setprecision(6);

  while(counter < n){
    // OWN INT
    Skip_set<int> s1(0, 0.5);
    for (int i = 0; i < 20; i++) {
      auto start = high_resolution_clock::now();
      for (int i = 0; i < counter; i++) {
        s1.insert(rand());
      }
      auto end = high_resolution_clock::now();
      duration<double> diff_ins = end - start;
      start = high_resolution_clock::now();
      for (int i = 0; i < counter; i++) {
        s1.find(rand());
      }
      end = high_resolution_clock::now();
      duration<double> diff_find = end - start;
      start = high_resolution_clock::now();
      for (int i = 0; i < counter; i++) {
        s1.erase(rand());
      }
      end = high_resolution_clock::now();
      duration<double> diff_erase = end - start;
      ofile1 << "ins;" << counter << ";" << (diff_ins).count() << endl;
      ofile1 << "find;" << counter << ";" << (diff_find).count() << endl;
      ofile1 << "erase;" << counter << ";" << (diff_erase).count() << endl;
    }
    //cout << "Int Self | ";
    // SET INT
    
    set<int> s2;
    for (int i = 0; i < 20; i++) {
      auto start = high_resolution_clock::now();
      for (int i = 0; i < counter; i++) {
        s2.insert(rand());
      }
      auto end = high_resolution_clock::now();
      duration<double> diff_ins = end - start;
      start = high_resolution_clock::now();
      for (int i = 0; i < counter; i++) {
        s2.find(rand());
      }
      end = high_resolution_clock::now();
      duration<double> diff_find = end - start;
      start = high_resolution_clock::now();
      for (int i = 0; i < counter; i++) {
        s2.erase(rand());
      }
      end = high_resolution_clock::now();
      duration<double> diff_erase = end - start;
      ofile2 << "ins;" << counter << ";" << (diff_ins).count() << endl;
      ofile2 << "find;" << counter << ";" << (diff_find).count() << endl;
      ofile2 << "erase;" << counter << ";" << (diff_erase).count() << endl;
    }
    //cout << "Int Set | ";

    // OWN STRING
    Skip_set<string> s3("", 0.5);
    for (int i = 0; i < 20; i++) {
      auto start = high_resolution_clock::now();
      for (int i = 0; i < counter; i++) {
        s3.insert(generate_rand_string(rand()));
      }
      auto end = high_resolution_clock::now();
      duration<double> diff_ins = end - start;

      start = high_resolution_clock::now();
      for (int i = 0; i < counter; i++) {
        s3.find(generate_rand_string(rand()));
      }
      end = high_resolution_clock::now();
      duration<double> diff_find = end - start;

      start = high_resolution_clock::now();
      for (int i = 0; i < counter; i++) {
        s3.erase(generate_rand_string(rand()));
      }
      end = high_resolution_clock::now();
      duration<double> diff_erase = end - start;

      ofile3 << "ins;" << counter << ";" << (diff_ins).count() << endl;
      ofile3 << "find;" << counter << ";" << (diff_find).count() << endl;
      ofile3 << "erase;" << counter << ";" << (diff_erase).count() << endl;
    }
    //cout << "String Self | ";

    // STL String
    set<string> s4;
    
    for (int i = 0; i < 20; i++) {
      auto start = high_resolution_clock::now();
      for (int i = 0; i < counter; i++) {
        s4.insert(generate_rand_string(rand()));
      }
      auto end = high_resolution_clock::now();
      duration<double> diff_ins = end - start;

      start = high_resolution_clock::now();
      for (int i = 0; i < counter; i++) {
        s4.find(generate_rand_string(rand()));
      }
      end = high_resolution_clock::now();
      duration<double> diff_find = end - start;

      start = high_resolution_clock::now();
      for (int i = 0; i < counter; i++) {
        s4.erase(generate_rand_string(rand()));
      }
      end = high_resolution_clock::now();
      duration<double> diff_erase = end - start;

      ofile4 << "ins;" << counter << ";" << (diff_ins).count() << endl;
      ofile4 << "find;" << counter << ";" << (diff_find).count() << endl;
      ofile4 << "erase;" << counter << ";" << (diff_erase).count() << endl;
    }
    //cout << "String Set | ";

    counter += counter_raise;
    cout << counter <<endl;
  }
    ofile1.close();
    ofile2.close();
    ofile3.close();
    ofile4.close();
  
}

#endif // !SIMULATIONFILE_H

