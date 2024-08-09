#include "cryption.h"
#include <gmpxx.h>
#include <math.h>

using namespace std;

int main() {
    vector<mpz_class> keys = key_generator(2048);

    mpz_class p = keys[0];
    mpz_class q = keys[1];
    mpz_class n = keys[2];
    mpz_class e = keys[3];
    mpz_class d = keys[4];

    mpz_class mesg;

    string mesg_input;

    cout << "Message: ";
    getline (cin, mesg_input);

    mesg = asciifi(mesg_input);

    //mesg = 35;

    cout << "Original message: " << mesg << endl;

    mpz_class encrypted = encryption(mesg, n, e);

    cout << "Encrypted message: " << encrypted << endl;
    mpz_class decrypted = decryption(encrypted, n, d);

    cout << "Decrypted Message: " << decrypted << endl;

    cout << "Decrypted Text: " << desciifi(decrypted) << endl;


    return 0;
}

