# <img src="https://raw.githubusercontent.com/ang3lo-azevedo/root-my-nothing/spacewar/app/app/src/main/res/mipmap-xxxhdpi/ic_launcher.png" width="32" height="32"> Root My Nothing

[![Release](https://img.shields.io/github/v/release/ang3lo-azevedo/root-my-nothing?style=flat-square)](https://github.com/ang3lo-azevedo/root-my-nothing/releases/latest)

One-click root for the **Nothing Phone (1)** (Spacewar, SM7325) using the CVE-2026-43499 (GhostLock) kernel exploit. Gains temporary root access and installs KernelSU without unlocking the bootloader.

## Install

[<img src="https://raw.githubusercontent.com/ImranR98/Obtainium/main/assets/graphics/badge_obtainium.png" alt="Get it on Obtainium" height="54">](https://apps.obtainium.imranr.dev/redirect?r=obtainium://add/https://github.com/ang3lo-azevedo/root-my-nothing)

Or download the latest APK from [Releases](https://github.com/ang3lo-azevedo/root-my-nothing/releases).

Requires the [KernelSU manager](https://github.com/tiann/KernelSU/releases) to manage root permissions.

## How it works

**CVE-2026-43499 (GhostLock)** is a use-after-free in the Linux kernel's futex priority-inheritance code, present since kernel 2.6.39. The `pselect6` syscall copies `fd_set` data onto the kernel stack. When combined with the futex PI waiter mechanism, a freed stack frame is reclaimed as an `rt_mutex_waiter`. The rb-tree rebalance during PI chain walk writes controlled values to arbitrary kernel addresses, allowing privilege escalation to root.

The exploit then uses KernelSU's late-load mechanism to install a kernel module, providing persistent root management without modifying the boot image.

## Status

| Device | SoC | Kernel | Status |
|--------|-----|--------|--------|
| Nothing Phone (1) | SM7325 | 5.4.302 | In progress |

- [x] Kernel confirmed vulnerable
- [x] Struct offsets extracted
- [x] APK builds and installs
- [ ] Exploit working end-to-end

## Build

```bash
# CLI binary
make TARGET=spacewar ANDROID_NDK_HOME=/path/to/ndk

# APK
cd app && ./gradlew :app:assembleRelease
```

## Credits

- [JoinChang/ghostlock-oneplus](https://github.com/JoinChang/ghostlock-oneplus)
- [YuKongA/ghostlock-app](https://github.com/YuKongA/ghostlock-app)
- [NebuSec/CyberMeowfia](https://github.com/NebuSec/CyberMeowfia)
- [BuSung-dev/Root-My-Galaxy](https://github.com/BuSung-dev/Root-My-Galaxy)
- [NothingOSS/android_kernel_msm-5.4_nothing_sm7325](https://github.com/NothingOSS/android_kernel_msm-5.4_nothing_sm7325)
- [William24hmar/nothing_android_kernel_sm7325](https://github.com/William24hmar/nothing_android_kernel_sm7325)

## License

For authorized security research and educational purposes only.
