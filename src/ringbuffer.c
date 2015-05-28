#include "ringbuffer.h"

int RingBuffer_init(RingBuffer *rbuf, void *buffer, uint8_t entry_size, uint8_t buffer_capacity)
{
  rbuf->buffer = buffer;
  rbuf->entry_size = entry_size;
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

  memcpy(rbuf->buffer+(rbuf->in*rbuf->entry_size), entry, rbuf->entry_size);
  rbuf->queue_count++;
  if (++rbuf->in == rbuf->buffer_capacity) {
    rbuf->in = 0;
  }

  lockclr(rbuf->lockId);
}


int RingBuffer_dequeue(RingBuffer *rbuf, void *dest)
{
  if (rbuf->queue_count < 1) {
    return 1;
  }

  while (lockset(rbuf->lockId) != 0) { /*spin lock*/ }

  memcpy(dest, rbuf->buffer+(rbuf->out*rbuf->entry_size), rbuf->entry_size);
  rbuf->queue_count--;
  if (++rbuf->out == rbuf->buffer_capacity) {
    rbuf->out = 0;
  }

  lockclr(rbuf->lockId);

  return 0;
}
