/**
*******************************************************************************
* @file           : ring_buffer.h
* @brief          : Description of header file
* @author         : https://github.com/AndersKaloer/Ring-Buffer, some customs
* @date           : 23/01/2023
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__
/******************************************************************************
        Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
/******************************************************************************
        Constants
 ******************************************************************************/
#define RING_BUFFER_ASSERT(x) assert(x)

/**
 * Checks if the buffer_size is a power of two.
 * Due to the design only <tt> RING_BUFFER_SIZE-1 </tt> items
 * can be contained in the buffer.
 * buffer_size must be a power of two.
*/
#define RING_BUFFER_IS_POWER_OF_TWO(buffer_size) ((buffer_size & (buffer_size - 1)) == 0)

/**
 * Used as a modulo operator
 * as <tt> a % b = (a & (b − 1)) </tt>
 * where \c a is a positive index in the buffer and
 * \c b is the (power of two) size of the buffer.
 */
#define RING_BUFFER_MASK(rb) (rb->buffer_byte_length / rb->data_size)

/******************************************************************************
        Data types
 ******************************************************************************/
typedef enum
{
	BUFFER_EMPTY = 0,
	BUFFER_FULL
}ring_buffer_sts_t;

/**
 * The type which is used to hold the size
 * and the indicies of the buffer.
 */
typedef volatile uint32_t ring_buffer_size_t;

/**
 * Structure which holds a ring buffer.
 * The buffer contains a buffer array
 * as well as metadata for the ring buffer.
 */
typedef struct
{
	/** Buffer memory. */
	void *buff;
	/** Size of element to store */
	ring_buffer_size_t data_size;
	/** Buffer mask. */
	ring_buffer_size_t buffer_byte_length;
	/** Index of tail. */
	ring_buffer_size_t tail_index;
	/** Index of head. */
	ring_buffer_size_t head_index;

}ring_buffer_t;

/******************************************************************************
        Public function prototypes
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initializes the ring buffer pointed to by <em>buffer</em>.
 * This function can also be used to empty/reset the buffer.
 * @param buffer The ring buffer to initialize.
 * @param buf The buffer allocated for the ringbuffer.
 * @param buf_size The size of the allocated ringbuffer.
 */
int ring_buffer_init(ring_buffer_t *buffer, void *buf, ring_buffer_size_t buf_size, ring_buffer_size_t element_size);

/**
 * Adds a byte to a ring buffer.
 * @param buffer The buffer in which the data should be placed.
 * @param data The byte to place.
 */
void ring_buffer_queue(ring_buffer_t *buffer, void *data);

/**
 * Adds an array of bytes to a ring buffer.
 * @param buffer The buffer in which the data should be placed.
 * @param data A pointer to the array of bytes to place in the queue.
 * @param size The size of the array.
 */
void ring_buffer_queue_arr(ring_buffer_t *buffer, const void *data, ring_buffer_size_t size);

/**
 * Returns the oldest byte in a ring buffer.
 * @param buffer The buffer from which the data should be returned.
 * @param data A pointer to the location at which the data should be placed.
 * @return 1 if data was returned; 0 otherwise.
 */
uint8_t ring_buffer_dequeue(ring_buffer_t *buffer, void *data);

/**
 * Returns the <em>len</em> oldest bytes in a ring buffer.
 * @param buffer The buffer from which the data should be returned.
 * @param data A pointer to the array at which the data should be placed.
 * @param len The maximum number of bytes to return.
 * @return The number of bytes returned.
 */
ring_buffer_size_t ring_buffer_dequeue_arr(ring_buffer_t *buffer, void *data, ring_buffer_size_t len);
/**
 * Peeks a ring buffer, i.e. returns an element without removing it.
 * @param buffer The buffer from which the data should be returned.
 * @param data A pointer to the location at which the data should be placed.
 * @param index The index to peek.
 * @return 1 if data was returned; 0 otherwise.
 */
uint8_t ring_buffer_peek(ring_buffer_t *buffer, void *data, ring_buffer_size_t index);

/**
 * Returns whether a ring buffer is empty.
 * @param buffer The buffer for which it should be returned whether it is empty.
 * @return 1 if empty; 0 otherwise.
 */
inline uint8_t ring_buffer_is_empty(ring_buffer_t *buffer)
{
	return (buffer->head_index == buffer->tail_index);
}

/**
 * Returns whether a ring buffer is full.
 * @param buffer The buffer for which it should be returned whether it is full.
 * @return 1 if full; 0 otherwise.
 */
inline uint8_t ring_buffer_is_full(ring_buffer_t *buffer)
{
	return ((buffer->head_index  - buffer->tail_index) & (buffer->buffer_byte_length / buffer->data_size)) == (buffer->buffer_byte_length / buffer->data_size);
}

/**
 * Returns the number of items in a ring buffer.
 * @param buffer The buffer for which the number of items should be returned.
 * @return The number of items in the ring buffer.
 */
inline ring_buffer_size_t ring_buffer_num_items(ring_buffer_t *buffer)
{
	return (buffer->head_index - buffer->tail_index) & (buffer->buffer_byte_length / buffer->data_size);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // EOF __RING_BUFFER_H__
