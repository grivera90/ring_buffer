#include "test/../data_type_buffered.h"
#include "test/../ring_buffer.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"














void setUp(void)

{



}





void tearDown(void)

{



}

void test__ring_buffer_init__bad_buffer(void)

{

 can_msg_t can_msg[15];

 ring_buffer_t ring_buf = {0};

 int ret = 0;



 ret = ring_buffer_init(&ring_buf, can_msg, sizeof(can_msg), sizeof(can_msg_t));



 UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((ret)), (

((void *)0)

), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_INT);

}

void test__ring_buffer_init__bad_element_size(void)

{

 can_msg_t can_msg[16];

 ring_buffer_t ring_buf = {0};

 int ret = 0;



 ret = ring_buffer_init(&ring_buf, can_msg, sizeof(can_msg), 35);



 UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((ret)), (

((void *)0)

), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_INT);

}

void test__ring_buffer_init__good_parameters(void)

{

 can_msg_t can_msg[16];

 ring_buffer_t ring_buf = {0};

 int ret = 0;



 ret = ring_buffer_init(&ring_buf, can_msg, sizeof(can_msg), sizeof(can_msg_t));



 UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((ret)), (

((void *)0)

), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((sizeof(can_msg) - 1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.buffer_byte_length)), (

((void *)0)

), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((sizeof(can_msg_t))), (UNITY_INT)(UNITY_UINT32)((ring_buf.data_size)), (

((void *)0)

), (UNITY_UINT)(75), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(77), UNITY_DISPLAY_STYLE_UINT32);

}



void test__ring_buffer_queue__one_element(void)

{

 can_msg_t can_msg = {0};

 can_msg_t my_buffer[8] = {0,0,0,0,0,0,0,0};

 ring_buffer_t ring_buf = {0};

 int ret = 0;



 ret = ring_buffer_init(&ring_buf, my_buffer, sizeof(my_buffer), sizeof(can_msg_t));



 UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((ret)), (

((void *)0)

), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((sizeof(my_buffer) - 1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.buffer_byte_length)), (

((void *)0)

), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((sizeof(can_msg_t))), (UNITY_INT)(UNITY_UINT32)((ring_buf.data_size)), (

((void *)0)

), (UNITY_UINT)(91), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(92), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(93), UNITY_DISPLAY_STYLE_UINT32);



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



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(108), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(109), UNITY_DISPLAY_STYLE_UINT32);

}



void test__ring_buffer_dequeue__one_element(void)

{

 can_msg_t can_msg = {0};

 can_msg_t my_buffer[8] = {0,0,0,0,0,0,0,0};

 ring_buffer_t ring_buf = {0};

 int ret = 0;



 ret = ring_buffer_init(&ring_buf, my_buffer, sizeof(my_buffer), sizeof(can_msg_t));



 UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((ret)), (

((void *)0)

), (UNITY_UINT)(121), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((sizeof(my_buffer) - 1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.buffer_byte_length)), (

((void *)0)

), (UNITY_UINT)(122), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((sizeof(can_msg_t))), (UNITY_INT)(UNITY_UINT32)((ring_buf.data_size)), (

((void *)0)

), (UNITY_UINT)(123), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(124), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(125), UNITY_DISPLAY_STYLE_UINT32);



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



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(140), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(141), UNITY_DISPLAY_STYLE_UINT32);



 can_msg_t can_msg_aux = {0};



 ring_buffer_dequeue(&ring_buf, &can_msg_aux);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(147), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(148), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0xAABBCCDD)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux.can_id)), (

((void *)0)

), (UNITY_UINT)(149), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.dlc)), (

((void *)0)

), (UNITY_UINT)(150), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x01)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[0])), (

((void *)0)

), (UNITY_UINT)(151), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x02)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[1])), (

((void *)0)

), (UNITY_UINT)(152), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x03)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[2])), (

((void *)0)

), (UNITY_UINT)(153), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x04)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[3])), (

((void *)0)

), (UNITY_UINT)(154), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x05)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[4])), (

((void *)0)

), (UNITY_UINT)(155), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x06)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[5])), (

((void *)0)

), (UNITY_UINT)(156), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x07)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[6])), (

((void *)0)

), (UNITY_UINT)(157), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x08)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[7])), (

((void *)0)

), (UNITY_UINT)(158), UNITY_DISPLAY_STYLE_UINT8);

}



void test__ring_buffer_num_items__one_element(void)

