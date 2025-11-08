#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

void sayHello(int clientSocket) {
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Client says: " << buffer << "\n";
    std::string reply = "Hello Client!";
    send(clientSocket, reply.c_str(), reply.size(), 0);
}

void sendFile(int clientSocket) {
    std::ifstream file("sample.txt", std::ios::binary);
    if (!file.is_open()) {
        std::string msg = "Error: sample.txt not found.";
        send(clientSocket, msg.c_str(), msg.size(), 0);
        return;
    }

    char buffer[1024];
    while (file.read(buffer, sizeof(buffer)) || file.gcount()) {
        send(clientSocket, buffer, file.gcount(), 0);
    }
    std::cout << "File sent successfully.\n";
    file.close();
}

void calculator(int clientSocket) {
    char buffer[1024];
    recv(clientSocket, buffer, sizeof(buffer), 0);
    double a, b;
    char op;
    std::stringstream ss(buffer);
    ss >> a >> op >> b;

    double result = 0;
    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = (b != 0) ? a / b : 0; break;
        default: result = 0;
    }

    std::string res = "Result: " + std::to_string(result);
    send(clientSocket, res.c_str(), res.size(), 0);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr{}, clientAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    std::cout << "Server is running on port 8080...\n";

    socklen_t clientSize = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
    std::cout << "Client connected!\n";

    int choice;
    recv(clientSocket, &choice, sizeof(choice), 0);

    switch (choice) {
        case 1: sayHello(clientSocket); break;
        case 2: sendFile(clientSocket); break;
        case 3: calculator(clientSocket); break;
        default: std::cout << "Invalid choice.\n"; break;
    }

    close(clientSocket);
    close(serverSocket);
    return 0;
}
