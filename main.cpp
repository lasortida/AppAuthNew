#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

string users[15][2];
string usersPhones[15];
string usersNames[15];
string usersSurnames[15];
string usersEmails[15];

void menu();  // ввод команд
void help(); // список команд
void registration(); // регистрация
int valid(); // проверка на свободное место в системе дла нового пользователя и вывод этого места
bool validLogin(string login); // проверка на совпадение логинов
void enterToMenu(); // выход в меню
void enterToAccount(string login); // выход в личный кабинет
void log(); // вход в аккаунт
int getId(string login); // получить ID пользователя по логину
bool validLogIn(string login, string password); // проверка на правильность введённых данных
void openPersonalAccount(string login); // вывод личного кабинета пользователя
void editAccountInformation(string login); // изменение информации о пользователе
bool validPhoneNumber(string phoneNumber); // проверить наличие уже существующего телефона
bool validEmail(string email); // проверить наличие уже существующего email
bool validVerification(string verification, int id);
void forgotPassword(string login);
void changePassword(int id);
void deleteAccount(int id);
bool validInformation(string login);

void run(string command) {
    if (command == "Help") {
        help();
    }

    if (command == "Registration") {
        registration();
    }

    if (command == "Log") {
        log();
    }

    if (command == "GoldenDog") {
        exit(0);
    }
    else {
        cout << "This command isn't available!";
        menu();
    }
} // обаботчик команд

bool validInformation(string login) {
    int id = getId(login);
    if (usersPhones[id] == "" || usersEmails[id] == "") {
        return false;
    }
    return true;
}

void deleteAccount(int id) {
    string key = users[id][0] + "/" + users[id][0];
    string repeatKey;
    cout << endl << endl << endl;
    cout << "   Delete Account" << endl;
    cout << "Enter this text - " << key << endl;
    cin >> repeatKey;
    while (repeatKey != key) {
        cout << "Please, check your text and try again: ";
        cin >> repeatKey;
    }
    users[id][0] = "";
    users[id][1] = "";
    usersPhones[id] = "";
    usersNames[id] = "";
    usersSurnames[id] = "";
    usersEmails[id] = "";
    cout << "Success! Your account have deleted! Press any button to back to menu...";
    enterToMenu();
}

bool validVerification(string verification, int id) {
    if (usersPhones[id] == verification || usersEmails[id] == verification) {
        return false;
    }
    else {
        return true;
    }
}

void changePassword(int id) {
    string password, repeatPassword;
    cout << endl << endl << endl;
    cout << "   Change Password" << endl;
    cout << "Enter new password: ";
    cin >> password;
    cout << "Enter your password again: ";
    cin >> repeatPassword;
    while (password != repeatPassword) {
        cout << "Error! Try again..." << endl;
        cout << "Create new password: ";
        cin >> password;
        cout << "Enter this password again: ";
        cin >> repeatPassword;
    }
    users[id][1] = password;
    cout << "Success! Press any button to back in account...";
    enterToAccount(users[id][0]);
}

void forgotPassword(string login) {
    int id = getId(login);
    string verification;
    cout << endl << endl << endl;
    cout << "Enter your phone number or e-mail: ";
    cin >> verification;
    while (validVerification(verification, id)) {
        cout << "Your data are incorrect! Try again" << endl;
        cout << "Enter your phone number or e-mail: ";
        cin >> verification;
    }
    changePassword(id);
}

void log() {
    string login;
    string password;
    cout << endl << endl << endl;
    cout << "   Log in" << endl;
    cout << "Enter your login: ";
    cin >> login;
    cout << "Enter your password (You can write - 'Forget'): ";
    cin >> password;
    while (validLogIn(login, password)) {
        if (password == "Forget") {
            while (! validLogin(login)) {
                cout << "Account with this login wasn't found!" << endl;
                cout << "Try again, enter your login or enter 'Exit': ";
                cin >> login;
                if (login == "Exit") {
                    menu();
                }
            }

        }
        cout << "Your data are incorrect! Please, repeat! " << endl;
        cout << "Enter login: ";
        cin >> login;
        cout << "Enter password: ";
        cin >> password;
    }
    openPersonalAccount(login);
}

int getId(string login) {
    for (int i = 0; i < 15; i++) {
        if (users[i][0] == login) {
            return i;
        }
    }
    return 228;
}

bool validPhoneNumber(string phoneNumber) {
    for (int i = 0; i < 15; i++) {
        if (usersPhones[i] == phoneNumber) {
            return true;
        }
    }
    return false;
}

bool validEmail(string email) {
    for (int i = 0; i < 15; i++) {
        if (usersEmails[i] == email) {
            return true;
        }
    }
    return false;
}

