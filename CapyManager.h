#pragma once
//boost and openssl includes
#include <boost/version.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/json.hpp>
#include <openssl/ssl.h>
#include <openssl/evp.h>
//regular includes
#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <Windows.h>
#include <wincred.h>

namespace beast = boost::beast;   
namespace http = beast::http;     
namespace net = boost::asio;        
namespace ssl = net::ssl;
namespace json = boost::json;
using tcp = net::ip::tcp;

class InteractionSystem
{
public:
	struct HttpTarget
	{
		std::string host;
		std::vector<std::string> AvailableTargets;
	};
	void SetupConnectionWTools()
	{
		std::cout << "Welcome to CapyManager, an app used to communicate with the internet through api calls and stuff." << "\n";
		std::cout << "Disclaimer: Please don't use this for ACTUAL work like a job. As it might be insecure, and this is a more of a way learning how to make API calls." << "\n";
		std::cout << "This tool is still in development, so please be patient with it." << "\n";
		std::cout << "Here, you will be setting up availible connections for NetworkSystem to use." << "\n"; 
		//i would add saving here but im lazy, ill program it later.
		while (true)
		{
			HttpTarget connection;
			std::cout << "Enter host name (e.g. github.com) or 'exit' if you want to finish: " << "\n";
			std::getline(std::cin, connection.host);
			if (connection.host == "exit")
			{
				break;
			}
			else
			{
				std::cout << "Enter availible targets (e.g. /api/v1/users) for " << connection.host << " and leave empty to end: " << "\n";
				while (true)
				{
					std::string target;
					std::getline(std::cin, target);
					if (target.empty())
					{
						break;
					}
					connection.AvailableTargets.push_back(target);
				}
			}
			connections.insert(std::make_pair(connection.host, connection));
		}
	}
	std::pair<std::string, std::string> GetUserConnectionInput()
	{
		std::string host, target;
		std::cout << "Availible hosts: ";
		for (const auto& pair : connections)
		{
			std::cout << pair.first << "\n";
		}
		std::cout << "Enter host: ";
		std::getline(std::cin, host);
		if (connections.find(host) == connections.end())
		{
			std::cout << "Host not found. Please check your input." << "\n";
			return std::make_pair("", "");
		}
		std::cout << "Availible targets for " << host << ": ";
		for (const auto& available_target : connections.at(host).AvailableTargets)
		{
			std::cout << available_target << "\n";
		}
		std::cout << "Enter target for " << host << ": ";
		std::getline(std::cin, target);
		std::cout << "You have selected host: " << host << " and target: " << target << "\n";
		if (host.empty() || target.empty())
		{
			std::cout << "Host or target is empty. Please check your input." << "\n";
			return std::make_pair("", "");
		}
		else if (std::find(connections.at(host).AvailableTargets.begin(), connections.at(host).AvailableTargets.end(), target) == connections.at(host).AvailableTargets.end())
		{
			std::cout << "Target not found for the selected host. Please check your input." << "\n";
			return std::make_pair("", "");
		}
		return std::make_pair(host, target);
	}
	void DisplayConnections()
	{
		std::cout << "Availible connections:" << "\n";
		for (const auto& pair : connections)
		{
			std::cout << "Host: " << pair.first << "\n";
			std::cout << "Targets: " << "\n";
			for (const auto& target : pair.second.AvailableTargets)
			{
				std::cout << target << "\n";
			}
			std::cout << "\n";
		}
	}
private:
	//there could be a better way of storing this, but for now this is how we will do it.
	std::unordered_map<std::string, HttpTarget> connections;
};

class NetworkSystem
{
public:
	static void ConnectToTool(const std::pair<std::string, std::string>& connection)
	{
		if (connection == std::make_pair("", ""))
		{
			std::cout << "Invalid connection. Please check your input." << "\n";
			return;
		}
		try 
		{
			const std::string& host = connection.first;
			const std::string& target = connection.second;
			const std::string port = "443"; // Default HTTPS port
			net::io_context ioc;
			ssl::context ctx(ssl::context::tls_client);

			ctx.set_options(
				ssl::context::default_workarounds |
				ssl::context::no_sslv2 |
				ssl::context::single_dh_use);

			beast::error_code ec;
			ctx.set_default_verify_paths(ec);
			ctx.load_verify_file("cacert.pem", ec);
			if (ec)
			{
				std::cerr << "Warning: Could not load default verify paths: " << ec.message() << std::endl;
				return;
			}
			ctx.set_verify_mode(ssl::verify_peer);

			tcp::resolver resolver(ioc);
			ssl::stream<beast::tcp_stream> stream(ioc, ctx);
			//verify hostname
			stream.set_verify_callback(ssl::host_name_verification(host));

			if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str()))
			{
				beast::error_code ec{ static_cast<int>(::ERR_get_error()), net::error::get_ssl_category() };
				throw beast::system_error{ ec };
			}

			beast::flat_buffer buffer;
			http::response<http::string_body> res;
			auto endpoints = resolver.resolve(host, port);
			net::connect(stream.lowest_layer(), endpoints);