{

 can_msg_t can_msg = {0};

 can_msg_t my_buffer[8] = {0,0,0,0,0,0,0,0};

 ring_buffer_t ring_buf = {0};

 int ret = 0;



 ret = ring_buffer_init(&ring_buf, my_buffer, sizeof(my_buffer), sizeof(can_msg_t));



 UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((ret)), (

((void *)0)

), (UNITY_UINT)(170), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((sizeof(my_buffer) - 1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.buffer_byte_length)), (

((void *)0)

), (UNITY_UINT)(171), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((sizeof(can_msg_t))), (UNITY_INT)(UNITY_UINT32)((ring_buf.data_size)), (

((void *)0)

), (UNITY_UINT)(172), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(173), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(174), UNITY_DISPLAY_STYLE_UINT32);



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



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(189), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(190), UNITY_DISPLAY_STYLE_UINT32);



 ring_buffer_size_t elements = ring_buffer_num_items(&ring_buf);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((elements)), (

((void *)0)

), (UNITY_UINT)(194), UNITY_DISPLAY_STYLE_UINT32);



 can_msg_t can_msg_aux = {0};



 ring_buffer_dequeue(&ring_buf, &can_msg_aux);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(200), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(201), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0xAABBCCDD)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux.can_id)), (

((void *)0)

), (UNITY_UINT)(202), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.dlc)), (

((void *)0)

), (UNITY_UINT)(203), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x01)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[0])), (

((void *)0)

), (UNITY_UINT)(204), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x02)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[1])), (

((void *)0)

), (UNITY_UINT)(205), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x03)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[2])), (

((void *)0)

), (UNITY_UINT)(206), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x04)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[3])), (

((void *)0)

), (UNITY_UINT)(207), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x05)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[4])), (

((void *)0)

), (UNITY_UINT)(208), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x06)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[5])), (

((void *)0)

), (UNITY_UINT)(209), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x07)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[6])), (

((void *)0)

), (UNITY_UINT)(210), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x08)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux.payload[7])), (

((void *)0)

), (UNITY_UINT)(211), UNITY_DISPLAY_STYLE_UINT8);



 elements = ring_buffer_num_items(&ring_buf);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((elements)), (

((void *)0)

), (UNITY_UINT)(215), UNITY_DISPLAY_STYLE_UINT32);

}



void test__ring_buffer_queue_dequeue__left_aproach(void)

{

 can_msg_t my_buffer[8] = {0,0,0,0,0,0,0,0};

 ring_buffer_t ring_buf = {0};

 int ret = 0;



 ret = ring_buffer_init(&ring_buf, my_buffer, sizeof(my_buffer), sizeof(can_msg_t));



 UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((ret)), (

((void *)0)

), (UNITY_UINT)(226), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((sizeof(my_buffer) - 1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.buffer_byte_length)), (

((void *)0)

), (UNITY_UINT)(227), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((sizeof(can_msg_t))), (UNITY_INT)(UNITY_UINT32)((ring_buf.data_size)), (

((void *)0)

), (UNITY_UINT)(228), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(229), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(230), UNITY_DISPLAY_STYLE_UINT32);



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



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((7)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(327), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(328), UNITY_DISPLAY_STYLE_UINT32);



 ring_buffer_size_t elements = ring_buffer_num_items(&ring_buf);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((7)), (UNITY_INT)(UNITY_UINT32)((elements)), (

((void *)0)

), (UNITY_UINT)(332), UNITY_DISPLAY_STYLE_UINT32);



 can_msg_t can_msg_aux[7] = {0};



 ring_buffer_dequeue(&ring_buf, &can_msg_aux[0]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[1]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[2]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[3]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[4]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[5]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[6]);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((7)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(344), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((7)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(345), UNITY_DISPLAY_STYLE_UINT32);



 elements = ring_buffer_num_items(&ring_buf);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((elements)), (

((void *)0)

), (UNITY_UINT)(349), UNITY_DISPLAY_STYLE_UINT32);





 for(int i = 0; i < 7; i++)

 {

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((i + 1)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[i].can_id)), (

 ((void *)0)

 ), (UNITY_UINT)(354), UNITY_DISPLAY_STYLE_UINT32);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].dlc)), (

 ((void *)0)

 ), (UNITY_UINT)(355), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x01)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[0])), (

 ((void *)0)

 ), (UNITY_UINT)(356), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x02)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[1])), (

 ((void *)0)

 ), (UNITY_UINT)(357), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x03)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[2])), (

 ((void *)0)

 ), (UNITY_UINT)(358), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x04)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[3])), (

 ((void *)0)

 ), (UNITY_UINT)(359), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x05)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[4])), (

 ((void *)0)

 ), (UNITY_UINT)(360), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x06)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[5])), (

 ((void *)0)

 ), (UNITY_UINT)(361), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x07)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[6])), (

 ((void *)0)

 ), (UNITY_UINT)(362), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x08)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[7])), (

 ((void *)0)

 ), (UNITY_UINT)(363), UNITY_DISPLAY_STYLE_UINT8);

 }

}



void test__ring_buffer_queue_dequeue__equal(void)

