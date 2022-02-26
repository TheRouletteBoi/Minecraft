#include "SystemCalls.hpp"
#include "Exports.hpp"

int sys_storage_ext_get_disc_type(unsigned int* real_disctype, unsigned int* effective_disctype, unsigned int* fake_disctype)
{
   system_call_4(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_GET_DISC_TYPE, (uint64_t)(uint32_t)real_disctype, (uint64_t)(uint32_t)effective_disctype, (uint64_t)(uint32_t)fake_disctype);
   return_to_user_prog(int);
}

int sys_storage_ext_fake_storage_event(uint64_t event, uint64_t param, uint64_t device)
{
   system_call_4(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_FAKE_STORAGE_EVENT, event, param, device);
   return_to_user_prog(int);
}

int cobra_send_fake_disc_eject_event()
{
   unsigned int ejected_realdisc;

   sys_storage_ext_get_disc_type(&ejected_realdisc, NULL, NULL);

   sys_storage_ext_fake_storage_event(4, 0, BDVD_DRIVE);
   return sys_storage_ext_fake_storage_event(8, 0, BDVD_DRIVE);
}

int sys_map_path(const char* oldpath, const char* newpath)
{
   char* paths[1] = { (char*)oldpath }, * new_paths[1] = { (char*)newpath };
   system_call_4(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_MAP_PATHS, (uint64_t)(uint32_t)paths, (uint64_t)(uint32_t)new_paths, 1);
   return_to_user_prog(int);
}

bool DoesFileExist(const char* fileName)
{
   CellFsStat st;
   return (cellFsStat(fileName, &st) == 0);
}

bool is_app_dir(const char* path, const char* app_name)
{
   char eboot[263];
   snprintf(eboot, sizeof(eboot), "%s/%s/USRDIR/EBOOT.BIN", path, app_name);
   return DoesFileExist(eboot);
}

void set_app_home(const char* game_path)
{
   // force remove "/app_home", "/app_home/PS3_GAME", "/app_home/USRDIR"
   for (uint8_t retry = 0; retry < 3; retry++)
   {
      sys_map_path("/app_home", NULL);
      sys_map_path("/app_home/PS3_GAME", NULL);
      sys_map_path("/app_home/USRDIR", NULL);
   }

   sys_map_path("/app_home", game_path);

   sys_map_path("/app_home/PS3_GAME", game_path);

   // USRDIR as /app_home if game path has USRDIR/EBOOT.BIN
   if (game_path && is_app_dir(game_path, "."))
   {
      char new_path[512 + 8];
      snprintf(new_path, sizeof(new_path), "%s/USRDIR", game_path);
      sys_map_path("/app_home", new_path);
   }
}

void do_umount()
{
   cellFsUnlink("/dev_hdd0/tmp/game/ICON0.PNG"); // remove XMB disc icon

   sys_timer_usleep(20000);

   cellFsChmod("/dev_bdvd/PS3_GAME/SND0.AT3", 0777); // restore SND0 permissions of game mounted (JB folder)

   sys_map_path("/dev_bdvd/PS3/UPDATE", NULL); // unmap UPDATE from bdvd

   // map PKGLAUNCH cores folder to RETROARCH
   sys_map_path("/dev_hdd0//game/PKGLAUNCH", NULL);
   sys_map_path("/dev_bdvd/PS3_GAME/USRDIR/cores", NULL);
   sys_map_path("/app_home/PS3_GAME/USRDIR/cores", NULL);
   sys_map_path("/dev_bdvd/PS3_GAME", NULL);
   sys_map_path("/app_home/PS3_GAME", NULL);

   // unmap bdvd & apphome
   sys_map_path("/dev_bdvd", NULL);
   sys_map_path("//dev_bdvd", NULL);

   set_app_home(NULL); // unmap app_home

   // send fake eject
   sys_timer_usleep(4000);
   cobra_send_fake_disc_eject_event();
   sys_timer_usleep(4000);
}