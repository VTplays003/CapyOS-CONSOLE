//boost includes
#include <boost/version.hpp>
#include <boost/beast.hpp>
//regular includes
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <windows.h>
#include <fstream>
#include <unordered_map>
#include <map>
#include <memory>
#include "CPPLingo_Player.h"
//THIS IS A SOURCE FILE. PLEASE DO NOT USE IT AS A HEADER.
//the reason i dont use using namespace std; is because I want to learn to tolerate std:: and its only an extra 5 characters to type :)
//variables (global)
struct Task
{
	std::string title;
	std::string description;
	std::chrono::system_clock::time_point date;
	int priority;
	bool completed;
};
std::vector<Task> tasks;


static void CPPLingo()
{
	Player player;
	LingoManual CPPmanual;
	PlayerProgression progression;
	SaveSystem SaveSystem;
	Inventory inventory;
	AcademySystem academySystem;
	CombatSystem combatSystem;
	std::ofstream testfile("testsave.txt");
	std::cout << "Welcome to C++ Lingo Adventure!" << "\n";
	std::cout << "This game supports saving. The game auto saves, but you have to type 'load' to load your data." << "\n";
	std::cout << "Testing save file..." << "\n";
	if (!testfile)
	{
		std::cout << "Oh noes! The save file system doesn't work! Try resetting it." << "\n";
	}
	std::cout << "Test success!" << "\n";
	testfile << "you suck at coding you capybara" << "\n";
	testfile.close();
	std::cout << "Type load to load your save file, or type anything else to start a new game." << "\n";
	std::getline(std::cin, SaveSystem.loadCharacter);
	if (SaveSystem.loadCharacter == "load")
	{
		SaveSystem.LoadGame(player, progression, inventory.getInventory(), inventory.getDatabase());
	}
	while (!player.characterVerifcation)
	{
		std::cout << "Anyway, let's start creating your character." << "\n";
		std::cout << "Choose your character's name." << "\n";
		std::getline(std::cin, player.name);
		std::cout << "Now, choose your race from the following. (Type the number)" << "\n";
		std::cout << "1. Capybara" << "\n";
		std::cout << "2. Elf" << "\n";
		std::cout << "3. Fairy" << "\n";
		std::cout << "4. Demon" << "\n";
		std::cout << "5. Angel" << "\n";
		std::getline(std::cin, player.input);
		player.CharacterCustomizationRace(std::stoi(player.input));
		std::cout << "Now, choose your gender from the following. (Type the number)" << "\n";
		std::cout << "1. Male" << "\n";
		std::cout << "2. Female" << "\n";
		std::cout << "3. Non-Binary" << "\n";
		std::getline(std::cin, player.input);
		player.CharacterCustomizationGender(std::stoi(player.input));
		std::cout << "Please check that your player info is correct. (Y/Yes to proceed. Anything else is treated as a No)" << "\n";
		std::cout << "Name: " << player.name << "\n";
		std::cout << "Race: " << player.RaceToString(player) << "\n";
		std::cout << "Gender: " << player.GenderToString(player) << "\n";
		std::getline(std::cin, player.characterComfirmation);
		if (player.characterComfirmation == "Yes" || player.characterComfirmation == "Y" || player.characterComfirmation == "y" || player.characterComfirmation == "yes" && player.gender != Gender::Unknown && player.race != Race::undefined)
		{
			std::cout << "Character creation complete!" << "\n";
			SaveSystem.SaveGame(player, progression, inventory.getInventory());
			player.characterVerifcation = true;
			break;
		}
		else
		{
			std::cout << "Correct your details and then come back." << "\n";
			std::cout << "Make sure all fields are filled correctly. (No unknown values)" << "\n";
		}
	}
	if (progression.prologue1_1)
	{
		std::cout << "Puzzle skipped due to SaveFile.Progression.Prologue1_1. (Result: True)" << "\n";
	}
	else 
	{
		std::cout << "Prologue - Act 1" << "\n";
		std::cout << "You arrive at the kingdom gates." << "\n";
		std::cout << "The sign says: Kingdom of CapyLingo" << "\n";
		std::cout << "Your goal is to cross the gates into the kingdom." << "\n";
		std::cout << "To do that, you need to solve the Lingo Box near the gate." << "\n";
	}
	while (!progression.prologue1_1)
	{
		std::cout << "Here are your options: " << "\n";
		std::cout << "(For actions, use the action name. You can also use the choice number.)" << "\n";
		std::cout << "1. Interact with the box" << "\n";
		std::cout << "2. Rest at the tent" << "\n";
		std::getline(std::cin, player.action);
		if (player.action == "Interact with the box" || player.action == "1")
		{
			std::cout << "You go close to the box." << "\n";
			std::cout << "The box has a hint." << "\n";
			std::cout << "C__" << "\n";
			std::cout << "You must guess the answer." << "\n";
			std::cout << "Remember, you also have a manual. (Type 'manual' to open it. You can use it at any time)" << "\n";
			std::getline(std::cin, player.lingoAnswer);
			if (player.lingoAnswer == "C++")
			{
				std::cout << "You got it correct!" << "\n";
				progression.prologue1_1 = true;
				SaveSystem.SaveGame(player, progression, inventory.getInventory());
				break;
			}
			else if (player.lingoAnswer == "manual")
			{
				std::cout << "You go back to your tent to read your manual..." << "\n";
				CPPmanual.viewPage();
				std::cout << "You come back outside.";
			}
			else
			{
				std::cout << "The answer is wrong. You go back to the nearby tent to rest." << "\n";
			}
		}
		else if (player.action == "Rest at the tent" || player.action == "2")
		{
			std::cout << "You rest in the tent, but you aren't going anywhere now unless you solve that puzzle." << "\n";
			std::cout << "You should probably interact with the box." << "\n";
		}
	}
	std::cout << "The gate opens, and you enter the kingdom" << "\n";
	std::cout << "Prologue - Act 2" << "\n";
	std::cout << "You have arrived at the City Center" << "\n";
	std::cout << "Now would probably be a good time to: " << "\n";
	std::cout << "1. Get supplies" << "\n"; 
	std::cout << "2. Sign up in the Guild" << "\n";
	std::cout << "3. Finding somewhere to live." << "\n";
	std::cout << "Perferably, you should start with 2 and 3. But it's up to you." << "\n";
	std::cout << "(You can use the choice number or the name)" << "\n";
	std::cout << "So, what will it be?" << "\n";
	while (!progression.prologue1_2)
	{
		std::cout << "You have completed: " << "\n" 
				  << (progression.prologue1_2_1 ? "Task 1" : "(Not complete)") << "\n"
				  << (progression.prologue1_2_2 ? "Task 2" : "(Not complete)") << "\n" 
				  << (progression.prologue1_2_3 ? "Task 3" : "(Not complete)") << "\n";
		if (progression.prologue1_2_1 && progression.prologue1_2_2 && progression.prologue1_2_3)
		{
			progression.prologue1_2 = true;
			SaveSystem.SaveGame(player, progression, inventory.getInventory());
			break;
		}
		std::getline(std::cin, player.action);
		if (player.action == "1" || player.action == "Get supplies")
		{
			if (player.hasGuildCard == true)
			{
				std::cout << "On arrival, you find that the enterance is locked behind another Lingo Box puzzle." << "\n";
				std::cout << "It has a hint on the box" << "\n";
				std::cout << "true or false" << "\n";
				std::cout << "You need to solve it." << "\n";
				std::getline(std::cin, player.lingoAnswer);
				if (player.lingoAnswer == "bool" || player.lingoAnswer == "boolean")
				{
					std::cout << "You got it correct!" << "\n";
					std::cout << "You enter the store and get your beginner tools." << "\n";
					std::cout << "Shopkeeper: Welcome! I heard you just joined the guild. Here are your tools!" << "\n";
					inventory.addItem("Beginner Uniform");
					inventory.addItem("Beginner Armor");
					inventory.addItem("Beginner Sword");
					progression.prologue1_2_1 = true;
				}
				else if (player.lingoAnswer == "manual")
				{
					CPPmanual.viewPage();
				}
				else
				{
					std::cout << "The answer is wrong. You go back outside but you really need to get your supplies." << "\n";
				}
			}
			else
			{
				std::cout << "You arrive at the shop only to find out..." << "\n";
				std::cout << "Shopkeeper: Sorry, you need a guild card to purchase supplies." << "\n";
			}
		}
		else if (player.action == "2" || player.action == "Sign up in the Guild")
		{
			if (!player.hasGuildCard)
			{
				std::cout << "You go to the guild conviently named 'Lingo Guild' and head in to get your guild membership and card." << "\n";
				std::cout << "Clerk: Welcome to the guild! Just sign this form and we'll get you that card." << "\n";
				std::cout << "Lingo Guild Registration Form" << "\n";
				for (int i = 0; i < 35; i++)
				{
					std::cout << "-";
				}
				std::cout << "\n"; 
				std::cout << "Name: " << player.name << "\n";
				std::cout << "Race: " << player.RaceToString(player) << "\n";
				std::cout << "Gender: " << player.GenderToString(player) << "\n";
				std::cout << "You sign the form and your form is stampped. You now have a guild card!" << "\n";
				std::cout << "⣀⠤⠿⢤⢖⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
						<< "⡔⢩⠂⠀⠒⠗⠈⠀⠉⠢⠄⣀⠠⠤⠄⠒⢖⡒⢒⠂⠤⢄⠀⠀⠀ \n"
						<< "⠇⠤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠈⠀⠈⠈⡨⢀⠡⡪⠢⡀⠀\n"
						<< "⠈⠒⠀⠤⠤⣄⡆⡂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠢⠀⢕⠱⠀\n"
						<< "⠀⠀⠀⠀⠀⠈⢳⣐⡐⠐⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠁⠇\n"
						<< "       ⠑⢤⢁⠀⠆⠀⠀⠀⠀⠀⢀⢰⠀⠀⠀⡀⢄⡜ \n"
						<< "         ⠘⡦⠄⡷⠢⠤⠤⠤⠤⢬⢈⡇⢠⣈⣰⠎ \n"
						<< "          ⣃⢸⡇⠀⠀⠀⠀⠀⠈⢪⢀⣺⡅⢈⠆ \n"
						<< "⠀⠀⠀⠀⠀⠀⠀ ⠶⡿⠤⠚⠁⠀⠀⠀⢀⣠⡤⢺⣥⠟⢡⠃⠀ \n";
				player.hasGuildCard = true;
				SaveSystem.SaveGame(player, progression, inventory.getInventory());
				std::cout << "Clerk: Here is your guild card! Thanks for joining the guild!" << "\n";
				std::cout << "Clerk: By the way, here's a little welcoming gift for you!" << "\n";
				std::cout << "You unlocked Page 2 of the manual!" << "\n";
				CPPmanual.unlockPage(2);
				std::cout << "Clerk: You'll need some tools to become a warrior, and a few classes in the academy. Go to the shop to get supplies" << "\n";
				std::cout << "Clerk: Also, you can now find a place to live in the guild academy dorms." << "\n";
				progression.prologue1_2_2 = true;
			}
			else if (player.hasGuildCard)
			{
				std::cout << "You already have a guild card, the guild just closed so they can't respond to any requests right now." << "\n";
			}
			
		}
		else if (player.action == "3" || player.action == "Finding somewhere to live.")
		{
			if (player.hasGuildCard)
			{
				std::cout << "You find your dorm room in the guild academy." << "\n";
				player.respawnPos = "House_1";
				progression.prologue1_2_3 = true;
			}
			else {
				std::cout << "You try to find a place to live, but you don't have a guild card, so no one wants to sell you a home." << "\n";
			}
		}
		else
		{
			std::cout << "dude, you need to TYPE a choice its simple." << "\n";
		}
	}
	std::cout << "Prologue - Act 3" << "\n";
	std::cout << "You wake up for your first time in the guild academy." << "\n";
	std::cout << "You go to the academy clerk and register for your classes" << "\n";
	auto classDatabase = academySystem.AccessClasses();
	academySystem.addClass(classDatabase, player);
	std::cout << "The bell rings and you attend your class" << "\n";
	academySystem.attendClass(academySystem.AccessEnrolled(), combatSystem, player);
}

