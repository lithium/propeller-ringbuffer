
#include "ringbuffer.h"


typedef struct {
  uint32_t foo;
  uint8_t bar;
} TestStruct;
  

#define TEST_BUF_SIZE 8
TestStruct structbuffer[TEST_BUF_SIZE];
RingBuffer ringbuff;

uint32_t stack[40+25];

void producer();
void consumer();

int main() {
  
  RingBuffer_init(&ringbuff, structbuffer, sizeof(TestStruct), TEST_BUF_SIZE);
    
  // start cog1 as the producer
  cogstart(&producer, NULL, stack, sizeof(stack));
  
  // turn cog0 into the consumer
  consumer();
}  


void producer() {
  TestStruct newStruct;
  uint32_t fooCounter = 0;
  uint8_t barCounter = 0;

  volatile unsigned int wait_time = CLKFREQ/20;
  unsigned int nextcnt = wait_time + CNT;
  
  while (1) {
    
    newStruct.foo = fooCounter++;
    newStruct.bar = barCounter--;
    RingBuffer_enqueue(&ringbuff, &newStruct);

    nextcnt = waitcnt2(nextcnt, wait_time);

  }    
  
  
}

void consumer() {
  TestStruct s;
  
  while (1) {
    
    while (RingBuffer_dequeue(&ringbuff, &s) != 0) { /* spinlock */ }

    printf("foo=%d bar=%d\n", s.foo, s.bar);
    
  }    
  
}    
