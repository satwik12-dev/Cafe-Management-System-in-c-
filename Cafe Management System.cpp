#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>

// User Class
class User {
private:
    std::string username;
    std::string password;
public:
    User(std::string uname, std::string pwd) : username(uname), password(pwd) {}
    std::string getUsername() { return username; }
    bool checkPassword(std::string pwd) { return password == pwd; }
};

// UserManager Class
class UserManager {
private:
    std::vector<User> users;
public:
    void addUser(std::string uname, std::string pwd) {
        users.push_back(User(uname, pwd));
    }
    bool authenticate(std::string uname, std::string pwd) {
        for (auto& user : users) {
            if (user.getUsername() == uname && user.checkPassword(pwd)) {
                return true;
            }
        }
        return false;
    }
};

// Session Class
class Session {
private:
    std::string username;
    std::time_t startTime;
    std::time_t endTime;
public:
    Session(std::string uname) : username(uname), startTime(std::time(nullptr)), endTime(0) {}
    void endSession() { endTime = std::time(nullptr); }
    double getSessionDuration() { 
        return std::difftime(endTime, startTime) / 60.0; // duration in minutes
    }
    std::string getUsername() { return username; }
};

// SessionManager Class
class SessionManager {
private:
    std::vector<Session> activeSessions;
public:
    void startSession(std::string uname) {
        activeSessions.push_back(Session(uname));
    }
    void endSession(std::string uname) {
        for (auto& session : activeSessions) {
            if (session.getUsername() == uname) {
                session.endSession();
                break;
            }
        }
    }
    double getSessionDuration(std::string uname) {
        for (auto& session : activeSessions) {
            if (session.getUsername() == uname) {
                return session.getSessionDuration();
            }
        }
        return 0;
    }
};

// Billing Class
class Billing {
private:
    double ratePerMinute;
public:
    Billing(double rate) : ratePerMinute(rate) {}
    double calculateBill(double duration) {
        return duration * ratePerMinute;
    }
};

// Main Function
int main() {
    UserManager userManager;
    SessionManager sessionManager;
    Billing billing(50); // 50 rupees per minute

    userManager.addUser("satwik", "123456");

    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (userManager.authenticate(username, password)) {
        std::cout << "Login successful!" << std::endl;
        sessionManager.startSession(username);

        // Simulate session
        std::this_thread::sleep_for(std::chrono::seconds(60)); // session for 2 minutes

        sessionManager.endSession(username);
        double duration = sessionManager.getSessionDuration(username);
        double bill = billing.calculateBill(duration);
        std::cout << "Session duration: " << duration << " minutes" << std::endl;
        std::cout << "Total bill: $" << bill << std::endl;
    } else {
        std::cout << "Invalid username or password!" << std::endl;
    }

    return 0;
}

