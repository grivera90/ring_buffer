/*
 * test_ring_buffer.c
 *
 *  Created on: 25 ene. 2023
 *      Author: Gonza
 */
#include "unity.h"
#include "../ring_buffer.h"
#include "../data_type_buffered.h"

void setUp(void)
{

}


void tearDown(void)
{

}

/**
 * Method under test: ring_buffer_init
 *
 * Scenario: null instance and length buffer not two pow
 *
 * Expected behavior: return -1 if buffer length isn't two pow.
 */
void test__ring_buffer_init__bad_buffer(void)
{
	can_msg_t can_msg[15];
	ring_buffer_t ring_buf = {0};
	int ret = 0; // its OK

	ret = ring_buffer_init(&ring_buf, can_msg, sizeof(can_msg), sizeof(can_msg_t));

	TEST_ASSERT_EQUAL_INT(-1, ret);
}

/**
 * Method under test: ring_buffer_init
 *
 * Scenario: buffer two pow but bad element size
 *
 * Expected behavior: return -1.
 */
void test__ring_buffer_init__bad_element_size(void)
{
	can_msg_t can_msg[16];
	ring_buffer_t ring_buf = {0};
	int ret = 0; // its OK

	ret = ring_buffer_init(&ring_buf, can_msg, sizeof(can_msg), 35);

	TEST_ASSERT_EQUAL_INT(-1, ret);
}

/**
 * Method under test: ring_buffer_init
 *
 * Scenario: good instance and length buffer two pow
 *
 * Expected behavior: return 0 all right
 */
void test__ring_buffer_init__good_parameters(void)
{
	can_msg_t can_msg[16];
	ring_buffer_t ring_buf = {0};
	int ret = 0; // its OK

	ret = ring_buffer_init(&ring_buf, can_msg, sizeof(can_msg), sizeof(can_msg_t));

	TEST_ASSERT_EQUAL_INT(0, ret);
	TEST_ASSERT_EQUAL_UINT32(sizeof(can_msg) - 1, ring_buf.buffer_byte_length);
	TEST_ASSERT_EQUAL_UINT32(sizeof(can_msg_t), ring_buf.data_size);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.tail_index);
}

void test__ring_buffer_queue__one_element(void)
{
	can_msg_t can_msg = {0};
	can_msg_t my_buffer[8] = {0,0,0,0,0,0,0,0};
	ring_buffer_t ring_buf = {0};
	int ret = 0; // its OK

	ret = ring_buffer_init(&ring_buf, my_buffer, sizeof(my_buffer), sizeof(can_msg_t));

	TEST_ASSERT_EQUAL_INT(0, ret);
	TEST_ASSERT_EQUAL_UINT32(sizeof(my_buffer) - 1, ring_buf.buffer_byte_length);
	TEST_ASSERT_EQUAL_UINT32(sizeof(can_msg_t), ring_buf.data_size);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.tail_index);

	can_msg.can_id = 0xAABBCCDD;
	can_msg.dlc = 8;
	can_msg.payload[0] = 0x01;
	can_msg.payload[1] = 0x02;
	can_msg.payload[2] = 0x03;
	can_msg.payload[3] = 0x04;
	can_msg.payload[4] = 0x05;
	can_msg.payload[5] = 0x06;
	can_msg.payload[6] = 0x07;
	can_msg.payload[7] = 0x08;

	ring_buffer_queue(&ring_buf, &can_msg);

	TEST_ASSERT_EQUAL_UINT32(1, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.tail_index);
}

