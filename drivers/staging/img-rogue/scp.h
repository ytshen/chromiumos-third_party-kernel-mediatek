/**************************************************************************/ /*!
@File
@Title          Software Command Processor header
@Copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved
@Description    Defines the interface for the software command processor
@License        Strictly Confidential.
*/ /***************************************************************************/

#ifndef SCP_H
#define SCP_H

#include "img_types.h"
#include "pvrsrv_error.h"
#include "sync_server.h"

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct _SCP_CONTEXT_ SCP_CONTEXT;	/*!< Opaque handle to a software command processor context */

typedef IMG_BOOL (*SCPReady)(IMG_PVOID pvReadyData);
typedef IMG_VOID (*SCPDo)(IMG_PVOID pvReadyData, IMG_PVOID pvCompleteData);

/*************************************************************************/ /*!
@Function       SCPCreate

@Description    Create a software command processor

@Input          ui32CCBSizeLog2         Log2 of the CCB size

@Output         ppvBufferSpace          Pointer to space allocated

@Return         PVRSRV_OK if the software command processor was created
*/
/*****************************************************************************/
IMG_IMPORT
PVRSRV_ERROR IMG_CALLCONV SCPCreate(IMG_UINT32 ui32CCBSizeLog2,
									SCP_CONTEXT **ppsContext);

/*************************************************************************/ /*!
@Function       SCPAllocCommand

@Description    Allocate space in the software command processor and return
                the data pointers for the callback data.

                Once any command ready data and command complete have been setup
                the command can be submitted for processing by calling
                SCPSubmitCommand.

                When any fences the command has have been meet then the command
                ready callback will be called with the command ready data.
                Once the command has completed the command complete callback will
                be called with the command complete data.

@Input          psSCPContext            Context to allocate from

@Input          ui32SyncPrimCount       Number of Sync Prim operations

@Input          papsSync                Pointer to array of pointers to server syncs

@Input          pfnCommandReady         Callback to call if the command is ready

@Input          pfnCommandDo            Callback to the function to run

@Input          ui32ReadyDataSize       Size of command ready data to allocate in bytes

@Input          pfnCommandComplete      Callback to call when the command has completed

@Input          ui32CompleteDataSize    Size of command complete data to allocate

@Output         ppvReadyData            Pointer to memory allocated for command
                                        ready callback data

@Output         ppvCompleteData         Pointer to memory allocated for command
                                        complete callback data

@Return         PVRSRV_OK if the allocate was successfull
*/
/*****************************************************************************/
IMG_IMPORT
PVRSRV_ERROR IMG_CALLCONV SCPAllocCommand(SCP_CONTEXT *psSCPContext,
										  IMG_UINT32 ui32SyncPrimCount,
										  SERVER_SYNC_PRIMITIVE **papsSync,
										  IMG_BOOL *pabUpdate,
										  IMG_INT32 i32AcquireFenceFd,
										  SCPReady pfnCommandReady,
										  SCPDo pfnCommandDo,
										  IMG_SIZE_T ui32ReadyDataByteSize,
										  IMG_SIZE_T ui32CompleteDataByteSize,
										  IMG_PVOID *ppvReadyData,
										  IMG_PVOID *ppvCompleteData,
										  IMG_INT32 *pi32ReleaseFenceFd);

/*************************************************************************/ /*!
@Function       SCPSubmitCommand

@Description    Submit a command for processing. We don't actually try to
                run the command in this call as it might not be valid to do
                from the same thread that this function is being called from

@Input          psSCPContext            Context to allocate on which to submit
                                        the command

@Return         PVRSRV_OK if the command was submitted
*/
/*****************************************************************************/
IMG_IMPORT
PVRSRV_ERROR SCPSubmitCommand(SCP_CONTEXT *psContext);


/*************************************************************************/ /*!
@Function       SCPRun

@Description    Run the software command processor to see if any commands are
                now ready.

@Input          psSCPContext            Context to process

@Return         PVRSRV_OK if the software command processor was run
*/
/*****************************************************************************/
IMG_IMPORT
PVRSRV_ERROR SCPRun(SCP_CONTEXT *psContext);

/*************************************************************************/ /*!
@Function       SCPCommandComplete

@Description    Complete a command which the software command processor
                has previously issued.
                Note: Commands _MUST_ be completed in order

@Input          psSCPContext            Context to process

@Return         PVRSRV_OK if the software command processor was run
*/
/*****************************************************************************/
IMG_IMPORT
IMG_VOID SCPCommandComplete(SCP_CONTEXT *psContext);

/*************************************************************************/ /*!
@Function       SCPFlush

@Description    Flush the software command processor.

@Input          psSCPContext            Context to process

@Return         PVRSRV_OK if all commands have been completed, otherwise
				PVRSRV_ERROR_RETRY
*/
/*****************************************************************************/
IMG_EXPORT
PVRSRV_ERROR SCPFlush(SCP_CONTEXT *psContext);

/*************************************************************************/ /*!
@Function       SCPHasPendingCommand

@Description    Check the software command processor for pending commands.

@Input          psContext               Context to process

@Return         IMG_TRUE if there is at least one pending command
				IMG_FALSE if there are no pending commands
*/
/*****************************************************************************/
IMG_EXPORT
IMG_BOOL SCPHasPendingCommand(SCP_CONTEXT *psContext);

/*************************************************************************/ /*!
@Function       SCPDumpStatus

@Description    Dump the status of the provided software command processor.

@Input          psSCPContext            Context to dump

@Return         None
*/
/*****************************************************************************/
IMG_EXPORT
IMG_VOID IMG_CALLCONV SCPDumpStatus(SCP_CONTEXT *psContext);

/*************************************************************************/ /*!
@Function       SCPDestroy

@Description    Destroy a software command processor.

@Input          psSCPContext            Context to destroy

@Return         None
*/
/*****************************************************************************/
IMG_IMPORT
IMG_VOID IMG_CALLCONV SCPDestroy(SCP_CONTEXT *psContext);

#if defined (__cplusplus)
}
#endif

#endif /* SCP_H */

/******************************************************************************
 End of file (queue.h)
******************************************************************************/
