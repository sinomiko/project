#include <atomic>
#include <cstdint>
#include <mutex>
#include <queue>
#include <string>
#include "Include/Network/io_service.h"
#include "Include/Network/tcp_socket.h"
#include "Include/Utils/typedefs.h"
class tcp_client {
public:
	//! ctor & dtor
	tcp_client(void);
	~tcp_client(void);
	//! custom ctor
	//! build socket from existing socket
	explicit tcp_client(tcp_socket&& socket);
	//! copy ctor & assignment operator
	tcp_client(const tcp_client&) = delete;
	tcp_client& operator=(const tcp_client&) = delete;
public:
	//! comparison operator
	bool operator==(const tcp_client& rhs) const;
	bool operator!=(const tcp_client& rhs) const;
public:
	//! get host & port information
	const std::string& get_host(void) const;
	std::uint32_t get_port(void) const;
public:
	//! start & stop the tcp client
	void connect(const std::string& addr, std::uint32_t port);
	void disconnect(bool wait_for_removal = false);
	//! returns whether the client is currently connected or not
	bool is_connected(void) const;
private:
	//! Call disconnection handler
	void call_disconnection_handler(void);
public:
	//! structure to store read requests result
	struct read_result {
		bool success;
		std::vector<char> buffer;
	};
	//! structure to store write requests result
	struct write_result {		bool success;
		std::size_t size;
	};
public:
	//! async read & write completion callbacks
	typedef std::function<void(read_result&)> async_read_callback_t;
	typedef std::function<void(write_result&)> async_write_callback_t;
public:
	//! structure to store read requests information
	struct read_request {
		std::size_t size;
		async_read_callback_t async_read_callback;
	};
	//! structure to store write requests information
	struct write_request {
		std::vector<char> buffer;
		async_write_callback_t async_write_callback;
	};
public:
	//! async read & write operations
	void async_read(const read_request& request);
	void async_write(const write_request& request);

public:
	//! socket getter
	tcp_socket& get_socket(void);
	const tcp_socket& get_socket(void) const;

public:
	//! disconnection handle
	typedef std::function<void()> disconnection_handler_t;
	//! set on disconnection handler
	void set_on_disconnection_handler(const disconnection_handler_t& disconnection_handler);
private:
	//! io service read callback
	void on_read_available(fd_t fd);
	//! io service write callback
	void on_write_available(fd_t fd);
private:
	//! process read & write operations when available
	async_read_callback_t process_read(read_result& result);
	async_write_callback_t process_write(write_result& result);
private:
	//! store io_service
	//! prevent deletion of io_service before the tcp_client itself
	std::shared_ptr<io_service> m_io_service;

	//! client socket
	tcp_socket m_socket;
	//! whether the client is currently connected or not
	std::atomic<bool> m_is_connected = ATOMIC_VAR_INIT(false);
	//! read & write requests
	std::queue<read_request> m_read_requests;
	std::queue<write_request> m_write_requests;
	//! thread safety
	std::mutex m_read_requests_mtx;
	std::mutex m_write_requests_mtx;
	//! disconnection handler
	disconnection_handler_t m_disconnection_handler;
};