void test__ring_buffer_dequeue__one_element(void)
{
	can_msg_t can_msg = {0};
	can_msg_t my_buffer[8] = {0,0,0,0,0,0,0,0};
	ring_buffer_t ring_buf = {0};
	int ret = 0; // its OK

	ret = ring_buffer_init(&ring_buf, my_buffer, sizeof(my_buffer), sizeof(can_msg_t));

	TEST_ASSERT_EQUAL_INT(0, ret);
	TEST_ASSERT_EQUAL_UINT32(sizeof(my_buffer) - 1, ring_buf.buffer_byte_length);
	TEST_ASSERT_EQUAL_UINT32(sizeof(can_msg_t), ring_buf.data_size);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.tail_index);

	can_msg.can_id = 0xAABBCCDD;
	can_msg.dlc = 8;
	can_msg.payload[0] = 0x01;
	can_msg.payload[1] = 0x02;
	can_msg.payload[2] = 0x03;
	can_msg.payload[3] = 0x04;
	can_msg.payload[4] = 0x05;
	can_msg.payload[5] = 0x06;
	can_msg.payload[6] = 0x07;
	can_msg.payload[7] = 0x08;

	ring_buffer_queue(&ring_buf, &can_msg);

	TEST_ASSERT_EQUAL_UINT32(1, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.tail_index);

	can_msg_t can_msg_aux = {0};

	ring_buffer_dequeue(&ring_buf, &can_msg_aux);

	TEST_ASSERT_EQUAL_UINT32(1, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(1, ring_buf.tail_index);
	TEST_ASSERT_EQUAL_UINT32(0xAABBCCDD, can_msg_aux.can_id);
	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux.dlc);
	TEST_ASSERT_EQUAL_UINT8(0x01, can_msg_aux.payload[0]);
	TEST_ASSERT_EQUAL_UINT8(0x02, can_msg_aux.payload[1]);
	TEST_ASSERT_EQUAL_UINT8(0x03, can_msg_aux.payload[2]);
	TEST_ASSERT_EQUAL_UINT8(0x04, can_msg_aux.payload[3]);
	TEST_ASSERT_EQUAL_UINT8(0x05, can_msg_aux.payload[4]);
	TEST_ASSERT_EQUAL_UINT8(0x06, can_msg_aux.payload[5]);
	TEST_ASSERT_EQUAL_UINT8(0x07, can_msg_aux.payload[6]);
	TEST_ASSERT_EQUAL_UINT8(0x08, can_msg_aux.payload[7]);
}

void test__ring_buffer_num_items__one_element(void)
{
	can_msg_t can_msg = {0};
	can_msg_t my_buffer[8] = {0,0,0,0,0,0,0,0};
	ring_buffer_t ring_buf = {0};
	int ret = 0; // its OK

	ret = ring_buffer_init(&ring_buf, my_buffer, sizeof(my_buffer), sizeof(can_msg_t));

	TEST_ASSERT_EQUAL_INT(0, ret);
	TEST_ASSERT_EQUAL_UINT32(sizeof(my_buffer) - 1, ring_buf.buffer_byte_length);
	TEST_ASSERT_EQUAL_UINT32(sizeof(can_msg_t), ring_buf.data_size);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.tail_index);

	can_msg.can_id = 0xAABBCCDD;
	can_msg.dlc = 8;
	can_msg.payload[0] = 0x01;
	can_msg.payload[1] = 0x02;
	can_msg.payload[2] = 0x03;
	can_msg.payload[3] = 0x04;
	can_msg.payload[4] = 0x05;
	can_msg.payload[5] = 0x06;
	can_msg.payload[6] = 0x07;
	can_msg.payload[7] = 0x08;

	ring_buffer_queue(&ring_buf, &can_msg);

	TEST_ASSERT_EQUAL_UINT32(1, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.tail_index);

	ring_buffer_size_t elements = ring_buffer_num_items(&ring_buf);

	TEST_ASSERT_EQUAL_UINT32(1, elements);

	can_msg_t can_msg_aux = {0};

	ring_buffer_dequeue(&ring_buf, &can_msg_aux);

	TEST_ASSERT_EQUAL_UINT32(1, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(1, ring_buf.tail_index);
	TEST_ASSERT_EQUAL_UINT32(0xAABBCCDD, can_msg_aux.can_id);
	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux.dlc);
	TEST_ASSERT_EQUAL_UINT8(0x01, can_msg_aux.payload[0]);
	TEST_ASSERT_EQUAL_UINT8(0x02, can_msg_aux.payload[1]);
	TEST_ASSERT_EQUAL_UINT8(0x03, can_msg_aux.payload[2]);
	TEST_ASSERT_EQUAL_UINT8(0x04, can_msg_aux.payload[3]);
	TEST_ASSERT_EQUAL_UINT8(0x05, can_msg_aux.payload[4]);
	TEST_ASSERT_EQUAL_UINT8(0x06, can_msg_aux.payload[5]);
	TEST_ASSERT_EQUAL_UINT8(0x07, can_msg_aux.payload[6]);
	TEST_ASSERT_EQUAL_UINT8(0x08, can_msg_aux.payload[7]);

	elements = ring_buffer_num_items(&ring_buf);

	TEST_ASSERT_EQUAL_UINT32(0, elements);
}

