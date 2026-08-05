/* Nothing Phone 1 (Spacewar) — SM7325 / Snapdragon 778G+, kernel 5.4.302
 *
 * Offsets extracted via pahole from spacewar_defconfig kernel build.
 * Global symbol offsets: TODO — extract from kallsyms.
 */

OFFSETS_ENTRY("5.4.302-android14-11",  /* TODO: verify exact uname -r on device */
  .kernel_phys_load=0,  /* TODO: from /proc/iomem "Kernel code" - 0x10000 */
  STRUCT_OFFSETS_5_4,
  /* Global symbol offsets — TODO from kallsyms */
  .off_init_task=0, .off_init_cred=0, .off_init_uts_ns=0,
  .off_empty_zero_page=0, .off_root_task_group=0,
  .off_selinux_enforcing=0, .off_kptr_restrict=0,
  .off_selinux_blob_sizes=0, .off_security_hook_heads=0,
  .off_kmalloc_caches=0, .off_anon_pipe_buf_ops=0,
  .off_ashmem_misc_fops=0, .off_ashmem_fops=0,
  .off_ashmem_ioctl=0, .off_ashmem_compat_ioctl=0,
  .off_ashmem_mmap=0,
  .off_ashmem_open=0, .off_ashmem_release=0, .off_ashmem_show_fdinfo=0,
  .off_configfs_read_iter=0, .off_configfs_bin_write_iter=0,
  .off_copy_splice_read=0, .off_noop_llseek=0,
  .off_cap_capable_active=0,
  .off_slide_nfulnl_logger=0, .off_slide_loggers_0_1=0,
  .off_slide_boot_id=0,
  .off_system_unbound_wq=0, .off_call_usermodehelper_exec_work=0,
),
