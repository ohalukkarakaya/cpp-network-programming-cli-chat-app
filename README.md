<div align="center">
    <img src="https://github.com/ohalukkarakaya/cpp-network-programming-cli-chat-app/blob/e74725264f05cd6ef101d4fc5162f1656c02a92a/assets/chat_app_banner.jpg" alt="thumbnail" style="width: 100%; height: auto;"></img>

<h1>CLI Chat App</h1>
<p>Network Programming C++ CLI P2P Chat App</p>
</div>

## 🗺️ map 
- [<code>🛜 About Network Programming</code>](#-about-network-programming)
- [<code>💻 Network Programming Code Implementations</code>](#-network-programming-code-implementations)
- [<code>🚀 About CLI Chat App</code>](#-about-cli-chat-app)
- [<code>🌐 Server-Side Overview</code>](#-server-side-overview)
- [<code>📝 Usage</code>](#-usage)
- [<code>🌟 Features</code>](#-features)
- [<code>🛡️ Technologies Used</code>](#️-technologies-used)
- [<code>🛠️ Installation</code>](#️-installation)
- [<code>🤝 Contributing</code>](#-contributing)
- [<code>📜 License</code>](#-license)

<hr style="border: 0.1px solid #ccc;" />

## 🛜 About Network Programming
Network programming involves writing programs that enable communication between devices over a network. To understand how data is transmitted and managed across networks, we can break it down into several key concepts and protocols

* * *

### 📖 OSI Model Overview

The OSI (Open Systems Interconnection) Model is a conceptual framework used to understand and implement network communication in seven layers:

1. Physical Layer: Manages the physical transmission of raw data over a medium (e.g., cables, radio signals).
2. Data Link Layer: Handles data transfer between two directly connected nodes, providing error detection and correction (e.g., Ethernet).
3. Network Layer: Responsible for routing data packets between nodes across different networks (e.g., IP).
4. Transport Layer: Ensures reliable data transfer between systems, handling error recovery and flow control (e.g., TCP, UDP).
5. Session Layer: Manages sessions or connections between applications (e.g., RPC protocols).
6. Presentation Layer: Translates data formats for the application layer, handling encryption and compression.
7. Application Layer: Provides network services to end-user applications (e.g., HTTP, FTP, DNS).

* * *

### 📡 Key Protocols

1. TCP (Transmission Control Protocol)
   - Characteristics: Connection-oriented, reliable, ensures data is delivered in order and without errors.
   - Use Cases: Web browsing (HTTP/HTTPS), email (SMTP), file transfer (FTP).
   - How It Works: Establishes a connection (3-way handshake) before data transfer and manages error checking and retransmission.
2. UDP (User Datagram Protocol)
   - Characteristics: Connectionless, faster but less reliable, no error correction or ordering of packets.
   - Use Cases: Video streaming, online gaming, live audio transmission.
   - How It Works: Sends packets without establishing a connection, prioritizing speed over reliability.
3. FTP (File Transfer Protocol)
   - Purpose: Transfers files between a client and a server over a network.
   - Modes: Active and Passive modes for establishing connections.
   - Ports Used: Typically, port 21 for command control and a separate data channel for file transfer.
4. HTTP/HTTPS (Hypertext Transfer Protocol/Secure)
   - Purpose: Used for transferring web content.
   - HTTP: Insecure, data transmitted in plaintext.
   - HTTPS: Secure, uses SSL/TLS for encryption.
   - Ports Used: Port 80 for HTTP, Port 443 for HTTPS.
5. DNS (Domain Name System)
   - Purpose: Translates human-readable domain names (e.g., example.com) into IP addresses.
   - How It Works: Uses a hierarchy of DNS servers to resolve names efficiently.

* * *

### 🧵 TCP vs. UDP Comparison
| **Feature**            | **TCP**                          | **UDP**                      |
|------------------------|----------------------------------|-----------------------------|
| **Connection**         | Connection-oriented             | Connectionless              |
| **Reliability**        | Reliable, guarantees delivery   | Unreliable, no guarantees   |
| **Ordering**           | Maintains order of packets      | No order guarantee          |
| **Error Checking**     | Yes, includes error correction  | Basic error checking only   |
| **Speed**              | Slower due to overhead          | Faster, low latency         |
| **Use Cases**          | Web browsing, email, file transfer | Streaming, gaming, VoIP     |

* * *

### ⚙ Practical Applications
- TCP: Ensures data integrity and order, making it ideal for applications where reliability is critical.
- UDP: Suitable for real-time applications where speed is essential, even if some data packets are lost.
- FTP: Useful for managing file transfers in client-server setups.
- HTTP/HTTPS: Fundamental for web-based applications and secure data transmission.

* * *

## 💻 Network Programming Code Implementations

### 🤝 TCP Implementation in C++

To understand how TCP is implemented in this CLI Chat Application, let's break down the key components of the code.

#### 1. Setting Up the TCP Connection

The first step in building a TCP-based communication system is to establish a connection between the client and the server. This involves creating a socket, binding it to a specific port, and listening for incoming connections.

**Basic Steps for TCP Server Setup**:
1. **Create a Socket**: Use the `socket()` function to create a TCP socket.
2. **Bind the Socket**: Associate the socket with a port using the `bind()` function.
3. **Listen for Connections**: Call `listen()` to start listening for incoming connections.
4. **Accept Connections**: Use `accept()` to accept a client connection.

```cpp
// Example: TCP Server Setup
int server_socket = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in serverAddress;
server_address.sin_family = AF_INET;
server_address.sin_port = htons(8080); // Port number
server_address.sin_addr.s_addr = INADDR_ANY;

bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
listen(server_socket, 5);

int client_socket = accept(server_socket, nullptr, nullptr);
```

#### 2. Handling Data Transmission

Once the connection is established, you can send and receive data using `send()` and `recv()` functions.

**Sending and Receiving Data:**
- `send()`: Sends data from the server to the client.
- `recv()`: Receives data from the client to the server.

```cpp
// Sending a message to the client
std::string message = "Hello, Client!";
send(client_socket, message.c_str(), message.size(), 0);

// Receiving a message from the client
char buffer[1024] = {0};
recv(client_socket, buffer, sizeof(buffer), 0);
std::cout << "Client says: " << buffer << std::endl;
```

#### 3. TCP Client Setup

On the client side, a similar process is followed but with a connection to the server.

**Basic Steps for TCP Client Setup:**
- **Create a Socket:** Use the `socket()` function to create a TCP socket.
- **Connect to Server:** Use `connect()` to establish a connection to the server.

```cpp
// Example: TCP Client Setup
int client_socket = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in server_address;
server_address.sin_family = AF_INET;
server_address.sin_port = htons(8080); // Same port as the server
server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP

connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

// Sending and receiving data
send(client_socket, "Hello, Server!", 14, 0);
char buffer[1024] = {0};
recv(client_socket, buffer, sizeof(buffer), 0);
std::cout << "Server says: " << buffer << std::endl;
```

#### 4. Closing the Connection

When the communication is finished, make sure to close the sockets to release resources.

```cpp
// Closing the sockets
close(client_socket);
close(server_socket);
```

### 🤜 UDP Implementation in C++

Unlike TCP, UDP is a connectionless protocol that focuses on speed rather than reliability. It is ideal for scenarios where data needs to be sent quickly, even if some packets may be lost.

#### 1. Setting Up the UDP Connection

UDP communication involves creating a socket, binding it to a port, and then sending or receiving data without establishing a connection.

**Basic Steps for UDP Server Setup**:
1. **Create a Socket**: Use the `socket()` function to create a UDP socket.
2. **Bind the Socket**: Associate the socket with a port using the `bind()` function.

```cpp
// Example: UDP Server Setup
int server_socket = socket(AF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM for UDP
struct sockaddr_in server_address;
server_address.sin_family = AF_INET;
server_address.sin_port = htons(8080); // Port number
server_ddress.sin_addr.s_addr = INADDR_ANY;

bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
```
#### 2. Receiving and Sending Data

Since UDP is connectionless, data is sent and received using `sendto()` and `recvfrom()` functions, which specify the destination or source address.

**Receiving Data**:
```cpp
char buffer[1024] = {0};
struct sockaddr_in clientAddress;
socklen_t client_address_len = sizeof(clientAddress);

recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_address, &client_address_len);
std::cout << "Received: " << buffer << std::endl;
```

**Sending Data**:
```cpp
// Example: UDP Client Setup
int client_socket = socket(AF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM for UDP
struct sockaddr_in server_ddress;
server_address.sin_family = AF_INET;
server_address.sin_port = htons(8080); // Server port
server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP

// Sending data to the server
std::string message = "Hello, Server!";
sendto(client_socket, message.c_str(), message.size(), 0, (struct sockaddr*)&server_address, sizeof(server_address));

// Receiving data from the server
char buffer[1024] = {0};
struct sockaddr_in from_address;
socklen_t from_address_len = sizeof(from_address);

recvfrom(client_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&from_address, &from_address_len);
std::cout << "Server says: " << buffer << std::endl;
```

#### 4. Closing the Socket

Just like with TCP, you should close the socket when you're done with communication.

```cpp
// Closing the socket
close(client_socket);
close(server_socket);
```

### 📂 FTP Implementation in C++

The **File Transfer Protocol (FTP)** is a standard network protocol used to transfer files between a client and a server. It operates over TCP to ensure reliable data transmission and uses two separate channels: one for commands and another for data transfer.

#### 1. Understanding FTP Communication

FTP uses two connections:
- **Control Connection**: A TCP connection (usually on port 21) used for sending commands and receiving responses.
- **Data Connection**: A separate TCP connection used for transferring file data between the client and the server.

#### 2. Setting Up an FTP Client

To implement a basic FTP client in C++, you need to establish a control connection and send FTP commands following the protocol standards.

**Basic Steps for FTP Client Setup**:
1. **Create and Connect a TCP Socket**: Establish a control connection to the FTP server on port 21.
2. **Send Commands and Receive Responses**: Use the `send()` and `recv()` functions to communicate with the server.
3. **Manage Data Transfer**: Open a separate data connection for file transfers when needed.

#### 3. Establishing a Control Connection

```cpp
// Example: Establishing a Control Connection
int control_socket = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in server_address;
server_address.sin_family = AF_INET;
server_address.sin_port = htons(21); // FTP control port
server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // FTP server IP

connect(control_socket, (struct sockaddr*)&server_address, sizeof(server_address));

// Receiving the server's welcome message
char buffer[1024] = {0};
recv(control_socket, buffer, sizeof(buffer), 0);
std::cout << "Server: " << buffer << std::endl;
```
#### 4. Sending FTP Commands

FTP commands are sent as plain text strings. For example, to log in to the server, you use the `USER` and `PASS` commands.

```cpp
// Sending the USER command
std::string user_command = "USER yourUsername\r\n";
send(control_socket, user_command.c_str(), user_command.size(), 0);
recv(control_socket, buffer, sizeof(buffer), 0);
std::cout << "Server: " << buffer << std::endl;

// Sending the PASS command
std::string pass_command = "PASS your_password\r\n";
send(control_socket, pass_command.c_str(), pass_command.size(), 0);
recv(control_socket, buffer, sizeof(buffer), 0);
std::cout << "Server: " << buffer << std::endl;
```

#### 5. Setting Up a Data Connection

For file transfers, you need to switch to active or passive mode:

- **Active Mode:** The server connects back to the client for data transfer.
- **Passive Mode:** The client connects to a server-specified port for data transfer.

Example: Entering Passive Mode and Connecting to the Data Port:
```cpp
// Sending the PASV command to enter passive mode
std::string pasv_command = "PASV\r\n";
send(control_socket, pasv_command.c_str(), pasv_command.size(), 0);
recv(control_socket, buffer, sizeof(buffer), 0);
std::cout << "Server: " << buffer << std::endl;

// Parse the server response to get the data port
int p1, p2;
sscanf(buffer, "227 Entering Passive Mode (%*d,%*d,%*d,%*d,%d,%d).", &p1, &p2);
int data_port = p1 * 256 + p2;

// Create a new socket for the data connection
int data_socket = socket(AF_INET, SOCK_STREAM, 0);
server_address.sin_port = htons(data_port); // Use the parsed data port
connect(data_socket, (struct sockaddr*)&server_sddress, sizeof(server_address));
```

#### 6. Transferring Files

To download or upload files, use FTP commands like RETR (retrieve) and STOR (store).

Example: Downloading a File:
```cpp
// Sending the RETR command to download a file
std::string retr_command = "RETR example.txt\r\n";
send(control_socket, retr_command.c_str(), retr_command.size(), 0);
recv(control_socket, buffer, sizeof(buffer), 0);
std::cout << "Server: " << buffer << std::endl;

// Receiving the file data from the data connection
char file_buffer[1024] = {0};
recv(data_socket, file_buffer, sizeof(file_buffer), 0);
std::cout << "File Data: " << file_buffer << std::endl;

// Close the data connection
close(data_socket);
```

#### 7. Closing the Connection

Always close the control and data sockets after the communication is complete.

```cpp
// Sending the QUIT command to terminate the session
std::string quit_command = "QUIT\r\n";
send(control_socket, quit_command.c_str(), quit_command.size(), 0);
recv(control_socket, buffer, sizeof(buffer), 0);
std::cout << "Server: " << buffer << std::endl;

// Closing the control socket
close(control_socket);
```

* * *

## 🚀 About CLI Chat App
This **CLI Chat Application** is a simple yet powerful tool built in C++ for real-time communication over a network. It is designed for efficient message transmission using TCP protocol, ensuring a seamless experience for users in a command-line interface environment.

## 🌐 Server-Side Overview

The application includes a **server-side component** responsible for managing chat rooms and keeping track of user information. Specifically, the server:

- Maintains a list of active chat rooms.
- Stores the user IDs and user IP addresses of members in each room.

All other communication, including the actual messages and data transfer, occurs **directly between clients using TCP in a peer-to-peer (P2P) manner**. This design ensures a decentralized communication flow while still allowing room management and user tracking by the server.

<br>

> 📂 **Related Repository**: <br>
[cpp-network-programming-cli-chat-app-server-side](https://github.com/ohalukkarakaya/cpp-network-programming-cli-chat-app-server-side.git)

<br>

## 📝 Usage

<img src="https://github.com/ohalukkarakaya/cpp-network-programming-cli-chat-app/blob/32550585a8b2b17be8e0ef01107ecd97e652511c/assets/example_ss.png" alt="ss" style="width: 100%; height: auto;"></img>

1. **Viewing Active Rooms**: Upon starting the application, users will see a list of active chat rooms.
2. **Joining or Creating a Room**:
   - The user will be prompted to enter the name of the room they wish to join.
   - If the entered room name does not exist, a new room will be created with that name.
   - If the entered room name exists, the user will join the existing room.
3. **Sending Messages**:
   - **Text Message**: Type `:m:` or `:message:` followed by the message you want to send. (e.g., `:m: Hello There!` for send `Hello There!` message).
   - **Audio Message**: Type `:a:` or `:audio:` and specify the number of seconds you wish to record (e.g., `:a: 5` for a 5-second recording). The recording will begin immediately, and once the specified duration is complete, the audio will be sent to other users in the room and played automatically on their devices.

* * *

## 🌟 Features

- **Near-Time Messaging**: Supports sending and receiving messages instantly.
- **TCP Support**: Enables reliable communication with TCP.
- **Cross-Platform Compatibility**: Developed to work seamlessly on macOS, Linux, and Windows (However all tests made in Intel chip MacOS).
- **User-Friendly CLI Interface**: Easy-to-use text-based interface for chatting.

* * *

## 🛡️ Technologies Used

- **C++17**: Core programming language
- **CMake**: Build system for easy project setup and configuration

* * *

## 🛠️ Installation

> ⚠️ **Important**: Before proceeding, make sure that the server-side application is deployed and running. The chat application relies on the server for managing rooms and user information.

Follow these steps to set up and run the CLI Chat Application:

### 1. Clone the Repository

First, clone the repository to your local machine using the following command:

```bash
git clone https://github.com/ohalukkarakaya/cpp-network-programming-cli-chat-app.git
cd cpp-network-programming-cli-chat-app
```

### 2. Build the Project

Create a `build` directory, navigate into it, and use `cmake` and `make` to compile the project:

```bash
mkdir build
cd build
cmake ..
make
```

This will generate the executable file for the chat application.

### 3. Running the Application

Once the build is successful, you can run the program as follows:

```bash
./cli_chat_app
```

### 4. Deploying the Program

To deploy the program, you can move the compiled executable to a directory included in your system's PATH or create a shortcut to the executable for easy access:

<br>

> 📝 **Note:** <br> Ensure that the server's IP address and port are correctly configured in the application settings before running the chat app.

<br>

1. **Option 1:** Move to `/usr/local/bin` (Linux/macOS)
    ```bash
    sudo mv cli_chat_app /usr/local/bin
    ```
    
    Now, you can run the program from anywhere using `cli_chat_app`.

2. **Option 2:** Create a Shortcut (Windows)
    - Copy the executable file to a preferred location.
    - Add the location to your system's PATH environment variable to run it from the command line.
  
**You are now ready to use the CLI Chat Application to join or create rooms and start real-time communication!**

* * *

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the project.
2. Create your feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a pull request.

* * *

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
    
