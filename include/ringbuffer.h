
#ifndef RINGBUFFER_H
#define RINGBUFFER_H


#include "propeller.h"



typedef struct ringbuffer_t {
  uint32_t *buffer;             // buffer should be sizeof(uint32)*buffer_capacity bytes
  uint8_t buffer_capacity;    
  uint8_t in,out;
  uint8_t queue_count;          // number of entries currently enqueued

  int lockId;
} RingBuffer;



/* Initialize a new RingBuffer. 
 *
 *  Returns
 *   0 - Success
 */
int RingBuffer_init(RingBuffer *rbuf, uint32_t *buffer, uint8_t buffer_capacity);
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
