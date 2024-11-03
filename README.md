<div align="center">
    <img src="https://github.com/ohalukkarakaya/cpp-network-programming-cli-chat-app/blob/e74725264f05cd6ef101d4fc5162f1656c02a92a/assets/chat_app_banner.jpg" alt="thumbnail" style="width: 100%; height: auto;"></img>

<h1>CLI Chat App</h1>
<p>Network Programming C++ CLI P2P Chat App</p>
</div>

## 🗺️ map 
- [<code>🛜 About Network Programming</code>](#-about-network-programming)
- [<code>🚀 About CLI Chat App</code>](#-about-cli-chat-app)
- [<code>🌐 Server-Side Overview</code>](#-server-side-overview)
- [<code>📝 Usage</code>](#-usage)
- [<code>🌟 Features</code>](#-features)
- [<code>🛠️ Installation</code>](#-installation)
- [<code>💻 Network Programming Code Implementations</code>](#-network-programming-code-implementations)
- [<code>👍 Conclusion</code>](#-conclusion)
- [<code>👉 References</code>](#-references)

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

## 🚀 About CLI Chat App
This **CLI Chat Application** is a simple yet powerful tool built in C++ for real-time communication over a network. It is designed for efficient message transmission using TCP protocol, ensuring a seamless experience for users in a command-line interface environment.

## 🌐 Server-Side Overview

The application includes a **server-side component** responsible for managing chat rooms and keeping track of user information. Specifically, the server:

- Maintains a list of active chat rooms.
- Stores the user IDs and user IP addresses of members in each room.

All other communication, including the actual messages and data transfer, occurs **directly between clients using TCP in a peer-to-peer (P2P) manner**. This design ensures a decentralized communication flow while still allowing room management and user tracking by the server.

## 📝 Usage

1. **Viewing Active Rooms**: Upon starting the application, users will see a list of active chat rooms.
2. **Joining or Creating a Room**:
   - The user will be prompted to enter the name of the room they wish to join.
   - If the entered room name does not exist, a new room will be created with that name.
   - If the entered room name exists, the user will join the existing room.
3. **Sending Messages**:
   - **Text Message**: Type `:m:` or `:message:` followed by the message you want to send. (e.g., `:m: Hello There!` for send `Hello There!` message).
   - **Audio Message**: Type `:a:` or `:audio:` and specify the number of seconds you wish to record (e.g., `:a: 5` for a 5-second recording). The recording will begin immediately, and once the specified duration is complete, the audio will be sent to other users in the room and played automatically on their devices.