static void CapyShell()
{
	//memory commands are in the works
	std::string command;
	std::cout << "You are in the CapyShell terminal. Use 'exit' to go back to CapybaraSystemsOS." << "\n";
	std::cout << "Please type a command. (Beginners should use 'help' first)" << "\n";
	while (true)
	{
		std::getline(std::cin, command);
		if (command == "help")
		{
			std::cout << "'help' - used to list the commands of CapyShell." << "\n";
			std::cout << "'echo (string)' - used to print things in the terminal. Please add a space between echo and the string" << "\n";
			std::cout << "'capy' - prints out a ASCII capybara" << "\n";
			std::cout << "'version' - used to get the version for CapyShell" << "\n";
			std::cout << "'exit' - used to return back to CapybaraSystemsOS" << "\n";
			std::cout << "Put these keywords/commmands at the beginning of the line!" << "\n";
		}
		else if (command.contains("echo"))
		{
			std::size_t echo_pos = command.find("echo");
			std::string result = command.substr(echo_pos + 5);
			std::cout << result << "\n";
		}
		else if (command.contains("capy"))
		{
			std::cout << "⠀⠀⢀⣀⠤⠿⢤⢖⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
					  << "⡔⢩⠂⠀⠒⠗⠈⠀⠉⠢⠄⣀⠠⠤⠄⠒⢖⡒⢒⠂⠤⢄⠀⠀⠀ \n"
					  << "⠇⠤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠈⠀⠈⠈⡨⢀⠡⡪⠢⡀⠀\n"
					  << "⠈⠒⠀⠤⠤⣄⡆⡂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠢⠀⢕⠱⠀\n"
					  << "⠀⠀⠀⠀⠀⠈⢳⣐⡐⠐⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠁⠇\n"
					  << "       ⠑⢤⢁⠀⠆⠀⠀⠀⠀⠀⢀⢰⠀⠀⠀⡀⢄⡜ \n"
					  << "         ⠘⡦⠄⡷⠢⠤⠤⠤⠤⢬⢈⡇⢠⣈⣰⠎ \n"
					  << "          ⣃⢸⡇⠀⠀⠀⠀⠀⠈⢪⢀⣺⡅⢈⠆ \n"
					  << "⠀⠀⠀⠀⠀⠀⠀ ⠶⡿⠤⠚⠁⠀⠀⠀⢀⣠⡤⢺⣥⠟⢡⠃⠀ \n";
				std::cout << "Credits to TextArtCopy.com" << "\n";
		}
		else if (command.contains("version"))
		{
			std::cout << "CapyShell, Version 0.0.1.0" << "\n";
		}
		else if (command.contains("exit"))
		{
			break;
			return;
		}
		else {
			std::cout << "invalid" << "\n";
		}
	}
}

