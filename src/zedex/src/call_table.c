#include <stdint.h>
#include <unistd.h>
#include <sys/syscall.h>

uint64_t CALL_TABLE[] =
{
#ifdef __NR_read
	__NR_read, 2,
#endif
#ifdef __NR_write
	__NR_write, 2,
#endif
#ifdef __NR_open
	__NR_open, 1,
#endif
#ifdef __NR_stat
	__NR_stat, 3,
#endif
#ifdef __NR_fstat
	__NR_fstat, 2,
#endif
#ifdef __NR_lstat
	__NR_lstat, 3,
#endif
#ifdef __NR_poll
	__NR_poll, 1,
#endif
#ifdef __NR_rt_sigaction
	__NR_rt_sigaction, 6,
#endif
#ifdef __NR_rt_sigprocmask
	__NR_rt_sigprocmask, 6,
#endif
#ifdef __NR_pread64
	__NR_pread64, 2,
#endif
#ifdef __NR_pwrite64
	__NR_pwrite64, 2,
#endif
#ifdef __NR_readv
	__NR_readv, 2,
#endif
#ifdef __NR_writev
	__NR_writev, 2,
#endif
#ifdef __NR_access
	__NR_access, 1,
#endif
#ifdef __NR_pipe
	__NR_pipe, 1,
#endif
#ifdef __NR_select
	__NR_select, 30,
#endif
#ifdef __NR_mincore
	__NR_mincore, 4,
#endif
#ifdef __NR_shmat
	__NR_shmat, 2,
#endif
#ifdef __NR_shmctl
	__NR_shmctl, 4,
#endif
#ifdef __NR_nanosleep
	__NR_nanosleep, 3,
#endif
#ifdef __NR_getitimer
	__NR_getitimer, 2,
#endif
#ifdef __NR_setitimer
	__NR_setitimer, 6,
#endif
#ifdef __NR_sendfile
	__NR_sendfile, 4,
#endif
#ifdef __NR_connect
	__NR_connect, 2,
#endif
#ifdef __NR_accept
	__NR_accept, 2,
#endif
#ifdef __NR_sendto
	__NR_sendto, 18,
#endif
#ifdef __NR_recvfrom
	__NR_recvfrom, 50,
#endif
#ifdef __NR_sendmsg
	__NR_sendmsg, 2,
#endif
#ifdef __NR_recvmsg
	__NR_recvmsg, 2,
#endif
#ifdef __NR_bind
	__NR_bind, 2,
#endif
#ifdef __NR_getsockname
	__NR_getsockname, 6,
#endif
#ifdef __NR_getpeername
	__NR_getpeername, 6,
#endif
#ifdef __NR_socketpair
	__NR_socketpair, 8,
#endif
#ifdef __NR_setsockopt
	__NR_setsockopt, 8,
#endif
#ifdef __NR_getsockopt
	__NR_getsockopt, 24,
#endif
#ifdef __NR_clone
	__NR_clone, 12,
#endif
#ifdef __NR_execve
	__NR_execve, 7,
#endif
#ifdef __NR_wait4
	__NR_wait4, 10,
#endif
#ifdef __NR_uname
	__NR_uname, 1,
#endif
#ifdef __NR_semop
	__NR_semop, 2,
#endif
#ifdef __NR_shmdt
	__NR_shmdt, 1,
#endif
#ifdef __NR_msgsnd
	__NR_msgsnd, 2,
#endif
#ifdef __NR_msgrcv
	__NR_msgrcv, 2,
#endif
#ifdef __NR_msgctl
	__NR_msgctl, 4,
#endif
#ifdef __NR_truncate
	__NR_truncate, 1,
#endif
#ifdef __NR_getdents
	__NR_getdents, 2,
#endif
#ifdef __NR_getcwd
	__NR_getcwd, 1,
#endif
#ifdef __NR_chdir
	__NR_chdir, 1,
#endif
#ifdef __NR_rename
	__NR_rename, 3,
#endif
#ifdef __NR_mkdir
	__NR_mkdir, 1,
#endif
#ifdef __NR_rmdir
	__NR_rmdir, 1,
#endif
#ifdef __NR_creat
	__NR_creat, 1,
#endif
#ifdef __NR_link
	__NR_link, 3,
#endif
#ifdef __NR_unlink
	__NR_unlink, 1,
#endif
#ifdef __NR_symlink
	__NR_symlink, 3,
#endif
#ifdef __NR_readlink
	__NR_readlink, 3,
#endif
#ifdef __NR_chmod
	__NR_chmod, 1,
#endif
#ifdef __NR_chown
	__NR_chown, 1,
#endif
#ifdef __NR_lchown
	__NR_lchown, 1,
#endif
#ifdef __NR_gettimeofday
	__NR_gettimeofday, 3,
#endif
#ifdef __NR_getrlimit
	__NR_getrlimit, 2,
#endif
#ifdef __NR_getrusage
	__NR_getrusage, 2,
#endif
#ifdef __NR_sysinfo
	__NR_sysinfo, 1,
#endif
#ifdef __NR_times
	__NR_times, 1,
#endif
#ifdef __NR_syslog
	__NR_syslog, 2,
#endif
#ifdef __NR_getgroups
	__NR_getgroups, 2,
#endif
#ifdef __NR_setgroups
	__NR_setgroups, 2,
#endif
#ifdef __NR_setresuid
	__NR_setresuid, 7,
#endif
#ifdef __NR_getresuid
	__NR_getresuid, 7,
#endif
#ifdef __NR_getresgid
	__NR_getresgid, 7,
#endif
#ifdef __NR_rt_sigpending
	__NR_rt_sigpending, 1,
#endif
#ifdef __NR_sigtimedwait
	__NR_sigtimedwait, 7,
#endif
#ifdef __NR_rt_sigqueueinfo
	__NR_rt_sigqueueinfo, 4,
#endif
#ifdef __NR_rt_sigsuspend
	__NR_rt_sigsuspend, 1,
#endif
#ifdef __NR_sigaltstack
	__NR_sigaltstack, 3,
#endif
#ifdef __NR_utime
	__NR_utime, 3,
#endif
#ifdef __NR_mknod
	__NR_mknod, 1,
#endif
#ifdef __NR_uselib
	__NR_uselib, 1,
#endif
#ifdef __NR_ustat
	__NR_ustat, 2,
#endif
#ifdef __NR_statfs
	__NR_statfs, 3,
#endif
#ifdef __NR_fstatfs
	__NR_fstatfs, 2,
#endif
#ifdef __NR_sched_setparam
	__NR_sched_setparam, 2,
#endif
#ifdef __NR_sched_getparam
	__NR_sched_getparam, 2,
#endif
#ifdef __NR_sched_setscheduler
	__NR_sched_setscheduler, 4,
#endif
#ifdef __NR_sched_rr_get_interval
	__NR_sched_rr_get_interval, 2,
#endif
#ifdef __NR_modify_ldt
	__NR_modify_ldt, 2,
#endif
#ifdef __NR_pivot_root
	__NR_pivot_root, 3,
#endif
#ifdef __NR_sysctl
	__NR_sysctl, 1,
#endif
#ifdef __NR_arch_prctl
	__NR_arch_prctl, 5,
#endif
#ifdef __NR_adjtimex
	__NR_adjtimex, 1,
#endif
#ifdef __NR_setrlimit
	__NR_setrlimit, 2,
#endif
#ifdef __NR_chroot
	__NR_chroot, 1,
#endif
#ifdef __NR_acct
	__NR_acct, 1,
#endif
#ifdef __NR_settimeofday
	__NR_settimeofday, 3,
#endif
#ifdef __NR_mount
	__NR_mount, 23,
#endif
#ifdef __NR_umount2
	__NR_umount2, 1,
#endif
#ifdef __NR_swapon
	__NR_swapon, 1,
#endif
#ifdef __NR_swapoff
	__NR_swapoff, 1,
#endif
#ifdef __NR_reboot
	__NR_reboot, 8,
#endif
#ifdef __NR_sethostname
	__NR_sethostname, 1,
#endif
#ifdef __NR_setdomainname
	__NR_setdomainname, 1,
#endif
#ifdef __NR_iopl
	__NR_iopl, 2,
#endif
#ifdef __NR_init_module
	__NR_init_module, 5,
#endif
#ifdef __NR_delete_module
	__NR_delete_module, 1,
#endif
#ifdef __NR_quotactl
	__NR_quotactl, 10,
#endif
#ifdef __NR_setxattr
	__NR_setxattr, 7,
#endif
#ifdef __NR_lsetxaddr
	__NR_lsetxaddr, 7,
#endif
#ifdef __NR_fsetxaddr
	__NR_fsetxaddr, 2,
#endif
#ifdef __NR_getxaddr
	__NR_getxaddr, 7,
#endif
#ifdef __NR_lgetxattr
	__NR_lgetxattr, 7,
#endif
#ifdef __NR_fgetxaddr
	__NR_fgetxaddr, 6,
#endif
#ifdef __NR_listxattr
	__NR_listxattr, 3,
#endif
#ifdef __NR_llistxattr
	__NR_llistxattr, 3,
#endif
#ifdef __NR_flistxattr
	__NR_flistxattr, 2,
#endif
#ifdef __NR_removexattr
	__NR_removexattr, 3,
#endif
#ifdef __NR_lremovexattr
	__NR_lremovexattr, 3,
#endif
#ifdef __NR_fremovexattr
	__NR_fremovexattr, 2,
#endif
#ifdef __NR_time
	__NR_time, 1,
#endif
#ifdef __NR_futex
	__NR_futex, 25,
#endif
#ifdef __NR_sched_setaffinity
	__NR_sched_setaffinity, 4,
#endif
#ifdef __NR_sched_getaffinity
	__NR_sched_getaffinity, 4,
#endif
#ifdef __NR_set_thread_area
	__NR_set_thread_area, 1,
#endif
#ifdef __NR_io_setup
	__NR_io_setup, 2,
#endif
#ifdef __NR_io_getevents
	__NR_io_getevents, 8,
#endif
#ifdef __NR_io_submit
	__NR_io_submit, 5,
#endif
#ifdef __NR_io_cancel
	__NR_io_cancel, 7,
#endif
#ifdef __NR_get_thread_area
	__NR_get_thread_area, 1,
#endif
#ifdef __NR_getdents64
	__NR_getdents64, 2,
#endif
#ifdef __NR_set_tid_address
	__NR_set_tid_address, 1,
#endif
#ifdef __NR_semtimedop
	__NR_semtimedop, 10,
#endif
#ifdef __NR_timer_create
	__NR_timer_create, 6,
#endif
#ifdef __NR_timer_settime
	__NR_timer_settime, 12,
#endif
#ifdef __NR_timer_gettime
	__NR_timer_gettime, 2,
#endif
#ifdef __NR_clock_settime
	__NR_clock_settime, 2,
#endif
#ifdef __NR_clock_gettime
	__NR_clock_gettime, 2,
#endif
#ifdef __NR_clock_getres
	__NR_clock_getres, 2,
#endif
#ifdef __NR_clock_nanosleep
	__NR_clock_nanosleep, 12,
#endif
#ifdef __NR_epoll_wait
	__NR_epoll_wait, 2,
#endif
#ifdef __NR_epoll_ctl
	__NR_epoll_ctl, 8,
#endif
#ifdef __NR_utimes
	__NR_utimes, 3,
#endif
#ifdef __NR_mbind
	__NR_mbind, 8,
#endif
#ifdef __NR_set_mempolicy
	__NR_set_mempolicy, 2,
#endif
#ifdef __NR_get_mempolicy
	__NR_get_mempolicy, 3,
#endif
#ifdef __NR_mq_open
	__NR_mq_open, 9,
#endif
#ifdef __NR_mq_unlink
	__NR_mq_unlink, 1,
#endif
#ifdef __NR_mq_timedsend
	__NR_mq_timedsend, 18,
#endif
#ifdef __NR_mq_timedreceive
	__NR_mq_timedreceive, 26,
#endif
#ifdef __NR_mq_notify
	__NR_mq_notify, 2,
#endif
#ifdef __NR_mq_getsetattr
	__NR_mq_getsetattr, 6,
#endif
#ifdef __NR_kexec_load
	__NR_kexec_load, 4,
#endif
#ifdef __NR_waitid
	__NR_waitid, 20,
#endif
#ifdef __NR_add_key
	__NR_add_key, 7,
#endif
#ifdef __NR_request_key
	__NR_request_key, 7,
#endif
#ifdef __NR_inotify_add_watch
	__NR_inotify_add_watch, 2,
#endif
#ifdef __NR_migrate_pages
	__NR_migrate_pages, 12,
#endif
#ifdef __NR_openat
	__NR_openat, 2,
#endif
#ifdef __NR_mkdirat
	__NR_mkdirat, 2,
#endif
#ifdef __NR_mknodat
	__NR_mknodat, 2,
#endif
#ifdef __NR_fchownat
	__NR_fchownat, 2,
#endif
#ifdef __NR_futimesat
	__NR_futimesat, 6,
#endif
#ifdef __NR_newfstatat
	__NR_newfstatat, 6,
#endif
#ifdef __NR_unlinkat
	__NR_unlinkat, 2,
#endif
#ifdef __NR_renameat
	__NR_renameat, 10,
#endif
#ifdef __NR_linkat
	__NR_linkat, 10,
#endif
#ifdef __NR_symlinkat
	__NR_symlinkat, 5,
#endif
#ifdef __NR_readlinkat
	__NR_readlinkat, 6,
#endif
#ifdef __NR_fchmodat
	__NR_fchmodat, 2,
#endif
#ifdef __NR_faccessat
	__NR_faccessat, 2,
#endif
#ifdef __NR_pselect6
	__NR_pselect6, 62,
#endif
#ifdef __NR_ppoll
	__NR_ppoll, 13,
#endif
#ifdef __NR_set_robust_list
	__NR_set_robust_list, 1,
#endif
#ifdef __NR_get_robust_list
	__NR_get_robust_list, 6,
#endif
#ifdef __NR_splice
	__NR_splice, 10,
#endif
#ifdef __NR_vmsplice
	__NR_vmsplice, 2,
#endif
#ifdef __NR_move_pages
	__NR_move_pages, 28,
#endif
#ifdef __NR_utimensat
	__NR_utimensat, 6,
#endif
#ifdef __NR_epoll_pwait
	__NR_epoll_pwait, 18,
#endif
#ifdef __NR_signalfd
	__NR_signalfd, 2,
#endif
#ifdef __NR_timerfd_settime
	__NR_timerfd_settime, 12,
#endif
#ifdef __NR_timerfd_gettime
	__NR_timerfd_gettime, 2,
#endif
#ifdef __NR_accept4
	__NR_accept4, 6,
#endif
#ifdef __NR_signalfd4
	__NR_signalfd4, 2,
#endif
#ifdef __NR_pipe2
	__NR_pipe2, 1,
#endif
#ifdef __NR_preadv
	__NR_preadv, 2,
#endif
#ifdef __NR_pwritev
	__NR_pwritev, 2,
#endif
#ifdef __NR_rt_tgsigqueueinfo
	__NR_rt_tgsigqueueinfo, 8,
#endif
#ifdef __NR_perf_event_open
	__NR_perf_event_open, 1,
#endif
#ifdef __NR_recvmmsg
	__NR_recvmmsg, 18,
#endif
#ifdef __NR_prlimit64
	__NR_prlimit64, 12,
#endif
#ifdef __NR_name_to_handle_at
	__NR_name_to_handle_at, 14,
#endif
#ifdef __NR_open_by_handle_at
	__NR_open_by_handle_at, 14,
#endif
#ifdef __NR_clock_adjtime
	__NR_clock_adjtime, 2,
#endif
#ifdef __NR_sendmmsg
	__NR_sendmmsg, 2,
#endif
#ifdef __NR_setns
	__NR_setns, 2,
#endif
#ifdef __NR_getcpu
	__NR_getcpu, 7,
#endif
#ifdef __NR_process_vm_readv
	__NR_process_vm_readv, 10,
#endif
#ifdef __NR_process_vm_writev
	__NR_process_vm_writev, 10,
#endif
#ifdef __NR_finit_module
	__NR_finit_module, 2,
#endif
#ifdef __NR_sched_setattr
	__NR_sched_setattr, 2,
#endif
#ifdef __NR_sched_getattr
	__NR_sched_getattr, 2,
#endif
#ifdef __NR_renameat2
	__NR_renameat2, 10,
#endif
#ifdef __NR_seccomp
	__NR_seccomp, 4,
#endif
#ifdef __NR_getrandom
	__NR_getrandom, 1,
#endif
#ifdef __NR_memfd_create
	__NR_memfd_create, 1,
#endif
#ifdef __NR_kexec_file_load
	__NR_kexec_file_load, 8,
#endif
#ifdef __NR_bpf
	__NR_bpf, 2,
#endif
#ifdef __NR_stub_execveat
	__NR_stub_execveat, 14,
#endif
#ifdef __NR_copy_file_range
	__NR_copy_file_range, 10,
#endif
#ifdef __NR_preadb2
	__NR_preadb2, 2,
#endif
#ifdef __NR_pwritev2
	__NR_pwritev2, 2,
#endif
};