void test__ring_buffer_queue_dequeue__left_aproach(void)
{
	can_msg_t my_buffer[8] = {0,0,0,0,0,0,0,0};
	ring_buffer_t ring_buf = {0};
	int ret = 0; // its OK

	ret = ring_buffer_init(&ring_buf, my_buffer, sizeof(my_buffer), sizeof(can_msg_t));

	TEST_ASSERT_EQUAL_INT(0, ret);
	TEST_ASSERT_EQUAL_UINT32(sizeof(my_buffer) - 1, ring_buf.buffer_byte_length);
	TEST_ASSERT_EQUAL_UINT32(sizeof(can_msg_t), ring_buf.data_size);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.tail_index);

	can_msg_t can_msg[7] = {
			{
					.can_id = 1,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 2,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 3,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 4,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 5,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 6,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 7,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			}
	};

	ring_buffer_queue(&ring_buf, &can_msg[0]);
	ring_buffer_queue(&ring_buf, &can_msg[1]);
	ring_buffer_queue(&ring_buf, &can_msg[2]);
	ring_buffer_queue(&ring_buf, &can_msg[3]);
	ring_buffer_queue(&ring_buf, &can_msg[4]);
	ring_buffer_queue(&ring_buf, &can_msg[5]);
	ring_buffer_queue(&ring_buf, &can_msg[6]);

	TEST_ASSERT_EQUAL_UINT32(7, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.tail_index);

	ring_buffer_size_t elements = ring_buffer_num_items(&ring_buf);

	TEST_ASSERT_EQUAL_UINT32(7, elements);

	can_msg_t can_msg_aux[7] = {0};

	ring_buffer_dequeue(&ring_buf, &can_msg_aux[0]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[1]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[2]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[3]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[4]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[5]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[6]);

	TEST_ASSERT_EQUAL_UINT32(7, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(7, ring_buf.tail_index);

	elements = ring_buffer_num_items(&ring_buf);

	TEST_ASSERT_EQUAL_UINT32(0, elements);

	// check if the values is pre load be equal that dequeue values
	for(int i = 0; i < 7; i++)
	{
		TEST_ASSERT_EQUAL_UINT32(i + 1, can_msg_aux[i].can_id);
		TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[i].dlc);
		TEST_ASSERT_EQUAL_UINT8(0x01, can_msg_aux[i].payload[0]);
		TEST_ASSERT_EQUAL_UINT8(0x02, can_msg_aux[i].payload[1]);
		TEST_ASSERT_EQUAL_UINT8(0x03, can_msg_aux[i].payload[2]);
		TEST_ASSERT_EQUAL_UINT8(0x04, can_msg_aux[i].payload[3]);
		TEST_ASSERT_EQUAL_UINT8(0x05, can_msg_aux[i].payload[4]);
		TEST_ASSERT_EQUAL_UINT8(0x06, can_msg_aux[i].payload[5]);
		TEST_ASSERT_EQUAL_UINT8(0x07, can_msg_aux[i].payload[6]);
		TEST_ASSERT_EQUAL_UINT8(0x08, can_msg_aux[i].payload[7]);
	}
}

