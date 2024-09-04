#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <random>
#include <cmath>
#include <ctime>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;

mpz_class prime_generator(int bit_length=2048) {

    bool prime_flag = false;

    random_device rd;
    
    gmp_randclass rr(gmp_randinit_mt);
    unsigned long seed = rd();
    rr.seed(seed);

    mpz_class rand_bits;

    while (!prime_flag) {
        rand_bits = rr.get_z_bits(bit_length);

        int prime_prob = mpz_probab_prime_p(rand_bits.get_mpz_t(), 100);

        if (prime_prob != 0) {
            prime_flag = true;
        }
        
        
    }
    return rand_bits;
}

mpz_class coprime_generator(int bit_length, mpz_class coprime_num) {

    random_device rd;

    mpz_class minimum_val;
    
    mpz_ui_pow_ui(minimum_val.get_mpz_t(), 2, bit_length-1);
    
    gmp_randclass rr(gmp_randinit_mt);
    unsigned long seed = rd();
    rr.seed(seed);

    mpz_class rand_bits;
    mpz_class gcdenominator;

    while ((gcdenominator != 1) || (rand_bits < minimum_val)) {
        rand_bits = rr.get_z_bits(bit_length);
        mpz_gcd(gcdenominator.get_mpz_t(), rand_bits.get_mpz_t(), coprime_num.get_mpz_t());
        //cout << gcdenominator << endl;
    }
    

    return rand_bits;
}

#endif