/**
 * Author: Evirir
 * Date: 2022-05-20
 * License: CC0
 * Source: own
 * Description: Compute prime factors and divisors of $n$. \texttt{getpf}
 * sets \texttt{pf} to a list of (prime factor, exponent). \texttt{getdiv}
 * modifies \texttt{div} to a list of factors (may not be in increasing order!)
 * with no duplicates. \texttt{pf} in \texttt{getdiv} should come from \texttt{getpf}.
 * Usage: vector<pair<ll, ll>> pf; vector<ll> div;
 *	getpf(pf, n); getdiv(div, pf);
 * Time: \texttt{getpf} is $O(\sqrt{n})$, \texttt{getdiv} is $\approx O(n^{1/3})$.
 * Status: tested
 */
#pragma once

#include "LinearSieveEvirir.h"

void getpf(vector<pair<ll, ll>>& pf, ll n) {
	pf.clear();
	for (ll i = 0; primes[i] * primes[i] <= n; i++)
	{
		int cnt = 0;
		while (n % primes[i] == 0)
		{
			n /= primes[i];
            cnt++;
		}
		if(cnt > 0) pf.push_back(pair<ll, ll>(primes[i], cnt));
	}
	if (n > 1)
	{
		pf.push_back(pair<ll, ll>(n, 1));
	}
}
void getdiv(vector<ll>& div, vector<pair<ll, ll>>& pf, ll n = 1, int i = 0) {
	if (pf.empty()) { div = {1}; return; } // divisors of 1
	ll x, k;
	if (i >= sz(pf)) return;
	x = n;
	for (k = 0; k <= pf[i].second; k++)
	{
		if (i == sz(pf) - 1) div.push_back(x);
		getdiv(div, pf, x, i + 1);
		x *= pf[i].first;
	}
}
