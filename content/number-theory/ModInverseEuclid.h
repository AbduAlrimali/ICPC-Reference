/**
 * Author: AbduAlrimali
 * Description: Computes Modular Inverse using Extended Euclid.
 * Status: Works
 */
#pragma once
#include "Euclid.h"

pair<bool, ll> modinv(ll a, ll m){
	ll x, y, g = euclid(a, m, x, y);
	if (g != 1) return {false, 0}; 
	return {true, (x % m + m) % m};
}