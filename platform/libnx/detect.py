import os
import platform


def get_name():
    return "Nintendo Switch (libnx)"


def can_build():
    if "DEVKITPRO" not in os.environ:
        print("Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitpro")
        return False

    return True


def get_opts():
    return []


def get_flags():
    return []


def configure(env):
    # devkitpro setup
    devkitpro = os.environ.get("DEVKITPRO")
    devkitpro_bin = os.path.join(devkitpro, "devkitA64/bin")

    # Compiler / toolchain setup
    env["CC"] = os.path.join(devkitpro_bin, "aarch64-none-elf-gcc")
    env["CXX"] = os.path.join(devkitpro_bin, "aarch64-none-elf-g++")
    env["LD"] = os.path.join(devkitpro_bin, "aarch64-none-elf-ld")
    env["AR"] = os.path.join(devkitpro_bin, "aarch64-none-elf-ar")
    env["RANLIB"] = os.path.join(devkitpro_bin, "aarch64-none-elf-ranlib")

    # Architecture setup
    arch_flags = ["-march=armv8-a+crc+crypto", "-mtune=cortex-a57", "-mtp=soft", "-fPIE"]
    env.Append(ASFLAGS=arch_flags)
    env.Append(CCFLAGS=arch_flags)
    env.Append(LINKFLAGS=arch_flags)

    # Platform setup
    env.Prepend(CPPPATH=["#platform/libnx"])
    env.Append(CPPDEFINES=["HORIZON_ENABLED"])
