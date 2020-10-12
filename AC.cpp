
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <stdint.h>

//16 bits approx adder
uint32_t approx_add(uint16_t a, uint16_t b){
  uint16_t bot_a = a << 8;
  bot_a = bot_a >> 8;
  uint16_t bot_b = b << 8;
  bot_b = bot_b >> 8;
  uint32_t bot_sum = bot_a + bot_b;
  if(bot_sum >= 512){
     bot_sum -= 512;
  }//SUM[7:0]

  uint16_t mid_a = a >> 4;
  mid_a = mid_a << 8;
  mid_a = mid_a >> 8;
  uint16_t mid_b = b >> 4;
  mid_b = mid_b << 8;
  mid_b = mid_b >> 8;
  uint32_t mid_sum = mid_a + mid_b;
  if(mid_sum >= 512){
     mid_sum -= 512;
  }
  mid_sum = mid_sum >> 4;//SUM[11:8]

  uint16_t top_a = a >> 8;
  uint16_t top_b = b >> 8;
  uint32_t top_sum = top_a + top_b;
  top_sum = top_sum >> 4;
  return bot_sum + (mid_sum << 8) + (top_sum << 12);
};

uint32_t ref_add(uint16_t a, uint16_t b){
  return a+b;
};


int AC(){
  const uint32_t MAX_IN = 0xffffffff;
  std::vector<uint32_t> h;
  unsigned int N = 0xffff;
  srand((int)time(0));
  for(uint32_t i = 0; i < N; i++){
      uint16_t a=rand();
      uint16_t b=rand();// 1B times per second
      uint32_t ref=ref_add( (uint16_t)a, (uint16_t)b );
      uint32_t got=approx_add( (uint16_t)a, (uint16_t)b );
      int32_t  err=(int32_t)ref-(int32_t)got;
      err=abs(err);
      h.push_back(err); // We have seen one sample at error level err
  }
  double scale= 1.0/N;
  for(uint32_t index=0; index<MAX_IN; index++){
        std::cout.setf(std::ios::fixed);
        double p = h[index] * scale;
        std::cout<<std::fixed<<std::setprecision(5)<<"Pr[e="<<index<<"] = "<<p<<"\n";
  }

  return 0;

}
