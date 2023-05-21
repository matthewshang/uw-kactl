/**
 * Author: Evirir
 * Date: 2022-05-20
 * License: CC0
 * Source: own
 * Description: Compute the mobius function $\mu(x)$ for $1 \le x \le n$.
 * Time: $O(n)$
 * Status: partially tested on CF 439E
 */
#pragma once

#include "LinearSieve_Evirir.h"

vector<int> mobius;
void SieveMobius(ll n)
{
    mobius.resize(n + 1);
    mobius[1] = 1;
    for (ll i = 2; i <= n; i++)
    {
        if (lowprime[i] == i) mobius[i] = -1;
        for (int j = 0; j < sz(primes) && primes[j] <= lowprime[i] && i * primes[j] <= n; j++)
        {
            ll cur = i * primes[j];
            if (primes[j] == lowprime[i]) mobius[cur] = 0;
            else mobius[cur] = -mobius[i];
        }
    }
}
