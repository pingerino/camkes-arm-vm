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

#include <assert.h>
#include <camkes/dataport.h>
#include <camkes/irq.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <platsupport/io.h>
#include <platsupport/irq.h>
#include <utils/util.h>
#include <sel4/sel4.h>

#include <simple/simple.h>

/*- import 'dtb-query-common.template.c' as dtb_macros with context -*/

/*# Grab the DTB object made from the previous stages of the parsing #*/
/*- set configuration_name = '%s.%s' % (me.instance.name, me.interface.name) -*/
/*- set dtb_query = configuration[me.instance.name].get('dtb') -*/
/*- set dtb = dtb_query.get('query') -*/

/*- set untyped_dtb_mmio = [] -*/
/*- set dtb_irqs = [] -*/

/*# Extract the relevant fields from the DTB (regs, interrupts, etc) #*/
/*- for i in range(0, len(dtb)) -*/
    /*- set node = dtb[i] -*/

    /*? dtb_macros.parse_dtb_node_reg(node) ?*/
    /*- set reg_set = pop('reg_set') -*/

    /*- for (paddr, size) in reg_set -*/
        /*- set paddr = macros.ROUND_DOWN(paddr, 4096) -*/
        /*- set size = macros.ROUND_UP(size, 4096) -*/
        /*- set page_size = macros.get_page_size(size, options.architecture) -*/
        /*- set page_size_bits = int(math.log(page_size, 2)) -*/
        /*- set num_pages = int(size/page_size) -*/
        /*- for i in range(0, num_pages) -*/
            /*- set alloc_paddr = paddr + page_size*i -*/
            /*- set cap = alloc('dtb_untyped_cap_0x%x' % alloc_paddr, seL4_UntypedObject, paddr = alloc_paddr, size_bits = page_size_bits) -*/
            /*- do untyped_dtb_mmio.append( (alloc_paddr, page_size_bits, cap) ) -*/
        /*- endfor -*/
    /*- endfor -*/

    /*? dtb_macros.parse_dtb_node_interrupts(node, -1) ?*/
    /*- set irq_set = pop('irq_set') -*/
    /*- set irq_notification_object = alloc_obj('irq_notification_obj', seL4_NotificationObject) -*/
    /*- set irq_notification = alloc_cap('irq_notification_obj', irq_notification_object, read=True) -*/
    /*- for irq in irq_set -*/
            /*- set irq_cap = alloc('%s_irq_%d' % (me.interface.name, irq), seL4_IRQHandler, number=irq, notification=my_cnode[irq_notification]) -*/
            /*- do dtb_irqs.append( (irq, irq_cap) ) -*/
    /*- endfor -*/

/*- endfor -*/

/*- set self_cnode = alloc_cap('cnode', my_cnode, write=true) -*/

static int camkes_dtb_irqs[] = {
    /*- for (irq, cap) in dtb_irqs -*/
            /*? irq ?*/,
    /*- endfor -*/
};

int *camkes_dtb_get_irqs(int *num_irqs) {
    *num_irqs = ARRAY_SIZE(camkes_dtb_irqs);
    return camkes_dtb_irqs;
}

seL4_Error camkes_dtb_get_irq_cap(int irq, seL4_CNode cnode, seL4_Word index, uint8_t depth) {
    /*- if len(dtb_irqs) > 0 -*/
        switch(irq) {
        /*- for irq,cap in dtb_irqs -*/
            case /*? irq ?*/:
                return seL4_CNode_Copy(cnode, index, depth, /*? self_cnode ?*/, /*? cap ?*/, CONFIG_WORD_SIZE, seL4_AllRights);
        /*- endfor -*/
            default:
                return seL4_FailedLookup;
        }
    /*- else -*/
        return seL4_FailedLookup;
    /*- endif -*/
}

int camkes_dtb_untyped_count(void) {
    return /*? len(untyped_dtb_mmio) ?*/;
}

seL4_CPtr camkes_dtb_get_nth_untyped(int n, size_t *size_bits, uintptr_t *paddr) {
    switch(n) {
    /*- for i in range(0, len(untyped_dtb_mmio)) -*/
        /*- set (paddr,size_bits,cap)  = untyped_dtb_mmio[i] -*/
        case /*? i ?*/:
            *size_bits = (size_t)/*? size_bits ?*/;
            *paddr = /*? paddr ?*/;
            return /*? cap ?*/;
        /*- endfor -*/
        default:
            assert(!"Invalid untyped cap requested");
    }
    return 0;
}
