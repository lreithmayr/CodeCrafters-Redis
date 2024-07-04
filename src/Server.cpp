#include "Server.h"

#define BUF_SIZE 256

void error(const char *msg) {
  perror(msg);
  exit(1);
}

void Server::init() {
  m_client_addr_len = sizeof(m_client_addr);
  m_server_addr.sin_family = AF_INET;
  m_server_addr.sin_addr.s_addr = INADDR_ANY;
  m_server_addr.sin_port = htons(6379);

  // Create socket
  m_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (m_sock_fd < 0) {
	error("Failed to create server socket\n");
  }

  int reuse = 1;
  if (setsockopt(m_sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
	error("setsockopt failed\n");
  }

  // Bind to socket adress
  if (bind(m_sock_fd, (struct sockaddr *)&m_server_addr, sizeof(m_server_addr)) < 0) {
	error("Failed to bind to port 6379\n");
  }
}

void Server::run() {
  // Listen for incoming connections
  int connection_backlog = 5;
  listen(m_sock_fd, connection_backlog);
  std::cout << "Waiting for a clients to connect..." << "\n";

  // Event loop processing incoming connections
  while (true) {
	// Clear the watched read FDs
	FD_ZERO(&m_readfds);
	// Add server to the watched FDs
	FD_SET(m_sock_fd, &m_readfds);

	// Re-initialize the active client FDs every time through the loop, since select() modifies readfds in-place
	if (!m_clients.empty()) {
	  for (size_t i = 0; i < m_clients.size(); ++i) {
		FD_SET(m_clients.at(i), &m_readfds);
	  }
	}

	// Check, if one of the watched FDs is ready to be read from. If so, FD_ISSET becomes true
	int onActivity = select(FD_SETSIZE, &m_readfds, NULL, NULL, NULL);
	if ((onActivity < 0) && (errno != EINTR)) {
	  error("Select error");
	}

	// If select() triggered on the server, there is an incoming new connection "new_client_socket". Add it to the list of clients
	if (FD_ISSET(m_sock_fd, &m_readfds)) {
	  int new_client_socket;
	  if ((new_client_socket = accept(m_sock_fd, (struct sockaddr *)&m_client_addr, (socklen_t *)&m_client_addr_len))
		< 0) {
		error("Accept error");
	  }
	  // Add it to the client list
	  m_clients.push_back(new_client_socket);
	}

	// Loop through the list of active connections to read the data
	for (size_t i = 0; i < m_clients.size(); ++i) {
	  int client_fd = m_clients.at(i);
	  // Only true if select() triggers on one of the clients on the watch list
	  if (FD_ISSET(client_fd, &m_readfds)) {
		process_command(client_fd, i);
	  }
	}
  }
}

void Server::process_command(const int &fd, const int i) {
  char rbuf[BUF_SIZE];
  int bytes_recvd = recv(fd, rbuf, sizeof(rbuf) - 1, 0);
  if (bytes_recvd < 0) {
	error("Receiving command");
  }
  if (bytes_recvd == 0) {
	// Client has closed connection
	close_connection(fd, i);
	return;
  }

  try {
	sz::string_view request(rbuf);
	sz::string parsed = Protocol::parse(request);
	int bytes_sent = 0;
	while (bytes_sent < parsed.length()) {
	  bytes_sent += send(fd, parsed.data(), parsed.length(), 0);
	  if (bytes_sent < 0) {
		error("Writing to socket");
	  }
	}
  } catch (const std::exception &e) {
	std::cout << e.what() << "\n";
  }

}

void Server::close_connection(const int &fd, const int i) {
  std::cout << "FD " << fd << "disconnected!" << "\n";
  close(fd);
  m_clients.erase(m_clients.begin() + i);
}
