/**
 * Author: Evirir
 * Date: 2022-05-20
 * License: CC0
 * Source: own
 * Description: Linear sieve. After calling \texttt{LinearSieve},
 * \texttt{primes} is the list of primes at most $n$,
 * \texttt{isprime[x]} is whether $x$ is prime, and \texttt{lowprime[x]}
 * is the lowest prime factor of $x$.
 * Time: $O(n)$
 * Status: tested
 */
#pragma once

vector<ll> primes, lowprime;
vector<bool> isprime;
void LinearSieve(ll n)
{
    isprime.assign(n + 1, 1);
    lowprime.assign(n + 1, 0);
    isprime[1] = false;
    for (ll i = 2; i <= n; i++)
    {
        if (lowprime[i] == 0)
        {
            primes.pb(i);
            lowprime[i] = i;
        }
        for (int j = 0; j < sz(primes) && primes[j] <= lowprime[i] && i * primes[j] <= n; j++)
        {
            isprime[i * primes[j]] = false;
            lowprime[i * primes[j]] = primes[j];
        }
    }
}
