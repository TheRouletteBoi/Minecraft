#pragma once
#include <cell/cell_fs.h>
#include <sys/sys_time.h>
#include <sys/timer.h>

#define SC_COBRA_SYSCALL8                             8
#define SYSCALL8_OPCODE_GET_DISC_TYPE                 0x7020
#define SYSCALL8_OPCODE_READ_PS3_DISC                 0x7021
#define SYSCALL8_OPCODE_FAKE_STORAGE_EVENT            0x7022
#define SYSCALL8_OPCODE_MAP_PATHS                     0x7964
#define BDVD_DRIVE                                    0x101000000000006ULL

int sys_storage_ext_get_disc_type(unsigned int* real_disctype, unsigned int* effective_disctype, unsigned int* fake_disctype);
int sys_storage_ext_fake_storage_event(uint64_t event, uint64_t param, uint64_t device);
int cobra_send_fake_disc_eject_event();
int sys_map_path(const char* oldpath, const char* newpath);
bool DoesFileExist(const char* fileName);
bool is_app_dir(const char* path, const char* app_name);
void set_app_home(const char* game_path);
void do_umount();