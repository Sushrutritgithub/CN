#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

void sayHello(int sock) {
    std::string msg = "Hello Server!";
    send(sock, msg.c_str(), msg.size(), 0);

    char buffer[1024] = {0};
    recv(sock, buffer, sizeof(buffer), 0);
    std::cout << "Server says: " << buffer << "\n";
}

void receiveFile(int sock) {
    std::ofstream outfile("received.txt", std::ios::binary);
    char buffer[1024];
    int bytesRead;

    while ((bytesRead = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        outfile.write(buffer, bytesRead);
        if (bytesRead < 1024) break; // end of file
    }

    std::cout << "File received as 'received.txt'\n";
    outfile.close();
}

void calculator(int sock) {
    std::string expr;
    std::cout << "Enter expression (e.g., 10 + 5): ";
    std::getline(std::cin, expr);
    send(sock, expr.c_str(), expr.size(), 0);

    char buffer[1024] = {0};
    recv(sock, buffer, sizeof(buffer), 0);
    std::cout << buffer << "\n";
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));

    std::cout << "\n========= TCP Socket Menu =========\n";
    std::cout << "1. Say Hello\n";
    std::cout << "2. File Transfer\n";
    std::cout << "3. Calculator\n";
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(); // clear newline
    send(sock, &choice, sizeof(choice), 0);

    switch (choice) {
        case 1: sayHello(sock); break;
        case 2: receiveFile(sock); break;
        case 3: calculator(sock); break;
        default: std::cout << "Invalid choice.\n"; break;
    }

    close(sock);
    return 0;
}
