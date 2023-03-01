/*
 ============================================================================
 Name        : ring_buffer.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "../ring_buffer_module/ring_buffer.h"
#include "../ring_buffer_module/data_type_buffered.h"

int main(void)
{

#if 0
	int i, cnt;
	char tmp;
	char tmp_arr[50];

	/* Create and initialize ring buffer */
	ring_buffer_t ring_buffer;
	char buf_arr[128];
	ring_buffer_init(&ring_buffer, buf_arr, sizeof(buf_arr));

	/* Add elements to buffer; one at a time */
	for(i = 0; i < 100; i++) {
		ring_buffer_queue(&ring_buffer, i);
	}

	/* Verify size */
	assert(ring_buffer_num_items(&ring_buffer) == 100);

	/* Peek third element */
	cnt = ring_buffer_peek(&ring_buffer, &tmp, 3);
	/* Assert byte returned */
	assert(cnt == 1);
	/* Assert contents */
	assert(tmp == 3);

	/* Dequeue all elements */
	for(cnt = 0; ring_buffer_dequeue(&ring_buffer, &tmp) > 0; cnt++) {
		/* Do something with buf... */
		assert(tmp == cnt);
		printf("Read: %d\n", tmp);
	}
	printf("\n===============\n");

	/* Add array */
	ring_buffer_queue_arr(&ring_buffer, "Hello, Ring Buffer!", 20);

	/* Is buffer empty? */
	assert(!ring_buffer_is_empty(&ring_buffer));

	/* Dequeue all elements */
	while(ring_buffer_dequeue(&ring_buffer, &tmp) > 0) {
		/* Print contents */
		printf("Read: %c\n", tmp);
	}

	/* Add new array */
	ring_buffer_queue_arr(&ring_buffer, "Hello again, Ring Buffer!", 26);

	/* Dequeue array in two parts */
	printf("Read:\n");
	cnt = ring_buffer_dequeue_arr(&ring_buffer, tmp_arr, 13);
	printf("%d\n", cnt);
	assert(cnt == 13);
	/* Add \0 termination before printing */
	tmp_arr[13] = '\0';
	printf("%s\n", tmp_arr);
	/* Dequeue remaining */
	cnt = ring_buffer_dequeue_arr(&ring_buffer, tmp_arr, 13);
	assert(cnt == 13);
	printf("%s", tmp_arr);


	printf("\n===============\n");

	/* Overfill buffer */
	for(i = 0; i < 1000; i++) {
		ring_buffer_queue(&ring_buffer, (i % 127));
	}

	/* Is buffer full? */
	if(ring_buffer_is_full(&ring_buffer)) {
		cnt = ring_buffer_num_items(&ring_buffer);
		printf("Buffer is full and contains %d bytes\n", cnt);
	}

	/* Dequeue all elements */
	while(ring_buffer_dequeue(&ring_buffer, &tmp) > 0) {
		/* Print contents */
		printf("Read: 0x%02x\n", tmp);
	}
