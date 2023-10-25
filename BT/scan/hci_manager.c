#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "hci_manager.h"

int open_bt_device(int *sock, int *dev_id)
{
    *dev_id = hci_get_route(NULL);
    *sock = hci_open_dev(*dev_id);
    if (*dev_id < 0 || *sock < 0)
    {
        perror("opening socket");
        return 0;
    }

    return 1;
}

void close_bt_device(int sock)
{
    if (sock >= 0 && sock <= 2)
    {
        fprintf(stderr, "Warning: Trying to close a standard file descriptor (%d)!\n", sock);
        return;
    }

    if (close(sock) < 0)
    {
        perror("Error closing socket");
    }
}

inquiry_info *perform_bt_inquiry(int dev_id, int len, int max_rsp, int flags, int *num_rsp)
{
    inquiry_info *inq_info = NULL;

    if (dev_id < 0)
    {
        fprintf(stderr, "No Bluetooth device found.\n");
    }

    inq_info = (inquiry_info *)malloc(max_rsp * sizeof(inquiry_info));
    *num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &inq_info, flags);
    if (*num_rsp < 0)
    {
        perror("hci_inquiry");
    }

    return inq_info;
}

void display_bt_device_info(int sock, inquiry_info *inq_info, int num_rsp)
{
    int i;
    char addr[19] = {0};
    char name[248] = {0};

    for (i = 0; i < num_rsp; i++)
    {
        ba2str(&(inq_info + i)->bdaddr, addr);
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(sock, &(inq_info + i)->bdaddr, sizeof(name), name, 0) < 0)
        {
            snprintf(name, sizeof(name), "[unknown]");
        }
        printf("%s  %s\n", addr, name);
    }
}

int get_bt_inquiry_flush_flag()
{
    return IREQ_CACHE_FLUSH;
}
