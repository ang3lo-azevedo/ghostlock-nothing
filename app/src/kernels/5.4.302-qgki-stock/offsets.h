/* Nothing Phone (1) stock kernel — 5.4.302-qgki-*
 * Target: lahaina_QGKI.config + defconfig, VA_BITS=39
 * Struct offsets from pahole on stock kernel source.
 * Kallsyms: TODO from stock boot.img.
 */

OFFSETS_ENTRY(
    "5.4.302-qgki-stock",  /* TODO: replace with exact uname -r from stock boot.img */
    .kernel_phys_load = 0xa007f000,
    STRUCT_OFFSETS_5_4_NOTHING_STOCK,
    .pselect_waiter_shift = 0,  /* TODO: measure on stock kernel */
    /* Kallsyms offsets: TODO from stock boot.img */
    .off_init_task = 0,
    .off_init_cred = 0,
    .off_root_task_group = 0,
    .off_selinux_enforcing = 0,
    .off_selinux_blob_sizes = 0,
    .off_security_hook_heads = 0,
    .off_kmalloc_caches = 0,
    .off_anon_pipe_buf_ops = 0,
    .off_slide_nfulnl_logger = 0,
    .off_slide_boot_id = 0,
    .off_configfs_read_iter = 0,
    .off_configfs_bin_write_iter = 0,
    .off_copy_splice_read = 0,
    .off_noop_llseek = 0,
    .off_slide_loggers_0_1 = 0,
    .off_ashmem_misc_fops = 0,
    .off_ashmem_fops = 0,
    .off_ashmem_ioctl = 0,
    .off_ashmem_compat_ioctl = 0,
    .off_ashmem_mmap = 0,
    .off_ashmem_open = 0,
    .off_ashmem_release = 0,
    .off_ashmem_show_fdinfo = 0,
)
