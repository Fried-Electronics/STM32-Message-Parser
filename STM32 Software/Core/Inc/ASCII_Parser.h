/*
 * ASCII_Parser.h
 *
 *  Created on: Sep 5, 2022
 *      Author: Tom Fry
 */

#include "main.h"

#ifndef INC_ASCII_PARSER_H_
#define INC_ASCII_PARSER_H_

/*			Defines			*/
#define ASCII_BUFFER_LENGTH 512
#define ASCII_COMMAND_BUFFER_LENGTH 64
#define ASCII_COMMAND_STRING_MAX_LENGTH 64

/*			Types			*/

/*
 * @brief: Status of the buffer
 */
typedef enum _ASCII_BufferStatusTypeDef
{
	Buffer_Ready,
	Buffer_Transmitting,
	Buffer_No_Data,
	Buffer_Partial_Data,
	Buffer_Command_Ready
} ASCII_BufferStatusTypeDef;

/*
 * @brief: Typedef for the transmitting and receiving buffers
 */
typedef struct _ASCII_BufferTypeDef
{
	char Buffer[ASCII_BUFFER_LENGTH];	// Buffer for ASCII data
	uint16_t Head;						// Head of the buffer
	uint16_t Tail;						// Tail of the buffer
	ASCII_BufferStatusTypeDef Status;			// Status of the buffer
} ASCII_BufferTypeDef;

/*
 * @brief: Typedef for the command buffer
 * @param: String, command string
 * @param: Length, length of the command string
 * @param: Enum, enum returned if a command is matched
 */
typedef struct _ASCII_CommandTypeDef
{
	char String[ASCII_COMMAND_STRING_MAX_LENGTH];
	uint16_t Length;
	uint16_t Enum;
} ASCII_CommandTypeDef;

/*
 * @brief: Status of the ASCII Parser
 */
typedef enum _ASCII_StatusTypeDef
{
	ASCII_OK,
	ASCII_CmdBufferFull,
	ASCII_InvalidCommand,
	ASCII_Invalid_Suffix,
} ASCII_StatusTypeDef;

/*			Exported Functions			*/
ASCII_StatusTypeDef Add_Command(char* String, uint16_t Enum);

#endif /* INC_ASCII_PARSER_H_ */
