/***********************************************************************************************************************
 * app_nfc_reader_wait_state.h - application example: reading the NFC SBB wait state
 *
 * The NFC SBB reports what it sees while it waits for a card (rs_nfc_reader_GetWaitState()). It prints nothing. This
 * example is the application side: it turns the state into text and prints it through APP_LOG(), which maps to
 * console_io today and can map to RTT with one change.
 **********************************************************************************************************************/
#ifndef APP_NFC_READER_WAIT_STATE_H
#define APP_NFC_READER_WAIT_STATE_H

#include "rs_nfc_reader.h"
#include "app_nfc_reader_log.h"

/* 1 = the demo runs app_nfc_heartbeat_run() after starting the reader. Off by default. */
#ifndef APP_NFC_HEARTBEAT_EXAMPLE
#define APP_NFC_HEARTBEAT_EXAMPLE 0
#endif

/* Plain-language text for a wait state. The SBB carries no text; the wording is the application's. */
const char * app_nfc_wait_state_text(rs_nfc_wait_state_t state);

/* Continuous mode never returns an error while it waits, so ask the SBB from time to time. Prints when the state
 * changes, and once if no reader interrupt has been seen for a long time. Never returns: call it from a task that
 * has nothing else to do (the demo's new_thread0). */
void app_nfc_heartbeat_run(void);

#endif /* APP_NFC_READER_WAIT_STATE_H */
