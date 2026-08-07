# <img src="https://raw.githubusercontent.com/ang3lo-azevedo/root-my-nothing/spacewar/app/app/src/main/res/mipmap-xxxhdpi/ic_launcher.png" width="32" height="32"> Root My Nothing

[![Release](https://img.shields.io/github/v/release/ang3lo-azevedo/root-my-nothing?style=flat-square)](https://github.com/ang3lo-azevedo/root-my-nothing/releases/latest)

CVE-2026-43499 (GhostLock) kernel exploit for **Nothing Phone (1)** (Spacewar, SM7325).

Fork of [JoinChang/ghostlock-oneplus](https://github.com/JoinChang/ghostlock-oneplus). APK builds automatically via GitHub Actions.

## Status

| Device | SoC | Kernel | Status |
|--------|-----|--------|--------|
| **Nothing Phone (1)** | SM7325 | 5.4.302 | In progress |

- [x] Kernel confirmed vulnerable (stock Nothing kernel, `remove_waiter` uses `current`)
- [x] Struct offsets extracted (pahole, `lahaina_QGKI.config`)
- [x] Device target and offsets (`src/devices/spacewar/`)
- [x] `kernel_phys_load` from boot.img (`0xa007f000`)
- [x] APK builds automatically and installs
- [ ] Kallsyms from stock kernel (need vulnerable boot.img flashed)
- [ ] `PSELECT_SHIFT` (need stock kernel + kprobes)
- [ ] 5.4 source adaptation (configfs, splice, ashmem API differences)
- [ ] Device test

## Install

[<img src="https://raw.githubusercontent.com/ImranR98/Obtainium/main/assets/graphics/badge_obtainium.png" alt="Get it on Obtainium" height="54">](https://apps.obtainium.imranr.dev/redirect?r=obtainium://add/https://github.com/ang3lo-azevedo/root-my-nothing)

Or download the latest APK from [Releases](https://github.com/ang3lo-azevedo/root-my-nothing/releases).

## Build

```bash
# CLI binary
make TARGET=spacewar ANDROID_NDK_HOME=/path/to/ndk

# APK (requires Android SDK + NDK 29)
cd app && ./gradlew :app:assembleRelease
```

## 5.4 API differences

The exploit source assumes 6.x kernel APIs. Known 5.4 differences:

- `configfs_read_file` / `configfs_write_bin_file` (not `configfs_bin_read_iter` / `configfs_bin_write_iter`)
- `generic_file_splice_read` (not `copy_splice_read`)
- C ashmem: direct symbols, not Rust-mangled
- `ashmem_show_fdinfo` does not exist on 5.4
- `rt_mutex_waiter` is 0x50 bytes (vs 0x70+ on 6.x)

## Credits

- [JoinChang/ghostlock-oneplus](https://github.com/JoinChang/ghostlock-oneplus)
- [YuKongA/ghostlock-app](https://github.com/YuKongA/ghostlock-app)
- [NebuSec/CyberMeowfia](https://github.com/NebuSec/CyberMeowfia)
- [BuSung-dev/Root-My-Galaxy](https://github.com/BuSung-dev/Root-My-Galaxy)
- [NothingOSS/android_kernel_msm-5.4_nothing_sm7325](https://github.com/NothingOSS/android_kernel_msm-5.4_nothing_sm7325)
- [William24hmar/nothing_android_kernel_sm7325](https://github.com/William24hmar/nothing_android_kernel_sm7325)

## License

For authorized security research and educational purposes only.
