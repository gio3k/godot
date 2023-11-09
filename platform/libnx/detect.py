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
    return [
        ("builtin_mbedtls", False),
        ("builtin_pcre2", False),
        ("builtin_miniupnpc", False),
        ("use_volk", False),  # Not supported
    ]


def configure(env):
    # devkitpro setup
    devkitpro = os.environ.get("DEVKITPRO")
    env["ENV"]["DEVKITPRO"] = devkitpro
    toolchain_bin = os.path.join(devkitpro, "devkitA64/bin")
    toolchain_portlibs = os.path.join(devkitpro, "portlibs/switch")
    toolchain_libnx = os.path.join(devkitpro, "libnx")

    # Compiler / toolchain setup
    env["CC"] = os.path.join(toolchain_bin, "aarch64-none-elf-gcc")
    env["CXX"] = os.path.join(toolchain_bin, "aarch64-none-elf-g++")
    env["LD"] = os.path.join(toolchain_bin, "aarch64-none-elf-ld")
    env["AR"] = os.path.join(toolchain_bin, "aarch64-none-elf-ar")
    env["RANLIB"] = os.path.join(toolchain_bin, "aarch64-none-elf-ranlib")

    env.Append(CPPPATH=[os.path.join(toolchain_portlibs, "include"), "#platform/libnx/compat/libc"])
    env.Append(CPPFLAGS=["-isystem", os.path.join(toolchain_libnx, "include")])
    env.Append(LIBPATH=[os.path.join(toolchain_portlibs, "lib"), os.path.join(toolchain_libnx, "lib")])
    env.Append(LINKFLAGS=[f"-specs={os.path.join(toolchain_libnx, 'switch.specs')}"])

    # Architecture setup
    arch_flags = ["-march=armv8-a+crc+crypto", "-mtune=cortex-a57", "-mtp=soft", "-fPIE"]
    env.Append(ASFLAGS=arch_flags)
    env.Append(CCFLAGS=arch_flags)
    env.Append(LINKFLAGS=arch_flags)

    # Portlibs / thirdparty
    def parse_portlib(args):
        pkg_config_path = os.path.join(toolchain_portlibs, "bin/aarch64-none-elf-pkg-config")
        env.ParseConfig(f"{pkg_config_path} {args}")

    if not env["builtin_pcre2"]:
        parse_portlib("libpcre2-32 --cflags --libs")

    if not env["builtin_miniupnpc"]:
        parse_portlib("miniupnpc --cflags --libs")

    if not env["builtin_mbedtls"]:
        env.Append(LIBS=["mbedtls", "mbedx509", "mbedcrypto"])

    # Platform setup
    env.Prepend(CPPPATH=["#platform/libnx"])
    env.Append(CPPDEFINES=["HORIZON_ENABLED", "__SWITCH__"])
    env.Append(CPPDEFINES=["UNIX_SOCKET_UNAVAILABLE"])
