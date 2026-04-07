/**
 * Author: Håkan Terelius
 * Date: 2009-08-26
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 * Description: Prime sieve for generating all primes up to a certain limit.
 * Time: $O(LIM)$.
 * Status: Tested
 */
#pragma once

// O(N)
const int LIM = 5'000'000;
vi spf, primes;
void eratosthenes() {
    spf.resize(LIM);
    for (int i = 2; i < LIM; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; i * primes[j] < LIM; j++) {
            spf[i * primes[j]] = primes[j];
            if (primes[j] == spf[i]) break;
        }
    }
}