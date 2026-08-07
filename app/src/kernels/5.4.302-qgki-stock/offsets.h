/* Nothing Phone (1) stock kernel — 5.4.302-qgki-*
 * Target: lahaina_QGKI.config + defconfig, VA_BITS=39
 * Struct offsets from pahole on stock kernel source.
 * Kallsyms: TODO from stock boot.img.
 */

OFFSETS_ENTRY(
    "5.4.302-qgki-stock",  /* TODO: replace with exact uname -r from stock boot.img */
    .kernel_phys_load = 0xa007f000,
    .pselect_waiter_shift = 0,  /* TODO: measure on stock kernel */
    .task_prio = 0x6C, .task_normal_prio = 0x74, .task_sched_task_group = 0x330,
    .task_pi_lock = 0x85C, .task_pi_waiters = 0x868,
    .task_pi_top_task = 0x878, .task_pi_blocked_on = 0x880,
    .task_pid = 0x5C8, .task_tgid = 0x5CC,
    .task_atomic_flags = 0x590, .task_real_cred = 0x768, .task_cred = 0x770,
    .task_comm = 0x780, .task_tasks = 0x4C8, .task_seccomp = 0x838,
    /* Kallsyms offsets: TODO from stock boot.img */
    .off_init_task = 0, .off_init_cred = 0,
    .off_root_task_group = 0, .off_selinux_enforcing = 0,
    .off_selinux_blob_sizes = 0, .off_security_hook_heads = 0,
    .off_kmalloc_caches = 0, .off_anon_pipe_buf_ops = 0,
    .off_slide_nfulnl_logger = 0, .off_slide_boot_id = 0,
    .off_configfs_read_iter = 0, .off_configfs_bin_write_iter = 0,
    .off_copy_splice_read = 0, .off_noop_llseek = 0,
    .off_slide_loggers_0_1 = 0, .off_ashmem_misc_fops = 0,
    .off_ashmem_fops = 0, .off_ashmem_ioctl = 0,
    .off_ashmem_compat_ioctl = 0, .off_ashmem_mmap = 0,
    .off_ashmem_open = 0, .off_ashmem_release = 0,
    .off_ashmem_show_fdinfo = 0,
),
