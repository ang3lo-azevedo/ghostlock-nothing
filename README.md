# GhostLock — Nothing Phone (1) Port

Fork of [JoinChang/ghostlock-oneplus](https://github.com/JoinChang/ghostlock-oneplus) adding support for the **Nothing Phone (1)** (Spacewar, SM7325).

Original: Kernel exploit for OnePlus/OPPO/realme devices with locked bootloader. Achieves root + KernelSU installation without unlocking bootloader or modifying boot image. Runtime auto-detection of kernel version with multi-device offset table.

## Vulnerability

**CVE-2026-43499** — Futex PI (Priority Inheritance) Use-After-Free

Affects Linux kernel 2.6.39 ~ 7.1. Fixed in mainline 7.1 (commit `3bfdc63936dd`).

The `pselect6` syscall copies `fd_set` data onto the kernel stack. When combined with the futex PI waiter mechanism, a freed stack frame can be reclaimed as an `rt_mutex_waiter` structure. The rb-tree rebalance during PI chain walk then writes controlled values to arbitrary kernel addresses.

## Supported Devices

### Working (upstream)

| Device | SoC | Kernel | Status |
|--------|-----|--------|--------|
| OnePlus Ace 6T (PLR110) | SM8845 | `6.12.38` | **Working** |
| OnePlus 15 (CPH2749) | SM8850 | `6.12.23` | **Working** |
| Xiaomi 17 (pudding) | SM8850 | `6.12.23` | **Working** |
| OnePlus 13 (IN2060) | SM8750 | `6.6.89` | **Working** |

### Work in Progress (this fork)

| Device | SoC | Kernel | Status |
|--------|-----|--------|--------|
| **Nothing Phone (1)** | SM7325 | `5.4.302` | Struct offsets extracted. Global symbols + pselect layout TODO. |

### Key differences for 5.4

- `rt_mutex_waiter` is 0x50 bytes (vs 0x70+ on 6.x) — smaller waiter means different stack layout
- `task_struct` layout significantly different (thread_info is 40 bytes, KABI reserves, custom configs)
- `CONFIG_FAIR_GROUP_SCHED=n`, `CONFIG_SCHED_CORE=n` — removes fields from task_struct
- `CONFIG_ASHMEM=y` (C ashmem) — UMH root path may be available
- `CONFIG_CONFIGFS_FS=y`, `CONFIG_FUTEX_PI=y` — required kernel features present
- Struct offsets extracted via **pahole** from the actual kernel build (spacewar_defconfig)

## Build

### Nothing Phone (1)

```bash
make TARGET=spacewar ANDROID_NDK_HOME=/path/to/ndk
```

### Other devices (upstream)

```bash
make ANDROID_NDK_HOME=/path/to/ndk
```

## Status — Nothing Phone (1)

- [x] Kernel confirmed vulnerable (`remove_waiter` uses `current` instead of `waiter->task`)
- [x] Struct offsets extracted via pahole (task_struct, rt_mutex_waiter, mm_struct)
- [x] Device directory + target.h created (`src/devices/spacewar/`)
- [x] `STRUCT_OFFSETS_5_4` macro defined in `src/devices/offsets.h`
- [ ] Global symbol offsets (kallsyms) — needs `/proc/kallsyms` dump from device
- [ ] pselect stack layout feasibility — needs kprobe measurement on device
- [ ] Source adaptation for 5.4 API differences
- [ ] Device test

## Setup

### Prerequisites

- ADB access to the device
- **ksud** for KernelSU management (already present if running a KSU kernel)
- Pull `/proc/kallsyms` to extract global symbol offsets:
  ```bash
  adb shell su -c 'cat /proc/kallsyms' > kallsyms.txt
  ```

### Determining pselect stack layout

On a rooted device, use kprobes to find the waiter position:

```bash
echo 'p:ds do_select fdsin=+0(%x1)' >> /sys/kernel/tracing/kprobe_events
echo 'p:rw rt_mutex_wait_proxy_lock waiter=%x2' >> /sys/kernel/tracing/kprobe_events
# trigger FUTEX_CMP_REQUEUE_PI, then:
#   PSELECT_SHIFT = ((waiter & 0x3fff) - (fdsin & 0x3fff)) / 8 - 2
```

### kernel_phys_load

```bash
su -c 'grep -i "Kernel code" /proc/iomem'
# Subtract _stext-_text (usually 0x10000)
```

## Adding New Devices / Kernel Versions

Only `boot.img` is needed — no root, no device access required.

### Extract offsets from boot.img

```bash
# 1. Extract kernel
python -c "import struct; d=open('boot.img','rb').read(); open('kernel','wb').write(d[4096:4096+struct.unpack_from('<I',d,8)[0]])"

# 2. Global symbols (kallsyms)
python tools/extract_target.py    # 28 offsets, auto-validated

# 3. Struct fields (BTF)
python tools/extract_btf.py kernel  # 57 offsets, auto-validated

# 4. Add to offsets.h, rebuild
```

### Adapting to non-OnePlus devices

The core exploit is device-agnostic. Adaptation may require:
- Different `VA_BITS` (48 vs 39) → update `target.h` memory layout
- Different `kernel_phys_load` → read from `/proc/iomem` or use `KPHYS=` env var
- Different struct offsets → use `STRUCT_OFFSETS_5_4`, `STRUCT_OFFSETS_6_6`, or `STRUCT_OFFSETS_6_12` in device entry
- Different `PSELECT_SHIFT` → determine via QEMU kprobe test or on-device measurement
- Different ashmem implementation (C vs Rust) → C ashmem enables UMH path

## Files

| File | Description |
|------|-------------|
| `src/core/main.c` | Exploit entry, Write 1/2, UMH path, bootstrap, root script |
| `src/core/fops.c` | pselect route, PI write mechanism, CFI stage |
| `src/core/util.c` | Heap spray, kernelsnitch, slab drain, payload setup |
| `src/core/pipe_physrw.c` | Pipe buffer-based physical memory r/w |
| `src/core/umh_root.c` | UMH root via workqueue injection |
| `src/core/miniadb.c` | Mini ADB client (TCP + RSA auth) |
| `src/core/common.h` | Timing parameters, macros |
| `src/core/target.h` | Default target (6.12) |
| `src/core/runtime_struct_offsets.h` | Per-device struct field override |
| `src/devices/offsets.h` | Aggregated offset tables + `STRUCT_OFFSETS_*` macros |
| `src/devices/spacewar/offsets.h` | Nothing Phone (1) offsets entry |
| `src/devices/spacewar/target.h` | Nothing Phone (1) target definitions |
| `src/core/slide.c` | SLIDE kernel address leak |
| `src/core/root.c` | Root shell setup |
| `tools/extract_target.py` | Offset extraction from kallsyms |
| `tools/extract_btf.py` | Struct offset extraction from BTF |
| `tools/check_feasibility.py` | Stack layout feasibility checker |

## License

For authorized security research and educational purposes only.

## Credits

- [JoinChang/ghostlock-oneplus](https://github.com/JoinChang/ghostlock-oneplus) — original exploit
- [NebuSec/CyberMeowfia](https://github.com/NebuSec/CyberMeowfia) — GhostLock exploit PoC
- [William24hmar/nothing_android_kernel_sm7325](https://github.com/William24hmar/nothing_android_kernel_sm7325) — KernelSU-SUSFS base