void test__ring_buffer_queue_dequeue__equal(void)
{
	can_msg_t my_buffer[8] = {0,0,0,0,0,0,0,0};
	ring_buffer_t ring_buf = {0};
	int ret = 0; // its OK

	ret = ring_buffer_init(&ring_buf, my_buffer, sizeof(my_buffer), sizeof(can_msg_t));

	TEST_ASSERT_EQUAL_INT(0, ret);
	TEST_ASSERT_EQUAL_UINT32(sizeof(my_buffer) - 1, ring_buf.buffer_byte_length);
	TEST_ASSERT_EQUAL_UINT32(sizeof(can_msg_t), ring_buf.data_size);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.tail_index);

	can_msg_t can_msg[8] = {
			{
					.can_id = 1,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 2,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 3,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 4,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 5,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 6,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 7,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 8,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			}
	};

	ring_buffer_queue(&ring_buf, &can_msg[0]);
	ring_buffer_queue(&ring_buf, &can_msg[1]);
	ring_buffer_queue(&ring_buf, &can_msg[2]);
	ring_buffer_queue(&ring_buf, &can_msg[3]);
	ring_buffer_queue(&ring_buf, &can_msg[4]);
	ring_buffer_queue(&ring_buf, &can_msg[5]);
	ring_buffer_queue(&ring_buf, &can_msg[6]);
	ring_buffer_queue(&ring_buf, &can_msg[7]);

	// TODO: to check values of index
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(1, ring_buf.tail_index);

	ring_buffer_size_t elements = ring_buffer_num_items(&ring_buf);

	TEST_ASSERT_EQUAL_UINT32(7, elements);

	can_msg_t can_msg_aux[8] = {0};
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[0]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[1]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[2]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[3]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[4]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[5]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[6]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[7]);

	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.tail_index);

	elements = ring_buffer_num_items(&ring_buf);

	TEST_ASSERT_EQUAL_UINT32(0, elements);

	// check if the values is pre load be equal that dequeue values.
	// should be start in index = 2 becouse in a ring buffer lost one byte to
	// operate with index head and tail.
	TEST_ASSERT_EQUAL_UINT32(2, can_msg_aux[0].can_id);
	TEST_ASSERT_EQUAL_UINT32(3, can_msg_aux[1].can_id);
	TEST_ASSERT_EQUAL_UINT32(4, can_msg_aux[2].can_id);
	TEST_ASSERT_EQUAL_UINT32(5, can_msg_aux[3].can_id);
	TEST_ASSERT_EQUAL_UINT32(6, can_msg_aux[4].can_id);
	TEST_ASSERT_EQUAL_UINT32(7, can_msg_aux[5].can_id);
	TEST_ASSERT_EQUAL_UINT32(8, can_msg_aux[6].can_id);
	// a partir de aqui no hay datos, devuelve el contenido con el que se inicializo.
	TEST_ASSERT_EQUAL_UINT32(0, can_msg_aux[7].can_id);

	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[0].dlc);
	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[1].dlc);
	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[2].dlc);
	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[3].dlc);
	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[4].dlc);
	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[5].dlc);
	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[6].dlc);
	// a partir de aqui no hay datos, devuelve el contenido con el que se inicializo.
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].dlc);

	for(int i = 0; i < 7; i++)
	{
		TEST_ASSERT_EQUAL_UINT8(0x01, can_msg_aux[i].payload[0]);
		TEST_ASSERT_EQUAL_UINT8(0x02, can_msg_aux[i].payload[1]);
		TEST_ASSERT_EQUAL_UINT8(0x03, can_msg_aux[i].payload[2]);
		TEST_ASSERT_EQUAL_UINT8(0x04, can_msg_aux[i].payload[3]);
		TEST_ASSERT_EQUAL_UINT8(0x05, can_msg_aux[i].payload[4]);
		TEST_ASSERT_EQUAL_UINT8(0x06, can_msg_aux[i].payload[5]);
		TEST_ASSERT_EQUAL_UINT8(0x07, can_msg_aux[i].payload[6]);
		TEST_ASSERT_EQUAL_UINT8(0x08, can_msg_aux[i].payload[7]);
	}

	// a partir de aqui no hay datos, devuelve el contenido con el que se inicializo.
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[0]);
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[1]);
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[2]);
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[3]);
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[4]);
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[5]);
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[6]);
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[7]);
}

