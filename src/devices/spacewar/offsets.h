/* Nothing Phone 1 (Spacewar) — SM7325 / Snapdragon 778G+, kernel 5.4.302
 *
 * Offsets extracted from live device kallsyms (kptr_restrict=0).
 * Struct offsets: pahole, spacewar_defconfig.
 * kernel_phys_load: /proc/iomem "Kernel code" - 0x1000 (PE header).
 *
 * uname -r: 5.4.302-qgki-g50ffa3680cd3
 */

OFFSETS_ENTRY("5.4.302-qgki-g50ffa3680cd3",
  .kernel_phys_load=0xa007f000, STRUCT_OFFSETS_5_4,
  .off_init_task=0x28a93c0, .off_init_cred=0x28b54a8,
  .off_init_uts_ns=0x28a9160, .off_empty_zero_page=0x2ad1000,
  .off_root_task_group=0x2ae2840, .off_selinux_enforcing=0x2ad0000,
  .off_kptr_restrict=0x27b87f0, .off_selinux_blob_sizes=0x250cc70,
  .off_security_hook_heads=0x250a888, .off_kmalloc_caches=0x250a3f0,
  .off_anon_pipe_buf_ops=0x23af5b8, .off_ashmem_misc_fops=0x283cdb8,
  .off_ashmem_fops=0x2384e10,
  .off_ashmem_ioctl=0x2105ec, .off_ashmem_compat_ioctl=0x210740,
  .off_ashmem_mmap=0x210790, .off_ashmem_open=0x210940,
  .off_ashmem_release=0x2109b0, .off_ashmem_show_fdinfo=0,
  .off_configfs_read_iter=0x57c60c,  /* configfs_read_file (5.4 name) */
  .off_configfs_bin_write_iter=0x57cc20,  /* configfs_write_bin_file (5.4 name) */
  .off_copy_splice_read=0x508abc,  /* generic_file_splice_read (5.4 name) */
  .off_noop_llseek=0x4c277c, .off_cap_capable_active=0x6d84b4,
  .off_slide_nfulnl_logger=0x27aae10, .off_slide_loggers_0_1=0x27b3458,
  .off_slide_boot_id=0x2b567d1,
  .off_system_unbound_wq=0x27afc80,
  .off_call_usermodehelper_exec_work=0x2c3e18,
),
