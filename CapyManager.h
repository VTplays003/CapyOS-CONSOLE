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

namespace beast = boost::beast;   
namespace http = beast::http;     
namespace net = boost::asio;        
namespace ssl = net::ssl;
namespace json = boost::json;
using tcp = net::ip::tcp;

class InteractionSystem
{

};

class NetworkSystem
{
public:
	bool TestConnection()
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

private:
};