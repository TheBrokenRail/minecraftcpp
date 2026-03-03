#include <sys/ioctl.h>
#include <fcntl.h>
#include <cstdio>
#include <unistd.h>

#define MAJOR_NUM 100
#define IOCTL_MBOX_PROPERTY _IOWR(MAJOR_NUM, 0, char *)
#define DEVICE_FILE_NAME "char_dev"

int mbox_property(int fd, void *buf) {
    int ret = ioctl(fd, IOCTL_MBOX_PROPERTY, buf);
    if (ret < 0) {
        printf("ioctl_set_msg failed:%d\n", ret);
    }
    return ret;
}

struct Overscan {
    unsigned field0_0x0;
    unsigned field1_0x4;
    unsigned field2_0x8;
    unsigned field3_0xc;
};

struct Mailbox {
    Mailbox();
    ~Mailbox();
    bool get_firmware_version(unsigned *ret);
    bool get_overscan(Overscan *ret);
    bool set_overscan(Overscan *obj);

    int fd;
    bool status;
};

Mailbox::Mailbox() {
    status = false;
    int x = open("char_dev", 0);
    fd = x;
    x = ~x;
    x >>= 31;
    status = x;
}
Mailbox::~Mailbox() {
    if (status) {
        close(fd);
        status = false;
    }
}

bool Mailbox::get_firmware_version(unsigned *ret) {
    int i = 0;
    unsigned arr[32];
    if (status) {
        arr[i++] = 0;
        arr[i++] = 0;
        arr[i++] = 1; // TAG_GET_FIRMWARE_VERSION
        arr[i++] = 4;
        arr[i++] = 0;
        arr[i++] = 0;
        arr[i++] = 0;
        arr[0] = i * sizeof(*arr);
        mbox_property(fd, arr);
        *ret = arr[5];
    }
    return status;
}

bool Mailbox::get_overscan(Overscan *ret) {
    int i = 0;
    unsigned arr[32];
    if (status) {
        arr[i++] = 0;
        arr[i++] = 0;
        arr[i++] = 0x4000a; // TAG_GET_OVERSCAN
        arr[i++] = 0x10;
        arr[i++] = 0;
        arr[i++] = 0;
        arr[i++] = 0;
        arr[i++] = 0;
        arr[i++] = 0;
        arr[i++] = 0;
        arr[0] = i * sizeof(*arr);
        mbox_property(fd, arr);
        ret->field0_0x0 = arr[5];
        ret->field1_0x4 = arr[6];
        ret->field2_0x8 = arr[7];
        ret->field3_0xc = arr[8];
    }
    return status;
}
bool Mailbox::set_overscan(Overscan *obj) {
    int i = 0;
    unsigned arr[32];
    if (status) {
        arr[i++] = 0;
        arr[i++] = 0;
        arr[i++] = 0x4800a; // TAG_SET_OVERSCAN
        arr[i++] = 0x10;
        arr[i++] = 0x10;
        arr[i++] = obj->field0_0x0;
        arr[i++] = obj->field1_0x4;
        arr[i++] = obj->field2_0x8;
        arr[i++] = obj->field3_0xc;
        arr[i++] = 0;
        arr[0] = i * sizeof(*arr);
        mbox_property(fd, arr);
        obj->field0_0x0 = arr[5];
        obj->field1_0x4 = arr[6];
        obj->field2_0x8 = arr[7];
        obj->field3_0xc = arr[8];
    }
    return status;
}