{

 can_msg_t my_buffer[8] = {0,0,0,0,0,0,0,0};

 ring_buffer_t ring_buf = {0};

 int ret = 0;



 ret = ring_buffer_init(&ring_buf, my_buffer, sizeof(my_buffer), sizeof(can_msg_t));



 UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((ret)), (

((void *)0)

), (UNITY_UINT)(375), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((sizeof(my_buffer) - 1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.buffer_byte_length)), (

((void *)0)

), (UNITY_UINT)(376), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((sizeof(can_msg_t))), (UNITY_INT)(UNITY_UINT32)((ring_buf.data_size)), (

((void *)0)

), (UNITY_UINT)(377), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(378), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(379), UNITY_DISPLAY_STYLE_UINT32);



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





 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(490), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(491), UNITY_DISPLAY_STYLE_UINT32);



 ring_buffer_size_t elements = ring_buffer_num_items(&ring_buf);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((7)), (UNITY_INT)(UNITY_UINT32)((elements)), (

((void *)0)

), (UNITY_UINT)(495), UNITY_DISPLAY_STYLE_UINT32);



 can_msg_t can_msg_aux[8] = {0};

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[0]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[1]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[2]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[3]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[4]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[5]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[6]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[7]);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(507), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(508), UNITY_DISPLAY_STYLE_UINT32);



 elements = ring_buffer_num_items(&ring_buf);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((elements)), (

((void *)0)

), (UNITY_UINT)(512), UNITY_DISPLAY_STYLE_UINT32);









 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((2)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[0].can_id)), (

((void *)0)

), (UNITY_UINT)(517), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((3)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[1].can_id)), (

((void *)0)

), (UNITY_UINT)(518), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((4)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[2].can_id)), (

((void *)0)

), (UNITY_UINT)(519), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((5)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[3].can_id)), (

((void *)0)

), (UNITY_UINT)(520), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((6)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[4].can_id)), (

((void *)0)

), (UNITY_UINT)(521), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((7)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[5].can_id)), (

((void *)0)

), (UNITY_UINT)(522), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((8)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[6].can_id)), (

((void *)0)

), (UNITY_UINT)(523), UNITY_DISPLAY_STYLE_UINT32);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[7].can_id)), (

((void *)0)

), (UNITY_UINT)(525), UNITY_DISPLAY_STYLE_UINT32);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[0].dlc)), (

((void *)0)

), (UNITY_UINT)(527), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[1].dlc)), (

((void *)0)

), (UNITY_UINT)(528), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[2].dlc)), (

((void *)0)

), (UNITY_UINT)(529), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[3].dlc)), (

((void *)0)

), (UNITY_UINT)(530), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[4].dlc)), (

((void *)0)

), (UNITY_UINT)(531), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[5].dlc)), (

((void *)0)

), (UNITY_UINT)(532), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[6].dlc)), (

((void *)0)

), (UNITY_UINT)(533), UNITY_DISPLAY_STYLE_UINT8);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].dlc)), (

((void *)0)

), (UNITY_UINT)(535), UNITY_DISPLAY_STYLE_UINT8);



 for(int i = 0; i < 7; i++)

 {

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x01)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[0])), (

 ((void *)0)

 ), (UNITY_UINT)(539), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x02)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[1])), (

 ((void *)0)

 ), (UNITY_UINT)(540), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x03)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[2])), (

 ((void *)0)

 ), (UNITY_UINT)(541), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x04)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[3])), (

 ((void *)0)

 ), (UNITY_UINT)(542), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x05)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[4])), (

 ((void *)0)

 ), (UNITY_UINT)(543), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x06)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[5])), (

 ((void *)0)

 ), (UNITY_UINT)(544), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x07)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[6])), (

 ((void *)0)

 ), (UNITY_UINT)(545), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x08)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[7])), (

 ((void *)0)

 ), (UNITY_UINT)(546), UNITY_DISPLAY_STYLE_UINT8);

 }





 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[0])), (

((void *)0)

), (UNITY_UINT)(550), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[1])), (

((void *)0)

), (UNITY_UINT)(551), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[2])), (

((void *)0)

), (UNITY_UINT)(552), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[3])), (

((void *)0)

), (UNITY_UINT)(553), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[4])), (

((void *)0)

), (UNITY_UINT)(554), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[5])), (

((void *)0)

), (UNITY_UINT)(555), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[6])), (

((void *)0)

), (UNITY_UINT)(556), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[7])), (

((void *)0)

), (UNITY_UINT)(557), UNITY_DISPLAY_STYLE_UINT8);

}



void test__ring_buffer_queue_dequeue__overflow(void)

