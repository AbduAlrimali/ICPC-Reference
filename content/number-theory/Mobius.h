/**
 * Author: Unknown
 * Description: denoted as $\mu(n)$, is a fundamental number theory function that maps positive integers to $\{-1, 0, 1\}$ based on their prime factorization.
 * Status: tested
 * Time: $O(N \log \log N)$
 */

#pragma once

const int LIM = 1'000'000;
vi mu(LIM);
bitset<LIM> vis;
void mobius(){
    rep(i, 1, LIM) mu[i]=1;
    rep(i, 2, LIM) if(!vis[i]) // prime encountered
            for(int j=i;j<LIM;j+=i){
                vis[j]=1;
                if(j%((ll) i*i)==0) mu[j]=0;
                else mu[j] *= -1;
            }
}