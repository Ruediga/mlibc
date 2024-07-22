#include <mlibc/all-sysdeps.hpp>
#include <mlibc/thread-entry.hpp>

#include <bits/ensure.h>
#include <mlibc/tcb.hpp>

#include <sys/mman.h>

#include <stddef.h>
#include <stdint.h>

extern "C" void __mlibc_enter_thread(void *entry, void *user_arg, Tcb *tcb) {
    // TODO
}

namespace mlibc {

static constexpr size_t default_stacksize = 0x1000000;

int sys_prepare_stack(void **stack, void *entry, void *user_arg, void *tcb,
                      size_t *stack_size, size_t *guard_size) {
	// TODO
	return -1;
}
} // namespace mlibc