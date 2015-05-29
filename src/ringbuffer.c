#include "ringbuffer.h"

int RingBuffer_init(RingBuffer *rbuf, uint32_t *buffer, uint8_t buffer_capacity)
{
  rbuf->buffer = buffer;
  rbuf->buffer_capacity = buffer_capacity;

  rbuf->in = rbuf->out = 0;

  rbuf->lockId = locknew();

  return 0;
}


void RingBuffer_destroy(RingBuffer *rbuf) {
  lockret(rbuf->lockId);
}

void RingBuffer_enqueue(RingBuffer *rbuf, void *entry)
{
  while (lockset(rbuf->lockId) != 0) { /*spin lock*/ }

  rbuf->buffer[rbuf->in++ % rbuf->buffer_capacity] = *(uint32_t*)entry;
  rbuf->queue_count++;

  lockclr(rbuf->lockId);
}


int RingBuffer_dequeue(RingBuffer *rbuf, void *dest)
{
  if (rbuf->queue_count < 1) {
    return 1;
  }

  while (lockset(rbuf->lockId) != 0) { /*spin lock*/ }

  *(uint32_t*)dest = rbuf->buffer[rbuf->out++ % rbuf->buffer_capacity];
  rbuf->queue_count--;

  lockclr(rbuf->lockId);

  return 0;
}
