/***********************************************************************************************************************
 * app_nfc_reader_wait_state.c - application example: reading the NFC SBB wait state
 **********************************************************************************************************************/
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "app_nfc_reader_wait_state.h"
#include "app_nfc_reader_blocking.h"

#if APP_NFC_HEARTBEAT_EXAMPLE || APP_NFC_BLOCKING_EXAMPLE

#define APP_NFC_HEARTBEAT_POLL_MS        (500U)
#define APP_NFC_HEARTBEAT_HINT_AFTER_MS  (10000U)

const char * app_nfc_wait_state_text (rs_nfc_wait_state_t state)
{
    switch (state)
    {
        case RS_NFC_WAIT_NO_IRQ_YET:
            return "waiting, no reader interrupt seen yet";
        case RS_NFC_WAIT_IRQ_SEEN:
            return "waiting, interrupt seen but no card reported yet";
        case RS_NFC_WAIT_CARD:
            return "card detected";
        case RS_NFC_WAIT_STOPPED:
            return "stopped by the application";
        case RS_NFC_WAIT_TIMEOUT_NO_IRQ:
            return "timed out, no reader interrupt seen";
        case RS_NFC_WAIT_TIMEOUT_IRQ_NO_CARD:
            return "timed out, interrupt seen but no card reported";
        case RS_NFC_WAIT_READER_ERROR:
            return "the reader reported a fault or could not be read";
        default:
            return "no wait yet";
    }
}

#endif

#if APP_NFC_HEARTBEAT_EXAMPLE

void app_nfc_heartbeat_run (void)
{
    rs_nfc_wait_state_t last       = RS_NFC_WAIT_NONE;
    uint32_t            quiet_ms   = 0U;
    bool                hint_shown = false;

    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(APP_NFC_HEARTBEAT_POLL_MS));

        rs_nfc_wait_state_t now = rs_nfc_reader_GetWaitState();

        if (now != last)
        {
            APP_LOG("NFC: %s\r\n", app_nfc_wait_state_text(now));
            last       = now;
            quiet_ms   = 0U;
            hint_shown = false;
        }
        else if (RS_NFC_WAIT_NO_IRQ_YET == now)
        {
            quiet_ms += APP_NFC_HEARTBEAT_POLL_MS;

            if ((!hint_shown) && (quiet_ms >= APP_NFC_HEARTBEAT_HINT_AFTER_MS))
            {
                APP_LOG("NFC: no reader interrupt for %u s. If a card is on the reader, check the IRQ line.\r\n",
                        (unsigned) (quiet_ms / 1000U));
                hint_shown = true;
            }
        }
        else
        {
            /* Nothing new to report. */
        }
    }
}

#endif

#if !(APP_NFC_HEARTBEAT_EXAMPLE || APP_NFC_BLOCKING_EXAMPLE)

typedef int app_nfc_reader_wait_state_disabled_t;   /* keep the translation unit non-empty */

#endif