void editAccountInformation(string login) {
    int id = getId(login);
    usersNames[id] = "";
    usersSurnames[id] = "";
    usersPhones[id] = "";
    usersEmails[id] = "";
    string phoneNumber;
    string email;
    string name;
    string surname;
    cout << "   Edit" << endl;
    cout << "Enter your Name and Surname: ";
    cin >> name >> surname;
    cout << "Enter your Phone number: ";
    cin >> phoneNumber;
    while (validPhoneNumber(phoneNumber)) {
        cout << "Error, repeat your Phone number: ";
        cin >> phoneNumber;
    }
    cout << "Enter your E-mail: ";
    cin >> email;
    while (validEmail(email)) {
        cout << "Error, repeat your Email: ";
        cin >> email;
    }
    if (id != 228) {
        usersNames[id] = name;
        usersSurnames[id] = surname;
        usersPhones[id] = phoneNumber;
        usersEmails[id] = email;
        cout << "Your data are correct, press any button to save and back to account...";
        enterToAccount(login);
    }
    else {
        cout << "System crash!";
        exit(0);
    }
}

void openPersonalAccount(string login) {
    int id = getId(login);
    if (id != 228) {
        cout << endl << endl << endl;
        cout << "   Personal Account" << endl;
        cout << "Welcome to our system, " << login << endl;
        if (usersNames[id] == "") {
            cout << "Your account is blank!" << endl;
            cout << endl << "You can edit information. For it enter 'Edit' or enter 'Exit' to exit: ";
        }
        else {
            cout << "Your Name: " << usersNames[id] << endl;
            cout << "Your Surname: " << usersSurnames[id] << endl;
            cout << "Your Phone number: " << usersPhones[id] << endl;
            cout << "Your E-mail: " << usersEmails[id] << endl;
            cout << endl << "Enter command 'Exit' or 'Edit': ";
        }
        string command;
        cin >> command;
        if (command == "Exit") {
            menu();
        }
        if (command == "Edit") {
            editAccountInformation(login);
        }
        if (command == "Delete") {
            deleteAccount(id);
        }
        else {
            cout << "This command isn't available! You'll back to menu!";
            menu();
        }
    }
    else {
        cout << "System crash";
        exit(0);
    }
}

void enterToAccount(string login) {
    int ch = _getch();
    if (ch == 13) {
        openPersonalAccount(login);
    }
}

bool validLogIn(string login, string password) {
    for (int i = 0; i < 15; i++) {
        if (users[i][0] == login) {
            if (users[i][1] == password) {
                return false;
            }
        }
    }
    return true;
}

void help() {
    cout << endl << endl << endl;
    cout << "   Available commands" << endl;
    cout << "1) Help" << endl;
    cout << "2) Registration" << endl;
    cout << "3) Log" << endl;
    cout << "Press Enter to continue... ";
    enterToMenu();
}

void registration() {
    cout << endl << endl << endl;
    if (valid() != 666) {
        int id = valid();
        string login;
        string password;
        string repeatPassword;
        cout << "   Registration" << endl;
        cout << "Create your login: ";
        cin >> login;
        while (validLogin(login)) {
            cout << "Please, create new login!" << endl;
            cout << "Enter your new login: ";
            cin >> login;
        }
        cout << "Create your password: ";
        cin >> password;
        cout << "Repeat your password: ";
        cin >> repeatPassword;
        while (password != repeatPassword) {
            cout << "Error, Enter your password again!" << endl;
            cout << "Enter your first password: ";
            cin >> password;
            cout << "Enter your repeat password: ";
            cin >> repeatPassword;
        }
        cout << "Success! Now, you can Log in" << endl;
        users[id][0] = login;
        users[id][1] = password;
        cout << "Press Enter to continue...";
        enterToMenu();
    }
    else {
        cout << "Sorry, but our system is full! Attend us latter!" << endl;
        enterToMenu();
    }
}

void enterToMenu() {
    int ch = _getch();
    if (ch == 13) {
        menu();
    }
}

bool validLogin(string login) {
    for (int i = 0; i < 15; i++) {
        if (users[i][0] == login) {
            return true;
        }
    }
    return false;
}

int valid() {
    for (int i = 0; i < 15; i++) {
        if (users[i][0] == "") {
            return i;
        }
    }
    return 666;
}

void menu() {
    cout << endl << endl << endl;
    string command;
    cout << "   Main Menu" << endl;
    cout << "Please, enter valid command!" << endl << "You can enter 'Help'" << endl;
    cout << "Your command:  ";
    cin >> command;
    run(command);
}

int main() {
    menu();
    return 0;
}
