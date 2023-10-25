#include <stdlib.h>
#include <unistd.h>

#include "hci_manager.h"

int main(int argc, char **argv)
{
    int sock, dev_id, num_rsp;
    inquiry_info *inq_info = NULL;

    if (!open_bt_device(&sock, &dev_id))
    {
        exit(1);
    }

    inq_info = perform_bt_inquiry(dev_id, SCAN_DURATION_10_24_SEC, MAX_BT_SCAN_DEVICES, get_bt_inquiry_flush_flag(), &num_rsp);
    display_bt_device_info(sock, inq_info, num_rsp);

    if (inq_info)
    {
        free(inq_info);
    }
    close_bt_device(sock);

    return 0;
}
