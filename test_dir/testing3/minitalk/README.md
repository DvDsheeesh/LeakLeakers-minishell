*This project has been created as part of the 42 curriculum by melshata.*

## Description
**Minitalk** is a small infrastructure project designed to facilitate communication between two processes: a **Server** and a **Client**. 

The goal of this project is to send a string of characters from the client to the server using only **UNIX signals** (`SIGUSR1` and `SIGUSR2`). The server acknowledges every bit received, ensuring a synchronized and reliable data transfer. This project demonstrates a deep understanding of process IDs (PID), signal handling, and bitwise operations in C.

## Instructions

### Compilation
To compile the project, run the following command in your terminal:
	
**(in bash)**

		make

### Execution
1. Start the Server: First, launch the server to obtain its Process ID (PID).

		./server

	The server will display its PID (e.g., pid: 1234).

2. Run the Client: In a separate terminal, run the client by providing the server's PID and the message you wish to send.

		./client <PID> "Hello from the client!"

## Resources
1. Unix Signal Handling: Signal.h Documentation for understanding sigaction and kill.

2. Bitwise Operations: A refresher on how to shift and mask bits to convert characters into binary signals.

3. 42 school documentation: Internal notes on the siginfo_t structure.

### AI Usage
Concept Comprehension: AI was used to help in understanding new concepts, such as signal interruptions and bit manipulation, by providing several simple examples and use cases. This assisted in the design of the acknowledgment (ACK) loop between the client and server.