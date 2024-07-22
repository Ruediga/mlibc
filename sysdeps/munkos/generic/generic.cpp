#include <bits/ensure.h>
#include <mlibc/debug.hpp>
#include <mlibc/all-sysdeps.hpp>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <limits.h>

namespace mlibc {

extern "C" void __mlibc_thread_entry();

	int sys_clone(void *tcb, pid_t *tid_out, void *stack) {
		// TODO
		return 0;
	}

	int sys_prepare_stack(void **stack, void *entry, void *arg, void *tcb, size_t *stack_size, size_t *guard_size, void **stack_base) {
		// TODO
		return 0;
	}

	void sys_thread_exit() {
		// TODO
		__builtin_unreachable();
	}


}


namespace mlibc {

void sys_libc_log(const char *message) {
	// TODO
}

void sys_libc_panic() {
	mlibc::infoLogger() << "\e[31mmlibc: panic!" << frg::endlog;
}

int sys_tcb_set(void *pointer) {
	// TODO
	return -1;
}

int sys_anon_allocate(size_t size, void **pointer) {
	return -1;
}

int sys_anon_free(void *pointer, size_t size) {
	// TODO
	return -1;
}

#ifndef MLIBC_BUILDING_RTDL
void sys_exit(int status) {
	// TODO
}
#endif

#ifndef MLIBC_BUILDING_RTDL
int sys_clock_get(int clock, time_t *secs, long *nanos) {
	return 0;
}
#endif

int sys_close(int fd) {
	// TODO
	return -1;
}

int sys_open(const char *path, int flags, mode_t mode, int *fd) {
	// TODO
	return -1;
}

int sys_read(int fd, void *buf, size_t count, ssize_t *bytes_read) {
	// TODO
	return -1;
}

ssize_t write(int fd, const void* buf, size_t count){
    
}

#ifndef MLIBC_BUILDING_RTDL
int sys_write(int fd, const void *buf, size_t count, ssize_t *bytes_written) {
	// TODO
	return -1;
}
#endif


int sys_seek(int fd, off_t offset, int whence, off_t *new_offset) {
	return 0;
}

int sys_vm_map(void *hint, size_t size, int prot, int flags, int fd, off_t offset, void **window){
	// TODO
	return -1;
}

int sys_vm_unmap(void *pointer, size_t size) {
	// TODO
	return -1;
}

int sys_futex_wait(int *pointer, int expected, const struct timespec *time) {
	// TODO
	return -1;
}

int sys_futex_wake(int *pointer) {
	// TODO
	return -1;
}
