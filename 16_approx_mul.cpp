#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <stdint.h>

uint32_t approx_mul(uint16_t a, uint16_t b);
uint32_t ref_mul(uint16_t a, uint16_t b);
int two_two_multiplier(int a , int b);

int main(){
  const uint32_t MAX_IN = 0xffffffff;
  std::vector<double> h;
  unsigned int N = 0xffff;
  srand((int)time(0));
  for(uint32_t i = 0; i < N; i++){
      uint16_t a=rand();
      uint16_t b=rand();// 1B times per second
      uint32_t ref=ref_mul( (uint16_t)a, (uint16_t)b );
      uint32_t got=approx_mul( (uint16_t)a, (uint16_t)b );
      int32_t  err=(int32_t)ref-(int32_t)got;
      err=abs(err);
      double error=double(err)/double(ref);
      h.push_back(error); // We have seen one sample at error level err
  }
  // double scale= 1.0/N;
  for(uint32_t index=0; index<MAX_IN; index++){
        std::cout.setf(std::ios::fixed);
        // double p = h[index] * scale;
        double p = h[index];
        std::cout<<std::fixed<<std::setprecision(6)<<"Pr[e="<<index<<"] = "<<p<<"\n";
  }

  return 0;
}

uint32_t approx_mul(uint16_t a, uint16_t b){
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
  return sum;
}
uint32_t ref_mul(uint16_t a, uint16_t b){
  return a*b;
}

int two_two_multiplier(int a , int b){
  if(a == 3 && b == 3){
    return 7;
  }
  else return a*b;
}
