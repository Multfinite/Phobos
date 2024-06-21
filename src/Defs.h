#pragma once
#include <Syringe.h>

#define ARES_NAME Ares.dll

#define ARES_3_PREFIX ares3
#define ARES_3_CRC32 0xAA4002FE
#define ARES_3p1_PREFIX ares3p1
#define ARES_3p1_CRC32 0x2474B6E7

#define DEFINE_ARES3_HOOK(hook, funcname, size) DEFINE_HOOK_EX(hook, funcname, size, ARES_3_PREFIX, ARES_NAME, ARES_3_CRC32)
#define DEFINE_ARES3_HOOK_AGAIN(hook, funcname, size) DEFINE_HOOK_EX_AGAIN(hook, funcname, size, ARES_3_PREFIX, ARES_NAME, ARES_3_CRC32)

#define DEFINE_ARES3p1_HOOK(hook, funcname, size) DEFINE_HOOK_EX(hook, funcname, size, ARES_3p1_PREFIX, ARES_NAME, ARES_3p1_CRC32)
#define DEFINE_ARES3p1_HOOK_AGAIN(hook, funcname, size) DEFINE_HOOK_EX_AGAIN(hook, funcname, size, ARES_3p1_PREFIX, ARES_NAME, ARES_3p1_CRC32)

#define REDEFINE_ARES3p1_AT(targetaddr, funcname, rettype, ...) REDEFINE_AT(targetaddr, funcname, prefix, name, checksum, rettype, __VA_ARGS__)
