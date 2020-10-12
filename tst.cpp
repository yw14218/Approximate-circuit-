#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <stdint.h>

uint32_t two_two_multiplier(int a , int b){
  if(a == 3 && b == 3){
    return 7;
  }
  else return a*b;
}

int main(){
  uint16_t a = 0b1001100110011001;
  uint16_t b = 0b1010101010101010;
  std::vector<int> a_pool;
  std::vector<int> b_pool;
  for(int i = 7; i > -1; i--){
    uint16_t tmp_a = a << (i*2);
    uint16_t tmp_b = b << (i*2);
    tmp_a = tmp_a >> 14;
    tmp_b = tmp_b >> 14;
    a_pool.push_back(tmp_a);
    b_pool.push_back(tmp_b);
  }

  uint32_t sum = 0;
  int n = 0;
  for(unsigned i = 0; i <= 7; i++){
    for(unsigned j = 0; j <= 7; j++){
        n++;
        uint32_t tmp = two_two_multiplier(a_pool[i],b_pool[j]) << (2*(i+j));
        sum += tmp;
    }
  }

  return 0;
}