static void TaskApp()
{
	std::cout << "Welcome to the Task App!" << "\n";
	while (true)
	{
		int waitTime = 30;
		std::string taskChoice;
		int taskSelection = 0;
		if (tasks.empty())
		{
			tasks.push_back({ "Default Task", "This is the task that shows when you first open the app", std::chrono::system_clock::now(), 1, false });
		}
		std::size_t totalTasks = tasks.size();
		std::cout << "You have: " << totalTasks << " tasks" << "\n";
		std::cout << "Here are your tasks:" << "\n";
		for (const auto& task : tasks)
		{
			for (int i = 0; i < 50; i++)
			{
				std::cout << "-";
				std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
			}
			std::cout << "\n";
			std::cout << "Title: " << task.title << "\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
			std::cout << "Description: " << task.description << "\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
			auto time = std::chrono::system_clock::to_time_t(task.date);
			std::tm timeinfo;
			localtime_s(&timeinfo, &time);
			std::cout << "Date: " << std::put_time(&timeinfo, "%m/%d/%Y") << "\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
			std::cout << "Priority: " << task.priority << "\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
			std::cout << "Completed: " << (task.completed ? "Yes" : "No") << "\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
		}
		for (int i = 0; i < 50; i++)
		{
			std::cout << "-";
			std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
		}
		std::cout << "\n";
		std::cout << "Choose a option: " << "\n";
		std::cout << "1. Create new task" << "\n";
		std::cout << "2. Mark task as Done" << "\n";
		std::cout << "3. Delete tasks" << "\n";
		std::cout << "4. Log out" << "\n";
		std::getline(std::cin, taskChoice);
		if (taskChoice == "1" || taskChoice == "Create new task")
		{
			std::string newTitle;
			std::string newDescription;
			std::string priorityLevel;
			std::cout << "Insert new task title here: " << "\n";
			std::getline(std::cin, newTitle);
			std::cout << "Insert new task description here: " << "\n";
			std::getline(std::cin, newDescription);
			std::cout << "Insert priority number (ONLY NUMBERS): ";
			std::getline(std::cin, priorityLevel);
			int priorityNumber = std::stoi(priorityLevel);
			tasks.push_back({ newTitle, newDescription, std::chrono::system_clock::now(), priorityNumber, false });
		}
		else if (taskChoice == "2" || taskChoice == "Mark task as Done")
		{
			std::cout << "Due to how vector<> works, the first task will be '0', the second will be '1' and so on. NUMBERS ONLY." << "\n";
			std::cout << "Please choose the task number you want to mark as Done:" << "\n";
			std::getline(std::cin, taskChoice);
			try
			{
				int markedTask = std::stoi(taskChoice);
				if (markedTask >= 0 && markedTask < static_cast<int>(tasks.size()))
				{
					tasks.at(markedTask).completed = true;
					std::cout << "Marked task as done!" << "\n";
				}
				else {
					std::cout << "Not valid." << "\n";
				}
			}
			catch (const std::invalid_argument)
			{
				std::cout << "Numbers only please." << "\n";
			}
			catch (const std::out_of_range)
			{
				std::cout << "Task doesn't exist. Out of range.";
			}
		}
		else if (taskChoice == "3" || taskChoice == "Delete tasks")
		{
			std::cout << "vector<> stuff. First item is 0, second item is 1, etc. NUMBERS ONLY." << "\n";
			std::cout << "Please select the task number to delete." << "\n";
			std::getline(std::cin, taskChoice);
			try
			{
				int markedTask = std::stoi(taskChoice);
				tasks.erase(tasks.begin() + markedTask);
			}
			catch (const std::invalid_argument)
			{
				std::cout << "Numbers only please." << "\n";
			}
			catch (const std::out_of_range)
			{
				std::cout << "Task doesn't exist. Out of range.";
			}

		}
		else if (taskChoice == "4" || taskChoice == "Log out")
		{
			break;
			return;
		}
		else {
			std::cout << "Invalid choice selected. Restarting app..." << "\n";
		}
	}
}

