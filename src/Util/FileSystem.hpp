#pragma once
#include <string>
#include <sys/prx.h>
#include <cell/cell_fs.h>
#undef vector
#include <vector>
#include "Util/Exports.hpp"

sys_prx_id_t GetModuleHandle(const char* moduleName);
sys_prx_module_info_t GetModuleInfo(sys_prx_id_t handle);
std::string GetModuleFilePath(const char* moduleName);