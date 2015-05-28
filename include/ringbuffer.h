
#ifndef RINGBUFFER_H
#define RINGBUFFER_H


#include "propeller.h"



typedef struct ringbuffer_t {
  void *buffer;            // buffer should be entry_size*buffer_capacity bytes
  uint8_t entry_size;       // size of each individual entry
  uint8_t buffer_capacity;  // number of entries
  uint8_t in,out;

  uint8_t queue_count;      // number of entries currently enqueued

  int lockId;
} RingBuffer;



/* Initialize a new RingBuffer. 
 *
 *  Returns
 *   0 - Success
 */
int RingBuffer_init(RingBuffer *rbuf, void *buffer, uint8_t entry_size, uint8_t buffer_capacity);
void RingBuffer_destroy(RingBuffer *rbuf);


/* Synchronized put, will overwrite oldest entry if full */
void RingBuffer_enqueue(RingBuffer *rbuf, void *entry);

/* Synchronized get, dest must point to entry_size bytes 
 *
 * Returns
     0 - Success, new entry present at dest
     1 - Failure, queue is empty. dest undefined
 */
int RingBuffer_dequeue(RingBuffer *rbuf, void *dest);


#endif