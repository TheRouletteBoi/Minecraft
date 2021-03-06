#include "Memory.hpp"

uint32_t GetCurrentToc()
{
   uint32_t* entry_point = *reinterpret_cast<uint32_t**>(0x1001C); // ElfHeader->e_entry 
   return entry_point[1];
}

uint32_t sys_dbg_write_process_memory(uint32_t pid, void* address, const void* data, size_t size)
{
   system_call_4(905, (uint64_t)pid, (uint64_t)address, (uint64_t)size, (uint64_t)data);
   return_to_user_prog(uint32_t);
}

uint32_t sys_hen_write_process_memory(uint32_t pid, void* address, const void* data, size_t size)
{
   system_call_6(8, 0x7777, 0x32, (uint64_t)pid, (uint64_t)address, (uint64_t)data, (uint64_t)size);
   return_to_user_prog(uint32_t);
}

uint32_t WriteProcessMemory(uint32_t pid, void* address, const void* data, size_t size)
{
   static bool useHenSyscalls = false;

   if (!useHenSyscalls)
   {
      uint32_t write = sys_dbg_write_process_memory(pid, address, data, size);
      if (write == SUCCEEDED)
      {
         return write;
      }
   }

   useHenSyscalls = true;
   return sys_hen_write_process_memory(pid, address, data, size);
}