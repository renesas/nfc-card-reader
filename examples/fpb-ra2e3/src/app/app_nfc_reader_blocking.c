/***********************************************************************************************************************
 * app_nfc_reader_blocking.c - application example: blocking-mode read
 *
 * Blocking mode in three lines of configuration:
 *   cfg.callback      = RS_NFC_CALLBACK_NONE;   (NULL)  -> the read runs in the calling task
 *   cfg.on_card_event = NULL;                           -> one card, then return
 *   cfg.timeout_ms    = RS_NFC_TIMEOUT_DEFAULT_MS;      -> do not wait forever
 *
 * To stop a blocking read early, call rs_nfc_reader_Stop() from another task: the calling task is busy inside Read().
 **********************************************************************************************************************/
#include <string.h>
#include "app_nfc_reader_blocking.h"
#include "app_nfc_reader_wait_state.h"

#if APP_NFC_BLOCKING_EXAMPLE

rs_status_t app_nfc_read_once_blocking (void)
{
    /* Static: keeps the ~1 KB result off the calling task's stack. */
    static rs_nfc_card_result_t result;

    rs_nfc_reader_cfg_t cfg;
    (void) memset(&cfg, 0, sizeof(cfg));

    cfg.tech_mask             = RS_NFC_TECH_ALL;
    cfg.timeout_ms            = RS_NFC_TIMEOUT_DEFAULT_MS;
    cfg.retry_count           = RS_NFC_RETRY_DISABLED;
    cfg.read_ndef             = RS_NFC_NDEF_READ_ENABLED;
    cfg.max_ndef_bytes        = RS_NFC_NDEF_MAX_BYTES;
    cfg.run_raw_exchange      = RS_NFC_RAW_EXCHANGE_DISABLED;
    cfg.callback              = RS_NFC_CALLBACK_NONE;        /* NULL: blocking mode */
    cfg.p_context             = RS_NFC_CONTEXT_NONE;
    cfg.on_card_event         = NULL;                        /* NULL: one card, then return */
    cfg.p_card_event_context  = RS_NFC_CONTEXT_NONE;
    cfg.validate_dependencies = RS_NFC_DEP_VALIDATION_ENABLED;
    cfg.cfg_valid_check_en    = RS_NFC_CFG_VALIDATION_ENABLED;

    rs_status_t st = rs_nfc_reader_Read(&cfg, &result);

    if (RS_OK != st)
    {
        APP_LOG("NFC read failed (status %d): %s\r\n",
                (int) st, app_nfc_wait_state_text(rs_nfc_reader_GetWaitState()));
    }
    else if (0U == result.uid_len)
    {
        APP_LOG("NFC read stopped before a card was read\r\n");
    }
    else
    {
        APP_LOG("Card UID:");

        for (uint8_t i = 0U; i < result.uid_len; i++)
        {
            APP_LOG(" %02X", (unsigned) result.uid[i]);
        }

        APP_LOG("\r\n");
    }

    return st;
}

#else

typedef int app_nfc_reader_blocking_disabled_t;   /* keep the translation unit non-empty */

#endif
