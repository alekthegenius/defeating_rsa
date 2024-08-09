#ifndef CRYPTION_H
#define CRYPTION_H

#include <iostream>
#include <random>
#include <cmath>
#include <ctime>
#include <gmpxx.h>
#include "generator.h"
#include <cstdlib>
#include <bits/stdc++.h>
#include <regex>

using namespace std;

vector<mpz_class> key_generator(int bit_length=2048) {
  mpz_class p;
  mpz_class q;
  mpz_class n;
  
  mpz_class pq_difference;
  mpz_ui_pow_ui(pq_difference.get_mpz_t(), 2, bit_length/2);

  do {
    p = prime_generator(bit_length);
    q = prime_generator(bit_length);
  }
  while (abs(p-q) < pq_difference);
  

  n = p*q;

  mpz_class toitent_n;
  mpz_class toitent_p;
  mpz_class toitent_q;

  toitent_p = p-1;
  toitent_q = q-1;

  mpz_lcm(toitent_n.get_mpz_t(), toitent_p.get_mpz_t(), toitent_q.get_mpz_t());

  //cout << "Toitent N: " << toitent_n << endl;

  mpz_class e;

  e = coprime_generator(16, toitent_n);
  
  mpz_class d;

  if (gcd(e, toitent_n) != 1) {
    // Handle the case when mpz_invert() returns zero
    // You can either generate a new e or handle the error appropriately
    cout << "Error: Failed to calculate d" << endl;
    return vector<mpz_class>();
  }

  mpz_invert(d.get_mpz_t(), e.get_mpz_t(), toitent_n.get_mpz_t());


  //cout << "P: " << p << endl;
  //cout << "Q: " << q << endl;

  //cout << "N: " << n << endl;

  //cout << "E: " << e << endl;

  //cout << "D: " << d << endl;

  return vector<mpz_class> {p, q, n, e, d};

}

mpz_class encryption(mpz_class message, mpz_class n, mpz_class e) {
  mpz_class c;

  mpz_powm(c.get_mpz_t(), message.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());

  return c;

}

mpz_class decryption(mpz_class c, mpz_class n, mpz_class d) {
  mpz_class origin;

  mpz_powm(origin.get_mpz_t(), c.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());

  return origin;

}




mpz_class asciifi(string message) {

  vector<int> values = {};
  string text = "";
  mpz_class decimal_text;

  int divider = 20000;

  values.push_back(10000);


  for (int i = 0; i < message.length(); i++) {
    char x = message.at(i);
    int ascii_dec = int(x);

    values.push_back(ascii_dec);
    values.push_back(divider);

  }

  values.push_back(10000);

  for (int i = 0; i < values.size(); i++) {
    text.append(to_string(int(values.at(i))));
  }

  decimal_text = mpz_class(text);
  return decimal_text;

}

string desciifi(mpz_class msg) {
  vector<string> values;

  string output_text = "";
  string ascii_string;

  string divider = "20000";
  string end_divider = "10000";

  int ascii;

  string message = msg.get_str();

  regex r(divider);

  regex d(end_divider);

  
  message = regex_replace(message, d, "");
  message = regex_replace(message, r, " ");


  string s;

  stringstream ss(message);

  

  //for(char& c : str) {}



  while (getline(ss, s, ' ')) {
    values.push_back(s);
  }


  for (int i = 0; i < values.size(); i++) {
    ascii = stoi(values[i]);

    //cout << "ASCII:" << ascii << endl;

    //cout << "CHAR:" << (char)ascii << endl;
    

    ascii_string = (char)ascii;



    output_text.append(ascii_string);
  }


  return output_text;


}


#endif