static void CapybaraSystemsOS()
{
	std::string openedApp;
	int waitTime = 30;
	while (true)
	{
		std::cout << "Welcome to CapybaraSystemsOS - v0.2!" << "\n";
		for (int i = 0; i < 36; i++)
		{
			std::cout << "-";
			std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
		}
		std::cout << "\n";
		std::cout << "Installed Apps:" << "\n";
		std::cout << "1. Task App" << "\n";
		std::cout << "2. Capyshell" << "\n";
		std::cout << "3. C++ Lingo" << "\n";
		std::cout << "Select an app. (Type App Number or App Name)" << "\n";
		std::getline(std::cin, openedApp);
		if (openedApp == "1" || openedApp == "Task App")
		{
			TaskApp();
		}
		else if (openedApp == "2" || openedApp == "Capyshell")
		{
			CapyShell();
		}
		else if (openedApp == "3" || openedApp == "C++ Lingo")
		{
			CPPLingo();
		}
		else
		{
			std::cout << "Invalid app selected" << "\n";
		}
	}
}

static void installCapyComputer()
{
	std::string username;
	std::string password;
	std::string OS;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 50);
	std::cout << "Please choose a username" << "\n";
	std::getline(std::cin, username);
	std::cout << "Please choose a password" << "\n";
	std::getline(std::cin, password);
	while (true)
	{
		std::cout << "Username: " << username << "\n";
		std::cout << "Password: " << password << "\n";
		std::cout << "Now choose a operating system to install" << "\n";
		std::cout << "Operating System Directory:" << "\n";
		std::cout << "----------------------------------------" << "\n";
		std::cout << "CapybaraSystemsOS - v0.2" << "\n";
		std::cout << "The standard operating system for CapyComputer, still in Alpha phase." << "\n";
		std::cout << "Now with a task app, a command terminal, and a RPG game!" << "\n";
		std::cout << "----------------------------------------" << "\n";
		std::cout << "Please choose a operating system:" << "\n";
		std::getline(std::cin, OS);
		if (OS == "CapybaraSystemsOS - v0.2")
		{
			std::cout << "Installing CapybaraSystemsOS - v0.2..." << "\n";
			for (int i = 0; i < 100; i++)
			{
				int waitTime = dist(gen);
				std::cout << "Installing... " << i << "%" << "\n";
				std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
			}
			std::cout << "Installation complete!" << "\n";
			CapybaraSystemsOS();
		}
		else
		{
			std::cout << "Invalid operating system selected." << "\n";
		}
	}
}

int main()
{
	//i had to manually do this because the capy command on Capyshell kept printing some ancient language.
	SetConsoleOutputCP(CP_UTF8);
	std::cout << "Hello and welcome to the CapyComputer Installation Client!" << "\n";
	std::cout << "This runs on Boost version " << BOOST_VERSION << " and also MVSC C++23 with Git for Windows installed." << "\n";
	std::cout << "Redirecting to the CapyComputer Installation Client..." << "\n";
	installCapyComputer();
	return 0;
}