#else

	can_msg_t can_msg_arr[10] = {
			{
					.can_id = 1,
					.dlc = 1,
					.payload[0] = 0xAA
			},
			{
					.can_id = 2,
					.dlc = 1,
					.payload[0] = 0xBB
			},
			{
					.can_id = 3,
					.dlc = 1,
					.payload[0] = 0xCC
			},
			{
					.can_id = 4,
					.dlc = 1,
					.payload[0] = 0xDD
			},
			{
					.can_id = 5,
					.dlc = 1,
					.payload[0] = 0xEE
			},
			{
					.can_id = 6,
					.dlc = 1,
					.payload[0] = 0xFF
			},
			{
					.can_id = 7,
					.dlc = 1,
					.payload[0] = 0xAA
			},
			{
					.can_id = 8,
					.dlc = 1,
					.payload[0] = 0xBB
			},
			{
					.can_id = 9,
					.dlc = 1,
					.payload[0] = 0xCC
			},
			{
					.can_id = 10,
					.dlc = 1,
					.payload[0] = 0xDD
			}
	};

	can_msg_t can_msg_aux;
	can_msg_t mybuffer[8];

	ring_buffer_t ring_buffer;
	uint16_t cnt = 0;
	uint16_t i = 0;

	ring_buffer_init(&ring_buffer, &mybuffer[0], sizeof(mybuffer), sizeof(can_msg_t));
	printf("Se unicializa el buffer con un maximo de:\n");
	printf("largo en bytes: %d\n", ring_buffer.buffer_byte_length);
	printf("largo del dato en bytes: %d\n", ring_buffer.data_size);
	printf("Cantidad de elementos que entrarian: %d\n\n", (int)(sizeof(mybuffer) / sizeof(can_msg_t)));

	printf("datos de la estructura ring_buffer:\n\n");
	printf("- Index head: %d\n", ring_buffer.head_index);
	printf("- Index tail: %d\n", ring_buffer.tail_index);
	printf("- Buffer byte length: %d\n", ring_buffer.buffer_byte_length);

	if(ring_buffer_is_full(&ring_buffer))
	{
		printf("- Buffer lleno\n");
	}
	else
	{
		printf("- Buffer no esta lleno\n");
	}

	if(ring_buffer_is_empty(&ring_buffer))
	{
		printf("- Buffer vacio\n");
	}
	else
	{
		printf("- Buffer no esta vacio\n");
	}

	printf("\nSe cargan los datos en el buffer:\n\n");

	/* Add elements to buffer; one at a time */
	for(i = 0; i < 8; i++)
	{
		ring_buffer_queue(&ring_buffer, &can_msg_arr[i]);
		printf("- Index head: %d\n", ring_buffer.head_index);
		printf("- Index tail: %d\n", ring_buffer.tail_index);
		printf("- Elements: %d\n", ring_buffer_num_items(&ring_buffer));
		printf("- Buffer byte length: %d\n", ring_buffer.buffer_byte_length);
		getchar();
	}

	if(ring_buffer_is_full(&ring_buffer))
	{
		printf("- Buffer lleno\n");
	}
	else
	{
		printf("- Buffer no esta lleno\n");
	}

	if(ring_buffer_is_empty(&ring_buffer))
	{
		printf("- Buffer vacio\n");
	}
	else
	{
		printf("- Buffer no esta vacio\n");
	}

//	getchar();

//	printf("\nSe saca un dato del buffer\n");
//
//	printf("- Index head: %d\n", ring_buffer.head_index);
//	printf("- Index tail: %d\n", ring_buffer.tail_index);
//	printf("- Elements: %d\n", ring_buffer_num_items(&ring_buffer));
//	printf("- Buffer byte length: %d\n", ring_buffer.buffer_byte_length);
//
//	ring_buffer_dequeue(&ring_buffer, &can_msg_aux);
//
//	printf("\n===============\n");
//	printf("can_msg:\n");
//	printf("\tcan_id: %X\n", can_msg_aux.can_id);
//	printf("\tdlc: %d\n", can_msg_aux.dlc);
//	printf("\tpayload[0]: 0x%X\n", can_msg_aux.payload[0]);
//	printf("\n===============\n");
//
//	printf("- Index head: %d\n", ring_buffer.head_index);
//	printf("- Index tail: %d\n", ring_buffer.tail_index);
//	printf("- Elements: %d\n", ring_buffer_num_items(&ring_buffer));
//	printf("- Buffer byte length: %d\n", ring_buffer.buffer_byte_length);