void test__ring_buffer_queue_dequeue__overflow(void)
{
	can_msg_t my_buffer[8] = {0,0,0,0,0,0,0,0};
	ring_buffer_t ring_buf = {0};
	int ret = 0; // its OK

	ret = ring_buffer_init(&ring_buf, my_buffer, sizeof(my_buffer), sizeof(can_msg_t));

	TEST_ASSERT_EQUAL_INT(0, ret);
	TEST_ASSERT_EQUAL_UINT32(sizeof(my_buffer) - 1, ring_buf.buffer_byte_length);
	TEST_ASSERT_EQUAL_UINT32(sizeof(can_msg_t), ring_buf.data_size);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(0, ring_buf.tail_index);

	can_msg_t can_msg[9] = {
			{
					.can_id = 1,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 2,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 3,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 4,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 5,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 6,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 7,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 8,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			},
			{
					.can_id = 9,
					.dlc = 8,
					.payload[0] = 0x01,
					.payload[1] = 0x02,
					.payload[2] = 0x03,
					.payload[3] = 0x04,
					.payload[4] = 0x05,
					.payload[5] = 0x06,
					.payload[6] = 0x07,
					.payload[7] = 0x08
			}
	};

	ring_buffer_queue(&ring_buf, &can_msg[0]);
	ring_buffer_queue(&ring_buf, &can_msg[1]);
	ring_buffer_queue(&ring_buf, &can_msg[2]);
	ring_buffer_queue(&ring_buf, &can_msg[3]);
	ring_buffer_queue(&ring_buf, &can_msg[4]);
	ring_buffer_queue(&ring_buf, &can_msg[5]);
	ring_buffer_queue(&ring_buf, &can_msg[6]);
	ring_buffer_queue(&ring_buf, &can_msg[7]);
	ring_buffer_queue(&ring_buf, &can_msg[8]);

	// TODO: to check values of index
	TEST_ASSERT_EQUAL_UINT32(1, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(2, ring_buf.tail_index);

	ring_buffer_size_t elements = ring_buffer_num_items(&ring_buf);
	// para un buffer de 8 elementos siempre deberían haber 7 elementos disponibles
	TEST_ASSERT_EQUAL_UINT32(7, elements);

	can_msg_t can_msg_aux[8] = {0};
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[0]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[1]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[2]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[3]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[4]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[5]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[6]);
	ring_buffer_dequeue(&ring_buf, &can_msg_aux[7]);

	TEST_ASSERT_EQUAL_UINT32(1, ring_buf.head_index);
	TEST_ASSERT_EQUAL_UINT32(1, ring_buf.tail_index);

	elements = ring_buffer_num_items(&ring_buf);

	TEST_ASSERT_EQUAL_UINT32(0, elements);

	// check if the values is pre load be equal that dequeue values.
	// should be start in index = 2 becouse in a ring buffer lost one byte to
	// operate with index head and tail.
	TEST_ASSERT_EQUAL_UINT32(3, can_msg_aux[0].can_id);
	TEST_ASSERT_EQUAL_UINT32(4, can_msg_aux[1].can_id);
	TEST_ASSERT_EQUAL_UINT32(5, can_msg_aux[2].can_id);
	TEST_ASSERT_EQUAL_UINT32(6, can_msg_aux[3].can_id);
	TEST_ASSERT_EQUAL_UINT32(7, can_msg_aux[4].can_id);
	TEST_ASSERT_EQUAL_UINT32(8, can_msg_aux[5].can_id);
	TEST_ASSERT_EQUAL_UINT32(9, can_msg_aux[6].can_id);
	// a partir de aqui no hay datos, devuelve el contenido con el que se inicializo.
	TEST_ASSERT_EQUAL_UINT32(0, can_msg_aux[7].can_id);

	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[0].dlc);
	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[1].dlc);
	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[2].dlc);
	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[3].dlc);
	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[4].dlc);
	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[5].dlc);
	TEST_ASSERT_EQUAL_UINT8(8, can_msg_aux[6].dlc);
	// a partir de aqui no hay datos, devuelve el contenido con el que se inicializo.
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].dlc);

	for(int i = 0; i < 7; i++)
	{
		TEST_ASSERT_EQUAL_UINT8(0x01, can_msg_aux[i].payload[0]);
		TEST_ASSERT_EQUAL_UINT8(0x02, can_msg_aux[i].payload[1]);
		TEST_ASSERT_EQUAL_UINT8(0x03, can_msg_aux[i].payload[2]);
		TEST_ASSERT_EQUAL_UINT8(0x04, can_msg_aux[i].payload[3]);
		TEST_ASSERT_EQUAL_UINT8(0x05, can_msg_aux[i].payload[4]);
		TEST_ASSERT_EQUAL_UINT8(0x06, can_msg_aux[i].payload[5]);
		TEST_ASSERT_EQUAL_UINT8(0x07, can_msg_aux[i].payload[6]);
		TEST_ASSERT_EQUAL_UINT8(0x08, can_msg_aux[i].payload[7]);
	}

	// a partir de aqui no hay datos, devuelve el contenido con el que se inicializo.
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[0]);
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[1]);
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[2]);
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[3]);
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[4]);
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[5]);
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[6]);
	TEST_ASSERT_EQUAL_UINT8(0, can_msg_aux[7].payload[7]);
}