			stream.handshake(ssl::stream_base::client);

			http::request<http::string_body> req{ http::verb::get, target, 11 };
			req.set(http::field::host, host);
			req.set(http::field::user_agent, "CapyOS/0.2");
			req.set(http::field::accept, "application/json");
			http::write(stream, req);
			http::read(stream, buffer, res);
			std::cout << "Response: " << res << std::endl;
			json::value data = json::parse(res.body());

			beast::error_code close_ec;
			stream.shutdown(close_ec);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
		

	}
	static bool TestConnection()
	{
		try
		{
			//network variables
			const std::string host = "httpbin.org";
			const std::string port = "443";
			const std::string target = "/get";

			net::io_context ioc;
			ssl::context ctx(ssl::context::tls_client);

			//configure SSL context
			ctx.set_options(
				ssl::context::default_workarounds |
				ssl::context::no_sslv2 |
				ssl::context::single_dh_use);

			//load CA certificates - try multiple methods
			beast::error_code ec;
			ctx.set_default_verify_paths(ec);
			if (ec)
			{
				std::cerr << "Warning: Could not load default verify paths: " << ec.message() << std::endl;
			}

			//verification 
			ctx.load_verify_file("cacert.pem", ec);
			ctx.set_verify_mode(ssl::verify_peer);  

			tcp::resolver resolver(ioc);
			ssl::stream<beast::tcp_stream> stream(ioc, ctx);

			//set hostname verification
			if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str()))
			{
				beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
				throw beast::system_error{ec};
			}

			beast::flat_buffer buffer;
			http::response<http::string_body> res;
			//resolve and connect to the server
			auto endpoints = resolver.resolve(host, port);
			net::connect(stream.lowest_layer(), endpoints);

			//perform SSL handshake
			stream.handshake(ssl::stream_base::client);

			//request
			http::request<http::string_body> req{ http::verb::get, target, 11 };
			req.set(http::field::host, host);
			req.set(http::field::user_agent, "CapyOS/0.2");
			req.set(http::field::accept, "application/json");
			http::write(stream, req);
			http::read(stream, buffer, res);
			std::cout << "Response: " << res << std::endl;
			json::value data = json::parse(res.body());
			std::cout << "Network connection test successful!" << std::endl;

			//cleanup: shutdown the SSL connection gracefully
			beast::error_code close_ec;
			stream.shutdown(close_ec);

			return true;

		}
		catch (const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
			return false;
		}

	}
	static bool exitTerminal()
	{
		std::string userInput;
		std::cout << "Are you sure you want to exit the Network Terminal? (y/n): " << "\n";
		std::getline(std::cin, userInput);
		if (userInput == "y" || userInput == "Y")
		{
			std::cout << "Exiting Network Terminal..." << "\n";
			return true;
		}
		else if (userInput == "n" || userInput == "N")
		{
			std::cout << "Continuing in Network Terminal..." << "\n";
			return false;
		}
		else
		{
			std::cout << "Invalid input. Please enter 'y' or 'n'." << "\n";
			return exitTerminal(); // Recursively ask again
		}
	}

private:
};
//now this is complex hold on
class AuthorizationSystem 
{
public:
	enum class AuthType
	{
		None,
		Basic,
		Bearer,
		ApiKey,
		OAuth2,
		Cookie,
		Digest,
		HMAC,
		MutualTLS
	};
	bool TestCredential()
	{
		CREDENTIALW credential = {};
		credential.Persist = CRED_PERSIST_LOCAL_MACHINE; //tells us "keep on computer"
		credential.Type = CRED_TYPE_GENERIC;
		wchar_t targetName[] = L"CapyOS/CapyManager/CredTest";
		credential.TargetName = targetName;
		//avoiding the "i change this now good luck" reinterpret cast
		std::vector<BYTE> testSecret = { 'l', 'o', 'l' };
		credential.CredentialBlob = testSecret.data();
		credential.CredentialBlobSize = static_cast<DWORD>(testSecret.size());
		//doing this because im TESTING it
		credential.UserName = nullptr;
		bool storeSuccess = CredWriteW(&credential, 0);
		if (storeSuccess)
		{
			std::cout << "Credential Write Test: Success" << "\n";
		}
		else
		{
			std::cout << "Credential Write Test: Failure" << "\n";
			std::cout << "Caused by: " << GetLastError() << "\n";
			return false;
		}
		PCREDENTIAL readCred = nullptr;
		bool ReadSuccess = CredReadW(targetName, CRED_TYPE_GENERIC, 0, &readCred);
		if (ReadSuccess && (std::equal(testSecret.begin(), testSecret.end(), readCred->CredentialBlob) && readCred->CredentialBlobSize == static_cast<DWORD>(testSecret.size())))
		{
			std::cout << readCred->CredentialBlob << "\n";
			std::cout << readCred->CredentialBlobSize << "\n";
			std::cout << "Credential Read Test: Success";
		}
		else
		{
			std::cout << "Credential Read Test: Failure" << "\n";
			return false;
		}
		CredFree(readCred);
		return true;
	}
};