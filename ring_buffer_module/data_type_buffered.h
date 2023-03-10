/**
*******************************************************************************
* @file           : data_type_buffered.h
* @brief          : Description of header file
* @author         : Gonzalo Rivera
* @date           : 23/01/2023
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
#ifndef __DATA_TYPE_BUFFERED_H__
#define __DATA_TYPE_BUFFERED_H__
/******************************************************************************
        Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
/******************************************************************************
        Constants
 ******************************************************************************/

/******************************************************************************
        Data types
 ******************************************************************************/
typedef struct  __attribute__ ((__packed__))
{
	uint32_t can_id;
	uint8_t payload[8];
	uint8_t dlc;

}can_msg_t;
/******************************************************************************
        Public function prototypes
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // EOF __DATA_TYPE_BUFFERED_H__
