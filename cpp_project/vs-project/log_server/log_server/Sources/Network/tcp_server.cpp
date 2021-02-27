#pragma  once
#include "error.h"
#include "logger.h"
#include "tcp_server.h"

#include <algorithm>

//!
//! ctor & dtor
//!

tcp_server::tcp_server(void)
	: m_io_service(get_default_io_service())
	, m_on_new_connection_callback(nullptr) {
	__MC_LOG(debug, "create tcp_server");
}

tcp_server::~tcp_server(void) {
	__MC_LOG(debug, "destroy tcp_server");
	stop();
}

//!
//! start & stop the tcp server
//!

void
tcp_server::start(const std::string& host, std::uint32_t port, const on_new_connection_callback_t& callback) {
	if (is_running()) { __MC_THROW(warn, "tcp_server is already running"); }

	m_socket.bind(host, port);
	m_socket.listen(__TACOPIE_CONNECTION_QUEUE_SIZE);

	m_io_service->track(m_socket);
	m_io_service->set_rd_callback(m_socket, std::bind(&tcp_server::on_read_available, this, std::placeholders::_1));
	m_on_new_connection_callback = callback;

	m_is_running = true;

	__MC_LOG(info, "tcp_server running");
}

void
tcp_server::stop(bool wait_for_removal, bool recursive_wait_for_removal) {
	if (!is_running()) { return; }

	m_is_running = false;

	m_io_service->untrack(m_socket);
	if (wait_for_removal) { m_io_service->wait_for_removal(m_socket); }
	m_socket.close();

	std::lock_guard<std::mutex> lock(m_clients_mtx);
	for (auto& client : m_clients) {
		client->disconnect(recursive_wait_for_removal && wait_for_removal);
	}
	m_clients.clear();

	__MC_LOG(info, "tcp_server stopped");
}

//!
//! io service read callback
//!

void
tcp_server::on_read_available(fd_t) {
	try {
		__MC_LOG(info, "tcp_server received new connection");

		auto client = std::make_shared<tcp_client>(m_socket.accept());

		if (!m_on_new_connection_callback || !m_on_new_connection_callback(client)) {
			__MC_LOG(info, "connection handling delegated to tcp_server");

			client->set_on_disconnection_handler(std::bind(&tcp_server::on_client_disconnected, this, client));
			m_clients.push_back(client);
		}
		else {
			__MC_LOG(info, "connection handled by tcp_server wrapper");
		}
	}
	catch (const mc_error&) {
		__MC_LOG(warn, "accept operation failure");
		stop();
	}
}

//!
//! client disconnected
//!

void
tcp_server::on_client_disconnected(const std::shared_ptr<tcp_client>& client) {
	//! If we are not running the server
	//! Then it means that this function is called by tcp_client::disconnect() at the destruction of all clients
	if (!is_running()) { return; }

	__MC_LOG(debug, "handle server's client disconnection");

	std::lock_guard<std::mutex> lock(m_clients_mtx);
	auto it = std::find(m_clients.begin(), m_clients.end(), client);

	if (it != m_clients.end()) { m_clients.erase(it); }
}

//!
//! returns whether the server is currently running or not
//!

bool
tcp_server::is_running(void) const {
	return m_is_running;
}

//!
//! get socket
//!

tcp_socket&
tcp_server::get_socket(void) {
	return m_socket;
}

const tcp_socket&
tcp_server::get_socket(void) const {
	return m_socket;
}

//!
//! get client sockets
//!

const std::list<std::shared_ptr<tcp_client>>&
tcp_server::get_clients(void) const {
	return m_clients;
}

//!
//! comparison operator
//!
bool
tcp_server::operator==(const tcp_server& rhs) const {
	return m_socket == rhs.m_socket;
}

bool
tcp_server::operator!=(const tcp_server& rhs) const {
	return !operator==(rhs);
}