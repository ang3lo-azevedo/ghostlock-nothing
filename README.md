# ghostlock-nothing

Fork of [JoinChang/ghostlock-oneplus](https://github.com/JoinChang/ghostlock-oneplus) with **Nothing Phone (1)** (Spacewar, SM7325) support.

## Vulnerability

CVE-2026-43499 (GhostLock): use-after-free in the Linux kernel rtmutex futex PI code. Affects Linux 2.6.39 through 7.1-rc1.

Confirmed vulnerable in the stock Nothing kernel (`remove_waiter` uses `current` instead of `waiter->task`).

## Kernel configs

The Nothing Phone (1) has two different kernel builds that need separate offsets:

| Kernel | Source | Config | GhostLock |
|--------|--------|--------|-----------|
| Stock Nothing | [NothingOSS](https://github.com/NothingOSS/android_kernel_msm-5.4_nothing_sm7325) | `lahaina_QGKI.config` + `defconfig` | Vulnerable |
| Custom KSU | [William24hmar](https://github.com/William24hmar/nothing_android_kernel_sm7325) | `spacewar_defconfig` | Patched |

These kernels have **different struct layouts** because `spacewar_defconfig` enables `CONFIG_ARM64_SW_TTBR0_PAN`, `CONFIG_SHADOW_CALL_STACK`, KABI reserves, and other features not in the stock config.

## Devices

| Device | SoC | Kernel | Status |
|--------|-----|--------|--------|
| OnePlus Ace 6T (PLR110) | SM8845 | 6.12.38 | Working |
| OnePlus 15 (CPH2749) | SM8850 | 6.12.23 | Working |
| OnePlus 13 (IN2060) | SM8750 | 6.6.89 | Working |
| **Nothing Phone (1)** | SM7325 | 5.4.302 | **In progress** |

### Nothing Phone (1) status

- [x] Kernel confirmed vulnerable (stock Nothing kernel)
- [x] Struct offsets for stock kernel (pahole, `lahaina_QGKI.config`)
- [x] Device target and offsets (`src/devices/spacewar/`)
- [x] kernel_phys_load from boot.img (0xa007f000)
- [ ] Kallsyms from **stock** kernel (need vulnerable boot.img flashed on device)
- [ ] PSELECT_SHIFT (need stock kernel running for kprobes)
- [ ] Source adaptation for 5.4 (configfs, splice, ashmem API differences)
- [ ] Device test
- [ ] APK wrapper app (base on [ghostlock-app](https://github.com/YuKongA/ghostlock-app))

Current offsets in the repo are from the **custom KSU kernel**, which is not the target. The target is the stock Nothing kernel. `STRUCT_OFFSETS_5_4` in `src/devices/offsets.h` holds the custom values — needs replacing with stock values once verified.

## Build

APKs are built automatically by [GitHub Actions](https://github.com/ang3lo-azevedo/ghostlock-nothing/actions) and published as [releases](https://github.com/ang3lo-azevedo/ghostlock-nothing/releases) on every push to `spacewar`.

To build locally:

```bash
# CLI binary
make TARGET=spacewar ANDROID_NDK_HOME=/path/to/ndk

# APK (requires Android SDK + NDK 29)
cd app && ./gradlew :app:assembleRelease
```

## Extracting offsets

### Struct offsets (pahole)

Clone the kernel source, run `make prepare`, then compile a dummy object and run pahole:

```bash
git clone --depth 1 --branch sm7325/s \
  https://github.com/NothingOSS/android_kernel_msm-5.4_nothing_sm7325

cd android_kernel_msm-5.4_nothing_sm7325
export ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-
scripts/kconfig/merge_config.sh arch/arm64/configs/defconfig \
  arch/arm64/configs/vendor/lahaina_QGKI.config
make olddefconfig prepare

aarch64-linux-gnu-gcc -std=gnu11 -D__KERNEL__ \
  -include include/generated/autoconf.h \
  -I. -Iinclude -Iarch/arm64/include \
  -nostdinc -g -c -o dummy.o dummy.c

pahole -C task_struct dummy.o
pahole -C rt_mutex_waiter dummy.o
pahole -C mm_struct dummy.o | grep owner
```

### Kallsyms (global symbols)

From the device running the **stock** (vulnerable) kernel:

```bash
# First disable kptr_restrict
adb shell su -c 'echo 0 > /proc/sys/kernel/kptr_restrict'
adb shell su -c 'cat /proc/kallsyms' > kallsyms_stock.txt

# kernel_phys_load
adb shell su -c 'grep -i "Kernel code" /proc/iomem'
# Subtract PE header size (0x1000) to get _text physical load address
```

### PSELECT_SHIFT (pselect stack layout)

On the device running the stock kernel:

```bash
adb shell su -c 'echo p:ds do_select fdsin=+0(%x1) > /sys/kernel/tracing/kprobe_events'
adb shell su -c 'echo p:rw rt_mutex_wait_proxy_lock waiter=%x2 >> /sys/kernel/tracing/kprobe_events'
adb shell su -c 'echo 1 | tee /sys/kernel/tracing/events/kprobes/ds/enable'
adb shell su -c 'echo 1 | tee /sys/kernel/tracing/events/kprobes/rw/enable'

# Trigger FUTEX_CMP_REQUEUE_PI, then read trace:
adb shell su -c 'cat /sys/kernel/tracing/trace'

# PSELECT_SHIFT = ((waiter & 0x3fff) - (fdsin & 0x3fff)) / 8 - 2
```

### 5.4 API differences

The exploit source (`src/core/`) assumes 6.x kernel APIs. Known differences on 5.4:

- `configfs_read_file` / `configfs_write_bin_file` (not `configfs_bin_read_iter` / `configfs_bin_write_iter`)
- `generic_file_splice_read` (not `copy_splice_read`)
- C ashmem (not Rust) — function names are direct symbols, not Rust-mangled
- `ashmem_show_fdinfo` does not exist on 5.4
- `rt_mutex_waiter` is 0x50 bytes (vs 0x70+ on 6.x)

## Credits

- [JoinChang/ghostlock-oneplus](https://github.com/JoinChang/ghostlock-oneplus)
- [NebuSec/CyberMeowfia](https://github.com/NebuSec/CyberMeowfia)
- [YuKongA/ghostlock-app](https://github.com/YuKongA/ghostlock-app)
- [BuSung-dev/Root-My-Galaxy](https://github.com/BuSung-dev/Root-My-Galaxy)
- [NothingOSS/android_kernel_msm-5.4_nothing_sm7325](https://github.com/NothingOSS/android_kernel_msm-5.4_nothing_sm7325)
- [William24hmar/nothing_android_kernel_sm7325](https://github.com/William24hmar/nothing_android_kernel_sm7325)

## License

For authorized security research and educational purposes only.
