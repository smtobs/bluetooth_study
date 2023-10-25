#ifndef _HCI_MANAGER_H
#define _HCI_MANAGER_H

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#define MAX_BT_SCAN_DEVICES     255

typedef enum
{
    SCAN_DURATION_1_28_SEC = 1, // 1 x 1.28 = 1.28 seconds
    SCAN_DURATION_2_56_SEC,     // 2 x 1.28 = 2.56 seconds
    SCAN_DURATION_5_12_SEC,     // 3 x 1.28 = 5.12 seconds
    SCAN_DURATION_10_24_SEC,    // 4 x 1.28 = 10.24 seconds
} scan_duration;

int open_bt_device(int *, int *);
void close_bt_device(int);
inquiry_info *perform_bt_inquiry(int, int, int, int, int *);
void display_bt_device_info(int, inquiry_info *, int);
int get_bt_inquiry_flush_flag();

#endif
