/*
 * Copyright 2019, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#pragma once

#include <sel4arm-vmm/vm.h>
#include <sel4arm-vmm/devices.h>

#define VIRTIO_IOPORT_SIZE      0x400
#define VIRTIO_IOPORT_START     0x6200
#define VIRTIO_INTERRUPT_PIN    1
