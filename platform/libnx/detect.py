import os
import platform


def get_name():
    return "Nintendo Switch (libnx)"


def can_build():
    return True


def get_opts():
    return []


def get_flags():
    return []


def configure(env):
    print(env)