//	int pos = 0;
//	printf("Se saca un dato de la posicion %d:\n", pos);
//	if(0 != ring_buffer_peek(&ring_buffer, &can_msg_aux, pos))
//	{
//		printf("\n===============\n");
//		printf("can_msg[%d]:\n", pos);
//		printf("\tcan_id: %X\n", can_msg_aux.can_id);
//		printf("\tdlc: %d\n", can_msg_aux.dlc);
//		printf("\tpayload[0]: 0x%X\n", can_msg_aux.payload[0]);
//		printf("\n===============\n");
//	}
//
//	printf("- Index head: %d\n", ring_buffer.head_index);
//	printf("- Index tail: %d\n", ring_buffer.tail_index);
//	printf("- Elements: %d\n", ring_buffer_num_items(&ring_buffer));
//	printf("- Buffer byte length: %d\n", ring_buffer.buffer_byte_length);

	getchar();
	can_msg_t can_arr[8] = {0};
	printf("Se sacan todos los datos del buffer:\n\n");
	for(int x = 0; x < 8; x++)
	{
		ring_buffer_dequeue(&ring_buffer, &can_arr[x]);
		printf("can_msg[%d]:\n", x);
		printf("\tcan_id: %X\n", can_arr[x].can_id);
		printf("\tdlc: %d\n", can_arr[x].dlc);
		printf("\tpayload[0]: 0x%X\n", can_arr[x].payload[0]);
		printf("\n===============\n");
		printf("Quedan %d elementos\n", ring_buffer_num_items(&ring_buffer));
		printf("\n===============\n");
		printf("- Index head: %d\n", ring_buffer.head_index);
		printf("- Index tail: %d\n", ring_buffer.tail_index);
		printf("\n===============\n");
		getchar();
	}

//	printf("Se sacan todos los datos del buffer:\n\n");
//	while(1 == ring_buffer_dequeue(&ring_buffer, &can_msg_aux))
//	{
//		printf("can_msg[%d]:\n", cnt++);
//		printf("\tcan_id: %X\n", can_msg_aux.can_id);
//		printf("\tdlc: %d\n", can_msg_aux.dlc);
//		printf("\tpayload[0]: 0x%X\n", can_msg_aux.payload[0]);
//		printf("\n===============\n");
//		printf("Quedan %d elementos\n", ring_buffer_num_items(&ring_buffer));
//		getchar();
//	}

	printf("- Index head: %d\n", ring_buffer.head_index);
	printf("- Index tail: %d\n", ring_buffer.tail_index);
	printf("- Elements: %d\n", ring_buffer_num_items(&ring_buffer));
	printf("- Buffer byte length: %d\n", ring_buffer.buffer_byte_length);

	if(ring_buffer_is_full(&ring_buffer))
	{
		printf("- Buffer lleno\n");
	}
	else
	{
		printf("- Buffer no esta lleno\n");
	}

	if(ring_buffer_is_empty(&ring_buffer))
	{
		printf("- Buffer vacio\n");
	}
	else
	{
		printf("- Buffer no esta vacio\n");
	}

	getchar();

	printf("Se carga un array en el buffer:\n\n");

	ring_buffer_queue_arr(&ring_buffer, can_msg_arr, 10);

	printf("- Index head: %d\n", ring_buffer.head_index);
	printf("- Index tail: %d\n", ring_buffer.tail_index);
	printf("- Elements: %d\n", ring_buffer_num_items(&ring_buffer));
	printf("- Buffer byte length: %d\n", ring_buffer.buffer_byte_length);

	if(ring_buffer_is_full(&ring_buffer))
	{
		printf("- Buffer lleno\n");
	}
	else
	{
		printf("- Buffer no esta lleno\n");
	}

	if(ring_buffer_is_empty(&ring_buffer))
	{
		printf("- Buffer vacio\n");
	}
	else
	{
		printf("- Buffer no esta vacio\n");
	}

	getchar();

	printf("\nSe eliminan los datos dentro del buffer:\n\n");
	ring_buffer_dequeue_arr(&ring_buffer, mybuffer, 10);

	printf("- Index head: %d\n", ring_buffer.head_index);
	printf("- Index tail: %d\n", ring_buffer.tail_index);
	printf("- Elements: %d\n", ring_buffer_num_items(&ring_buffer));
	printf("- Buffer byte length: %d\n", ring_buffer.buffer_byte_length);

	if(ring_buffer_is_full(&ring_buffer))
	{
		printf("- Buffer lleno\n");
	}
	else
	{
		printf("- Buffer no esta lleno\n");
	}

	if(ring_buffer_is_empty(&ring_buffer))
	{
		printf("- Buffer vacio\n");
	}
	else
	{
		printf("- Buffer no esta vacio\n");
	}

	getchar();

#endif
	return EXIT_SUCCESS;
}
