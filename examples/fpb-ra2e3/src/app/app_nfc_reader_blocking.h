/***********************************************************************************************************************
 * app_nfc_reader_blocking.h - application example: blocking-mode read
 *
 * The demo app (app_nfc_reader.c) runs the NFC SBB in non-blocking mode. This example shows blocking mode: leave the
 * callback and on_card_event empty and rs_nfc_reader_Read() returns when one card has been read, the timeout expires
 * or an error occurs. Output goes through APP_LOG().
 **********************************************************************************************************************/
#ifndef APP_NFC_READER_BLOCKING_H
#define APP_NFC_READER_BLOCKING_H

#include "rs_nfc_reader.h"
#include "app_nfc_reader_log.h"

/* 1 = build this example. Off by default: it is not called by the demo and it holds a ~1 KB result buffer. */
#ifndef APP_NFC_BLOCKING_EXAMPLE
#define APP_NFC_BLOCKING_EXAMPLE 0
#endif

/* Wait up to RS_NFC_TIMEOUT_DEFAULT_MS for one card, then print its UID or the failure. Call it from a FreeRTOS
 * task, not from an ISR or a software-timer callback, because the read blocks the calling task. */
rs_status_t app_nfc_read_once_blocking(void);

#endif /* APP_NFC_READER_BLOCKING_H */
