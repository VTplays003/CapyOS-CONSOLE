#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <filesystem>
#include <windows.h>
#include <psapi.h>
#include <intrin.h>

class Parser
{
public:
	std::string command;
	void parseCommand(std::string& command)
	{
		while (true)
		{
			std::getline(std::cin, command);
			if (command.substr(0, 4) == "help")
			{
				std::cout << "Welcome to CapyShell v0.2" << "\n";
				std::cout << "Here you can do loads of stuff!" << "\n";
				std::cout << "To start, to use a command, you will type a command like 'echo' or another command";
				std::cout << "Some commands will need fields like 'echo'" << "\n";
				std::cout << "Others will need flags like for the 'diagnostics' command, for example: 'diagnostics --usedRAM'";
				std::cout << " to only print the amount of usedRAM by CapyOS" << "\n";
				std::cout << "Here are the commands you can use:" << "\n";
				std::cout << "'help' - used to list the commands of CapyShell." << "\n";
				std::cout << "'echo (string)' - used to print things in the terminal. Please add a space between echo and the string" << "\n";
				std::cout << "'capy' - prints out a ASCII capybara" << "\n";
				std::cout << "'version' - used to get the version for CapyShell or CapyOS using --CapyOS flag." << "\n";
				std::cout << "'diagnostics' - used to display stats about the machine system running CapyOS." << "\n";
				std::cout << "This command has flags you can use. Availible flags:" << "\n";
				std::cout << "--usedRAM - displays the amount of used RAM" << "\n";
				std::cout << "--availibleRAM - displays the amount of availible RAM" << "\n";
				std::cout << "--totalRAM - displays the total amount of RAM" << "\n";
				std::cout << "--CPU - displays the CPU information" << "\n";
				std::cout << "--Storage - displays the storage information" << "\n";
				std::cout << "WARNING: Due to C++ not having a standard way of measuring system data, the feature is only availible on Windows." << "\n";
				std::cout << "'exit' - used to return back to CapybaraSystemsOS" << "\n";
				std::cout << "Put these keywords/commmands at the beginning of the line or else the parser won't be able to process them correctly!" << "\n";
			}
			if (command.substr(0, 4) == "echo")
			{
				std::cout << command.substr(5) << "\n";
			}
			else if (command.length() > 5 && command.substr(0, 4) == "echo")
			{
				std::cout << "You need to include a string literal field after the 'echo' command to print things" << "\n";
			}
			if (command.substr(0, 4) == "capy")
			{
				std::cout << "⠀⠀⢀⣀⠤⠿⢤⢖⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << "\n";
				std::cout << "⡔⢩⠂⠀⠒⠗⠈⠀⠉⠢⠄⣀⠠⠤⠄⠒⢖⡒⢒⠂⠤⢄⠀⠀⠀⠀" << "\n";
				std::cout << "⠇⠤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠈⠀⠈⠈⡨⢀⠡⡪⠢⡀⠀" << "\n";
				std::cout << "⠈⠒⠀⠤⠤⣄⡆⡂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠢⠀⢕⠱⠀" << "\n";
				std::cout << "⠀⠀⠀⠀⠀⠈⢳⣐⡐⠐⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠁⠇" << "\n";
				std::cout << " ⠀⠀⠀⠀⠀⠀⠀⠑⢤⢁⠀⠆⠀⠀⠀⠀⠀⢀⢰⠀⠀⠀⡀⢄⡜⠀" << "\n";
				std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠘⡦⠄⡷⠢⠤⠤⠤⠤⢬⢈⡇⢠⣈⣰⠎⠀" << "\n";
				std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣃⢸⡇⠀⠀⠀⠀⠀⠈⢪⢀⣺⡅⢈⠆⠀⠀" << "\n";
				std::cout << "  ⠀⠀⠀⠀⠀⠀⠀⠶⡿⠤⠚⠁⠀⠀⠀⢀⣠⡤⢺⣥⠟⢡⠃⠀⠀⠀" << "\n";
			}
			if (command.substr(0, 7) == "version")
			{
				if (command.find("--CapyOS") != std::string::npos)
				{
					std::cout << "CapyOS version: v0.2.7" << "\n";
				}
				else
				{
					std::cout << "CapyShell version: v0.2" << "\n";
				}
			}
			if (command.substr(0, 11) == "diagnostics")
			{
				if (command.find("--usedRAM") != std::string::npos)
				{
					MEMORYSTATUSEX statex;
					statex.dwLength = sizeof(statex);
					GlobalMemoryStatusEx(&statex);
					std::cout << "Used RAM: " << (statex.ullTotalPhys - statex.ullAvailPhys) / (1024 * 1024) << " MB" << "\n";
				}
				else if (command.find("--availibleRAM") != std::string::npos)
				{
					MEMORYSTATUSEX statex;
					statex.dwLength = sizeof(statex);
					GlobalMemoryStatusEx(&statex);
					std::cout << "Availible RAM: " << statex.ullAvailPhys / (1024 * 1024) << " MB" << "\n";
				}
				else if (command.find("--totalRAM") != std::string::npos)
				{
					MEMORYSTATUSEX statex;
					statex.dwLength = sizeof(statex);
					GlobalMemoryStatusEx(&statex);
					std::cout << "Total RAM: " << statex.ullTotalPhys / (1024 * 1024) << " MB" << "\n";
				}
				//"oh no C style arrays!?!?!?!?!?"
				//this requires very low level code hold with me here
				//tbh i just saw some code and copied it ngl, too hard man. i dont even understand whats going on here.
				else if (command.find("--CPU") != std::string::npos)
				{
					int regs[4] = {0};
					__cpuid(regs, 0);
					char vendor[13];	
					std::memcpy(vendor + 0, &regs[1], 4); 
					std::memcpy(vendor + 4, &regs[3], 4); 
					std::memcpy(vendor + 8, &regs[2], 4); 
					std::cout << "CPU Vendor: " << vendor << "\n"; 
					char brand[49] = { 0 };
					for (unsigned int i = 0; i < 3; ++i) {
						__cpuid(regs, 0x80000002 + i);
						std::memcpy(brand + (i * 16), regs, sizeof(regs));
					}
					std::cout << "Model:  " << brand << "\n";
					DWORD bufferSize = 0;
					GetLogicalProcessorInformation(nullptr, &bufferSize);
					std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION> buffer(
						bufferSize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION)
					);

					if (!GetLogicalProcessorInformation(buffer.data(), &bufferSize)) {
						std::cerr << "Failed to query processor topology.\n";
						return;
					}
					int physical_cores = 0;
					int logical_processors = 0;
					DWORD l1_cache = 0, l2_cache = 0, l3_cache = 0;
					for (const auto& info : buffer) {
						if (info.Relationship == RelationProcessorCore) {
							physical_cores++;
							// Count set bits in ProcessorMask to get logical threads for this core
							ULONG_PTR mask = info.ProcessorMask;
							while (mask) {
								logical_processors += (mask & 1);
								mask >>= 1;
							}
						}
						else if (info.Relationship == RelationCache) {
							if (info.Cache.Level == 1) l1_cache += info.Cache.Size;
							else if (info.Cache.Level == 2) l2_cache += info.Cache.Size;
							else if (info.Cache.Level == 3) l3_cache += info.Cache.Size;
						}
					}

					std::cout << "Physical Cores:     " << physical_cores << "\n";
					std::cout << "Logical Processors: " << logical_processors << "\n";
					std::cout << "Total L1 Cache:     " << (l1_cache / 1024) << " KB\n";
					std::cout << "Total L2 Cache:     " << (l2_cache / 1024) << " KB\n";
					std::cout << "Total L3 Cache:     " << (l3_cache / (1024 * 1024)) << " MB\n";
				}
				else if (command.find("--Storage") != std::string::npos)
				{
					std::error_code ec;
					std::filesystem::space_info si = std::filesystem::space("C:/", ec);
					std::cout << "Total Storage: " << si.capacity / (1024 * 1024 * 1024) << " GB" << "\n";
					std::cout << "Used Storage: " << (si.capacity - si.free) / (1024 * 1024 * 1024) << " GB" << "\n";
					std::cout << "Available Storage: " << si.free / (1024 * 1024 * 1024) << " GB" << "\n";
				}
				else
				{
					MEMORYSTATUSEX statex;
					statex.dwLength = sizeof(statex);
					GlobalMemoryStatusEx(&statex);
					std::cout << "Total RAM: " << statex.ullTotalPhys / (1024 * 1024) << " MB" << "\n";
					std::cout << "Used RAM: " << (statex.ullTotalPhys - statex.ullAvailPhys) / (1024 * 1024) << " MB" << "\n";
					std::cout << "Availible RAM: " << statex.ullAvailPhys / (1024 * 1024) << " MB" << "\n";
					int regs[4] = { 0 };
					__cpuid(regs, 0);
					char vendor[13];
					std::memcpy(vendor + 0, &regs[1], 4);
					std::memcpy(vendor + 4, &regs[3], 4);
					std::memcpy(vendor + 8, &regs[2], 4);
					std::cout << "CPU Vendor: " << vendor << "\n";
					char brand[49] = { 0 };
					for (unsigned int i = 0; i < 3; ++i) {
						__cpuid(regs, 0x80000002 + i);
						std::memcpy(brand + (i * 16), regs, sizeof(regs));
					}
					std::cout << "Model:  " << brand << "\n";
					DWORD bufferSize = 0;
					GetLogicalProcessorInformation(nullptr, &bufferSize);
					std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION> buffer(
						bufferSize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION)
					);

					if (!GetLogicalProcessorInformation(buffer.data(), &bufferSize)) {
						std::cerr << "Failed to query processor topology.\n";
						return;
					}
					int physical_cores = 0;
					int logical_processors = 0;
					DWORD l1_cache = 0, l2_cache = 0, l3_cache = 0;
					for (const auto& info : buffer) {
						if (info.Relationship == RelationProcessorCore) {
							physical_cores++;
							// Count set bits in ProcessorMask to get logical threads for this core
							ULONG_PTR mask = info.ProcessorMask;
							while (mask) {
								logical_processors += (mask & 1);
								mask >>= 1;
							}
						}
						else if (info.Relationship == RelationCache) {
							if (info.Cache.Level == 1) l1_cache += info.Cache.Size;
							else if (info.Cache.Level == 2) l2_cache += info.Cache.Size;
							else if (info.Cache.Level == 3) l3_cache += info.Cache.Size;
						}
					}

					std::cout << "Physical Cores:     " << physical_cores << "\n";
					std::cout << "Logical Processors: " << logical_processors << "\n";
					std::cout << "Total L1 Cache:     " << (l1_cache / 1024) << " KB\n";
					std::cout << "Total L2 Cache:     " << (l2_cache / 1024) << " KB\n";
					std::cout << "Total L3 Cache:     " << (l3_cache / (1024 * 1024)) << " MB\n";
					std::error_code ec;
					std::filesystem::space_info si = std::filesystem::space("C:/", ec);
					std::cout << "Total Storage: " << si.capacity / (1024 * 1024 * 1024) << " GB" << "\n";
					std::cout << "Used Storage: " << (si.capacity - si.free) / (1024 * 1024 * 1024) << " GB" << "\n";
					std::cout << "Available Storage: " << si.free / (1024 * 1024 * 1024) << " GB" << "\n";

				}
			}
			if (command.substr(0, 4) == "exit")
			{
				std::cout << "Exiting CapyShell..." << "\n";
				break;
			}
		}
		return;
	}
	void initTerminal()
	{
		int waitTime = 50;
		std::cout << "Loading CapyShell.hpp..." << "\n";
		for (int i = 0; i < 244; i++)
		{
			std::cout << "Loading line:" << i << "\n";
		}
		std::cout << "Getting system info..." << "\n";
		std::cout << "Complete!" << "\n";
		std::cout << "You are in the CapyShell terminal. Use 'exit' to go back to CapybaraSystemsOS." << "\n";
		std::cout << "Please type a command. (Beginners should use 'help' first)" << "\n";
	}
};