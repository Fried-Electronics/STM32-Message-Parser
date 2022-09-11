/*
 * ASCII_Parser.c
 *
 *  Created on: Sep 5, 2022
 *      Author: Tom Fry
 */

#include "ASCII_Parser.h"
#include "string.h"

/*			Buffers			*/
ASCII_BufferTypeDef ASCII_TxBuffer;
ASCII_BufferTypeDef ASCII_RxBuffer;

ASCII_CommandTypeDef CommandBuffer[ASCII_COMMAND_BUFFER_LENGTH];

/*			Global Variables			*/
uint16_t CommandBufferIndex = 0;

/*			Function Prototypes			*/

/*			Function Implementations			*/

/*
 *  @brief: Add new command to the command buffer
 *  @param: String, command string
 *  @param: Enum, enum to be returned on a successful match
 *  @retval: ASCII_OK if there is room in the buufer for the command
 */
ASCII_StatusTypeDef Add_Command (char* String, uint16_t Enum)
{
	uint16_t upperStringIndex = 0;
	uint16_t newCmdLength = strlen(String);
	char upperString[ASCII_COMMAND_STRING_MAX_LENGTH] = "";

	if (CommandBufferIndex >= ASCII_COMMAND_BUFFER_LENGTH) // Is the buffer full?
	{
		CommandBufferIndex = ASCII_COMMAND_BUFFER_LENGTH;
		return ASCII_CmdBufferFull;
	}

	if (newCmdLength > ASCII_COMMAND_STRING_MAX_LENGTH)
	{
		return ASCII_InvalidCommand;
	}

	while(*String != '\0')
	{
		if(*String >= 'a' && *String <= 'z')
		{
			upperString[upperStringIndex++] = *String - 32;
		} else {
			upperString[upperStringIndex++] = *String;
		}
		String++;
	}

	strcpy(CommandBuffer[CommandBufferIndex].String, upperString);
	CommandBuffer[CommandBufferIndex].Length = newCmdLength;
	CommandBuffer[CommandBufferIndex].Enum = Enum;

	CommandBufferIndex++;

	return ASCII_OK;
}

/*
 * @brief: Increments the head of the buffer
 */
ASCII_BufferStatusTypeDef Increment_Head (void)
{
	ASCII_BufferStatusTypeDef returnValue = Buffer_No_Data;
	uint16_t startHead = ASCII_RxBuffer.Head;

	for (uint16_t bufferIndex = ASCII_RxBuffer.Head; bufferIndex < ASCII_BUFFER_LENGTH; bufferIndex++)
	{
		if (ASCII_RxBuffer.Buffer[bufferIndex] != '0/')
		{
			if (ASCII_RxBuffer.Head == ASCII_BUFFER_LENGTH)
			{
				ASCII_RxBuffer.Head = 0;
			} else
			{
				ASCII_RxBuffer.Head++;
			}
		}
		break;
	}

	if (startHead != ASCII_RxBuffer.Head)
	{
		if (ASCII_RxBuffer.Buffer[ASCII_RxBuffer.Head] == ('\r' || '\n'))
		{
			returnValue = Buffer_Command_Ready;
		} else
		{
			returnValue = Buffer_Partial_Data;
		}
	}

	return returnValue;
}

/*
 * @brief: Increments the tail of the buffer
 */
ASCII_BufferStatusTypeDef Increment_Tail (void)
{
	while (ASCII_RxBuffer.Tail != ASCII_RxBuffer.Head)
	{
		if (ASCII_RxBuffer.Tail == ASCII_BUFFER_LENGTH)
		{
			ASCII_RxBuffer.Tail = 0;
		}
	}
}