{

 can_msg_t my_buffer[8] = {0,0,0,0,0,0,0,0};

 ring_buffer_t ring_buf = {0};

 int ret = 0;



 ret = ring_buffer_init(&ring_buf, my_buffer, sizeof(my_buffer), sizeof(can_msg_t));



 UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((ret)), (

((void *)0)

), (UNITY_UINT)(568), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((sizeof(my_buffer) - 1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.buffer_byte_length)), (

((void *)0)

), (UNITY_UINT)(569), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((sizeof(can_msg_t))), (UNITY_INT)(UNITY_UINT32)((ring_buf.data_size)), (

((void *)0)

), (UNITY_UINT)(570), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(571), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(572), UNITY_DISPLAY_STYLE_UINT32);



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





 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(696), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((2)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(697), UNITY_DISPLAY_STYLE_UINT32);



 ring_buffer_size_t elements = ring_buffer_num_items(&ring_buf);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((7)), (UNITY_INT)(UNITY_UINT32)((elements)), (

((void *)0)

), (UNITY_UINT)(701), UNITY_DISPLAY_STYLE_UINT32);



 can_msg_t can_msg_aux[8] = {0};

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[0]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[1]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[2]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[3]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[4]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[5]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[6]);

 ring_buffer_dequeue(&ring_buf, &can_msg_aux[7]);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.head_index)), (

((void *)0)

), (UNITY_UINT)(713), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((ring_buf.tail_index)), (

((void *)0)

), (UNITY_UINT)(714), UNITY_DISPLAY_STYLE_UINT32);



 elements = ring_buffer_num_items(&ring_buf);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((elements)), (

((void *)0)

), (UNITY_UINT)(718), UNITY_DISPLAY_STYLE_UINT32);









 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((3)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[0].can_id)), (

((void *)0)

), (UNITY_UINT)(723), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((4)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[1].can_id)), (

((void *)0)

), (UNITY_UINT)(724), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((5)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[2].can_id)), (

((void *)0)

), (UNITY_UINT)(725), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((6)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[3].can_id)), (

((void *)0)

), (UNITY_UINT)(726), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((7)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[4].can_id)), (

((void *)0)

), (UNITY_UINT)(727), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((8)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[5].can_id)), (

((void *)0)

), (UNITY_UINT)(728), UNITY_DISPLAY_STYLE_UINT32);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((9)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[6].can_id)), (

((void *)0)

), (UNITY_UINT)(729), UNITY_DISPLAY_STYLE_UINT32);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((can_msg_aux[7].can_id)), (

((void *)0)

), (UNITY_UINT)(731), UNITY_DISPLAY_STYLE_UINT32);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[0].dlc)), (

((void *)0)

), (UNITY_UINT)(733), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[1].dlc)), (

((void *)0)

), (UNITY_UINT)(734), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[2].dlc)), (

((void *)0)

), (UNITY_UINT)(735), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[3].dlc)), (

((void *)0)

), (UNITY_UINT)(736), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[4].dlc)), (

((void *)0)

), (UNITY_UINT)(737), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[5].dlc)), (

((void *)0)

), (UNITY_UINT)(738), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((8)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[6].dlc)), (

((void *)0)

), (UNITY_UINT)(739), UNITY_DISPLAY_STYLE_UINT8);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].dlc)), (

((void *)0)

), (UNITY_UINT)(741), UNITY_DISPLAY_STYLE_UINT8);



 for(int i = 0; i < 7; i++)

 {

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x01)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[0])), (

 ((void *)0)

 ), (UNITY_UINT)(745), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x02)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[1])), (

 ((void *)0)

 ), (UNITY_UINT)(746), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x03)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[2])), (

 ((void *)0)

 ), (UNITY_UINT)(747), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x04)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[3])), (

 ((void *)0)

 ), (UNITY_UINT)(748), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x05)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[4])), (

 ((void *)0)

 ), (UNITY_UINT)(749), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x06)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[5])), (

 ((void *)0)

 ), (UNITY_UINT)(750), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x07)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[6])), (

 ((void *)0)

 ), (UNITY_UINT)(751), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0x08)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[i].payload[7])), (

 ((void *)0)

 ), (UNITY_UINT)(752), UNITY_DISPLAY_STYLE_UINT8);

 }





 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[0])), (

((void *)0)

), (UNITY_UINT)(756), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[1])), (

((void *)0)

), (UNITY_UINT)(757), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[2])), (

((void *)0)

), (UNITY_UINT)(758), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[3])), (

((void *)0)

), (UNITY_UINT)(759), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[4])), (

((void *)0)

), (UNITY_UINT)(760), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[5])), (

((void *)0)

), (UNITY_UINT)(761), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[6])), (

((void *)0)

), (UNITY_UINT)(762), UNITY_DISPLAY_STYLE_UINT8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((can_msg_aux[7].payload[7])), (

((void *)0)

), (UNITY_UINT)(763), UNITY_DISPLAY_STYLE_UINT8);

}
