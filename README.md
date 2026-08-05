# ghostlock-nothing

Fork of [JoinChang/ghostlock-oneplus](https://github.com/JoinChang/ghostlock-oneplus) with **Nothing Phone (1)** (Spacewar, SM7325) support.

## Vulnerability

CVE-2026-43499 (GhostLock): use-after-free in the Linux kernel rtmutex futex PI code. Affects Linux 2.6.39 through 7.1-rc1.

## Devices

| Device | SoC | Kernel | Status |
|--------|-----|--------|--------|
| OnePlus Ace 6T (PLR110) | SM8845 | 6.12.38 | Working |
| OnePlus 15 (CPH2749) | SM8850 | 6.12.23 | Working |
| OnePlus 13 (IN2060) | SM8750 | 6.6.89 | Working |
| **Nothing Phone (1)** | SM7325 | 5.4.302 | **In progress** |

### Nothing Phone (1) status

- [x] Kernel confirmed vulnerable
- [x] Struct offsets extracted (pahole, 5.4 spacewar_defconfig)
- [x] Device target and offsets (`src/devices/spacewar/`)
- [ ] Kallsyms offsets (need dump from device)
- [ ] pselect stack layout (need on-device kprobes)
- [ ] Source adaptation for 5.4
- [ ] Device test

## Build

```bash
# Nothing Phone (1)
make TARGET=spacewar ANDROID_NDK_HOME=/path/to/ndk

# Other devices (upstream)
make ANDROID_NDK_HOME=/path/to/ndk
```

## Kallsyms and pselect layout

Needs a running device with root (KernelSU works):

```bash
# Dump kallsyms for global symbol offsets
adb shell su -c 'cat /proc/kallsyms' > kallsyms.txt

# kernel_phys_load
adb shell su -c 'grep -i "Kernel code" /proc/iomem'
# subtract 0x10000 (_stext - _text)

# PSELECT_SHIFT via kprobes
adb shell su -c 'echo "p:ds do_select fdsin=+0(%x1)" >> /sys/kernel/tracing/kprobe_events'
adb shell su -c 'echo "p:rw rt_mutex_wait_proxy_lock waiter=%x2" >> /sys/kernel/tracing/kprobe_events'
# trigger FUTEX_CMP_REQUEUE_PI, then:
#   PSELECT_SHIFT = ((waiter & 0x3fff) - (fdsin & 0x3fff)) / 8 - 2
```

## Adding devices

Extract offsets from boot.img:

```bash
python -c "import struct; d=open('boot.img','rb').read(); open('kernel','wb').write(d[4096:4096+struct.unpack_from('<I',d,8)[0]])"
python tools/extract_target.py   # kallsyms
python tools/extract_btf.py kernel   # struct fields (if CONFIG_DEBUG_INFO_BTF=y)
```

Create `src/devices/<name>/offsets.h` and `src/devices/<name>/target.h`. Use `STRUCT_OFFSETS_5_4`, `STRUCT_OFFSETS_6_6`, or `STRUCT_OFFSETS_6_12` based on kernel version.

## Credits

- [JoinChang/ghostlock-oneplus](https://github.com/JoinChang/ghostlock-oneplus)
- [NebuSec/CyberMeowfia](https://github.com/NebuSec/CyberMeowfia)
- [William24hmar/nothing_android_kernel_sm7325](https://github.com/William24hmar/nothing_android_kernel_sm7325)

## License

For authorized security research and educational purposes only.
