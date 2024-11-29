/**
*******************************************************************************
* @file           : ring_buffer.c
* @brief          : Description of C implementation module
* @author         : Gonzalo Rivera
* @date           : 23/01/2023
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
/******************************************************************************
    Includes
******************************************************************************/
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "ring_buffer.h"
/******************************************************************************
    Defines and constants
******************************************************************************/

/******************************************************************************
    Data types
******************************************************************************/

/******************************************************************************
    Local variables
******************************************************************************/

/******************************************************************************
    Local function prototypes
******************************************************************************/

/******************************************************************************
    Local function definitions
******************************************************************************/

/******************************************************************************
    Public function definitions
******************************************************************************/
int ring_buffer_init(ring_buffer_t *buffer, void *buf, ring_buffer_size_t buf_size, ring_buffer_size_t element_size)
{
	if(RING_BUFFER_IS_POWER_OF_TWO(buf_size / element_size) == 0)
	{
		return -1;
	}

	if(buf_size % element_size != 0)
	{
		return -1;
	}

	buffer->buff = buf;
	buffer->buffer_byte_length = buf_size - 1;
	buffer->data_size = element_size;
	buffer->tail_index = 0;
	buffer->head_index = 0;

	return 0;
}

void ring_buffer_queue(ring_buffer_t *buffer, void *data)
{
	/* Is buffer full? */
	if(ring_buffer_is_full(buffer))
	{
		/* Is going to overwrite the oldest byte */
		/* Increase tail index */
		buffer->tail_index = ((buffer->tail_index + 1) & (buffer->buffer_byte_length / buffer->data_size));
	}

	/* Place data in buffer */
	memcpy(buffer->buff + buffer->head_index * buffer->data_size, data, buffer->data_size);
	buffer->head_index = ((buffer->head_index + 1) & (buffer->buffer_byte_length / buffer->data_size));
}

void ring_buffer_queue_arr(ring_buffer_t *buffer, const void *data, ring_buffer_size_t size)
{
	/* Add bytes; one by one */
	ring_buffer_size_t i;
	for(i = 0; i < size; i++)
	{
		ring_buffer_queue(buffer, &data + i * buffer->data_size);
	}
}

uint8_t ring_buffer_dequeue(ring_buffer_t *buffer, void *data)
{
	if(ring_buffer_is_empty(buffer))
	{
		/* No items */
		return 0;
	}

	memcpy(data, buffer->buff + buffer->tail_index * buffer->data_size, buffer->data_size);
	buffer->tail_index = ((buffer->tail_index + 1) & (buffer->buffer_byte_length / buffer->data_size));

	return 1;
}

ring_buffer_size_t ring_buffer_dequeue_arr(ring_buffer_t *buffer, void *data, ring_buffer_size_t len)
{
	uint16_t i = 0;

	if(ring_buffer_is_empty(buffer))
	{
		/* No items */
		return 0;
	}

	for(i = 0; i < len; i++)
	{
		if(1 != ring_buffer_dequeue(buffer, data + i * buffer->data_size))
		{
			break;
		}
	}

	return i;
}

uint8_t ring_buffer_peek(ring_buffer_t *buffer, void *data, ring_buffer_size_t index)
{
	if(index >= ring_buffer_num_items(buffer))
	{
		/* No items at index */
		return 0;
	}

	/* Add index to pointer */
	ring_buffer_size_t n = ((buffer->tail_index + index) & (buffer->buffer_byte_length / buffer->data_size));
	memcpy(data, buffer->buff + n * buffer->data_size, buffer->data_size);

	return 1;
}

extern inline uint8_t ring_buffer_is_empty(ring_buffer_t *buffer);
extern inline uint8_t ring_buffer_is_full(ring_buffer_t *buffer);
extern inline ring_buffer_size_t ring_buffer_num_items(ring_buffer_t *buffer);
