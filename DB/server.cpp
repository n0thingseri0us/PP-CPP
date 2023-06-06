#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <bitset>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <netdb.h>
#include <unistd.h>
#include <cerrno>
#include <cctype>
#include <exception>
#include <unordered_map>

using namespace std;

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    istringstream iss(str);
    string token;

    while (getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// department -- group
unordered_map<string, int> groups = {
    {"208", 0}, {"209", 1}, {"210", 2}, {"211", 3},
    {"212", 4}, {"214", 5}, {"215", 6}, {"216", 7},
    {"217", 8}, {"218", 9}, {"219", 10}
};


vector<string> names = {
        "Ivanov",       "Smirnov",      "Kuznetsov",     "Popov",
    "Vasilev",      "Petrov",       "Sokolov",       "Mikhailov",
    "Novikov",      "Fedorov",      "Morozov",       "Volkov",
    "Alekseev",     "Lebedev",      "Semenov",       "Egorov",
    "Pavlov",       "Kozlov",       "Stepanov",      "Nikolaev",
    "Orlov",        "Andreev",      "Makarov",       "Nikitin",
    "Zakharov",     "Zaitsev",      "Solovev",       "Borisov",
    "IAkovlev",     "Grigorev",     "Romanov",       "Vorobev",
    "Sergeev",      "Kuzmin",       "Frolov",        "Aleksandrov",
    "Dmitriev",     "Korolev",      "Gusev",         "Kiselev",
    "Ilin",         "Maksimov",     "Poliakov",      "Sorokin",
    "Vinogradov",   "Kovalev",      "Belov",         "Medvedev",
    "Antonov",      "Tarasov",      "ZHukov",        "Baranov",
    "Filippov",     "Komarov",      "Davydov",       "Beliaev",
    "Gerasimov",    "Bogdanov",     "Osipov",        "Sidorov",
    "Matveev",      "Titov",        "Markov",        "Mironov",
    "Krylov",       "Kulikov",      "Karpov",        "Vlasov",
    "Melnikov",     "Denisov",      "Gavrilov",      "Tikhonov",
    "Kazakov",      "Afanasev",     "Danilov",       "Savelev",
    "Timofeev",     "Fomin",        "Chernov",       "Abramov",
    "Martynov",     "Efimov",       "Fedotov",       "Shcherbakov",
    "Nazarov",      "Kalinin",      "Isaev",         "Chernyshev",
    "Bykov",        "Maslov",       "Rodionov",      "Konovalov",
    "Lazarev",      "Voronin",      "Klimov",        "Filatov",
    "Ponomarev",    "Golubev",      "Kudriavtsev",   "Prokhorov",
    "Naumov",       "Potapov",      "ZHuravlev",     "Ovchinnikov",
    "Trofimov",     "Leonov",       "Sobolev",       "Ermakov",
    "Kolesnikov",   "Goncharov",    "Emelianov",     "Nikiforov",
    "Grachev",      "Kotov",        "Grishin",       "Efremov",
    "Arkhipov",     "Gromov",       "Kirillov",      "Malyshev",
    "Panov",        "Moiseev",      "Rumiantsev",    "Akimov",
    "Kondratev",    "Biriukov",     "Gorbunov",      "Anisimov",
    "Eremin",       "Tikhomirov",   "Galkin",        "Lukianov",
    "Mikheev",      "Skvortsov",    "Iudin",         "Belousov",
    "Nesterov",     "Simonov",      "Prokofev",      "KHaritonov",
    "Kniazev",      "TSvetkov",     "Levin",         "Mitrofanov",
    "Voronov",      "Aksenov",      "Sofronov",      "Maltsev",
    "Loginov",      "Gorshkov",     "Savin",         "Krasnov",
    "Maiorov",      "Demidov",      "Eliseev",       "Rybakov",
    "Safonov",      "Plotnikov",    "Demin",         "KHokhlov",
    "Fadeev",       "Molchanov",    "Ignatov",       "Litvinov",
    "Ershov",       "Ushakov",      "Dementev",      "Riabov",
    "Mukhin",       "Kalashnikov",  "Leontev",       "Lobanov",
    "Kuzin",        "Korneev",      "Evdokimov",     "Borodin",
    "Platonov",     "Nekrasov",     "Balashov",      "Bobrov",
    "ZHdanov",      "Blinov",       "Ignatev",       "Korotkov",
    "Muravev",      "Kriukov",      "Beliakov",      "Bogomolov",
    "Drozdov",      "Lavrov",       "Zuev",          "Petukhov",
    "Larin",        "Nikulin",      "Serov",         "Terentev",
    "Zotov",        "Ustinov",      "Fokin",         "Samoilov",
    "Konstantinov", "Sakharov",     "Shishkin",      "Samsonov",
    "Cherkasov",    "Chistiakov",   "Nosov",         "Spiridonov",
    "Karasev",      "Avdeev",       "Vorontsov",     "Zverev",
    "Vladimirov",   "Seleznev",     "Nechaev",       "Kudriashov",
    "Sedov",        "Firsov",       "Andrianov",     "Panin",
    "Golovin",      "Terekhov",     "Ulianov",       "Shestakov",
    "Ageev",        "Nikonov",      "Selivanov",     "Bazhenov",
    "Gordeev",      "Kozhevnikov",  "Pakhomov",      "Zimin",
    "Kostin",       "Shirokov",     "Filimonov",     "Larionov",
    "Ovsiannikov",  "Sazonov",      "Suvorov",       "Nefedov",
    "Kornilov",     "Liubimov",     "Lvov",          "Gorbachev",
    "Kopylov",      "Lukin",        "Tokarev",       "Kuleshov",
    "Shilov",       "Bolshakov",    "Pankratov",     "Rodin",
    "Shapovalov",   "Pokrovskii",   "Bocharov",      "Nikolskii",
    "Markin",       "Gorelov",      "Agafonov",      "Berezin",
    "Ermolaev",     "Zubkov",       "Kupriianov",    "Trifonov",
    "Maslennikov",  "Kruglov",      "Tretiakov",     "Kolosov",
    "Rozhkov",      "Artamonov",    "Shmelev",       "Laptev",
    "Lapshin",      "Fedoseev",     "Zinovev",       "Zorin",
    "Utkin",        "Stoliarov",    "Zubov",         "Tkachev",
    "Dorofeev",     "Antipov",      "Zavialov",      "Sviridov",
    "Zolotarev",    "Kulakov",      "Meshcheriakov", "Makeev",
    "Diakonov",     "Guliaev",      "Petrovskii",    "Bondarev",
    "Pozdniakov",   "Panfilov",     "Kochetkov",     "Sukhanov",
    "Ryzhov",       "Starostin",    "Kalmykov",      "Kolesov",
    "Zolotov",      "Kravtsov",     "Subbotin",      "Shubin",
    "Shchukin",     "Losev",        "Vinokurov",     "Lapin",
    "Parfenov",     "Isakov",       "Golovanov",     "Korovin",
    "Rozanov",      "Artemov",      "Kozyrev",       "Rusakov",
    "Aleshin",      "Kriuchkov",    "Bulgakov",      "Koshelev",
    "Sychev",       "Sinitsyn",     "Chernykh",      "Rogov",
    "Kononov",      "Lavrentev",    "Evseev",        "Pimenov",
    "Panteleev",    "Goriachev",    "Anikin",        "Lopatin",
    "Rudakov",      "Odintsov",     "Serebriakov",   "Pankov",
    "Degtiarev",    "Orekhov",      "TSarev",        "Shuvalov",
    "Kondrashov",   "Goriunov",     "Dubrovin",      "Golikov",
    "Kurochkin",    "Latyshev",     "Sevastianov",   "Vavilov",
    "Erofeev",      "Salnikov",     "Kliuev",        "Noskov",
    "Ozerov",       "Koltsov",      "Komissarov",    "Merkulov",
    "Kireev",       "KHomiakov",    "Bulatov",       "Ananev",
    "Burov",        "Shaposhnikov", "Druzhinin",     "Ostrovskii",
    "Shevelev",     "Dolgov",       "Suslov",        "Shevtsov",
    "Pastukhov",    "Rubtsov",      "Bychkov",       "Glebov",
    "Ilinskii",     "Uspenskii",    "Diakov",        "Kochetov",
    "Vishnevskii",  "Vysotskii",    "Glukhov",       "Dubov",
    "Bessonov",     "Sitnikov",     "Astafev",       "Meshkov",
    "Sharov",       "IAshin",       "Kozlovskii",    "Tumanov",
    "Basov",        "Korchagin",    "Boldyrev",      "Oleinikov",
    "Chumakov",     "Fomichev",     "Gubanov",       "Dubinin",
    "Shulgin",      "Kasatkin",     "Pirogov",       "Semin",
    "Troshin",      "Gorokhov",     "Starikov",      "Shcheglov",
    "Fetisov",      "Kolpakov",     "Chesnokov",     "Zykov",
    "Vereshchagin", "Minaev",       "Rudnev",        "Troitskii",
    "Okulov",       "Shiriaev",     "Malinin",       "Cherepanov",
    "Izmailov",     "Alekhin",      "Zelenin",       "Kasianov",
    "Pugachev",     "Pavlovskii",   "Chizhov",       "Kondratov",
    "Voronkov",     "Kapustin",     "Sotnikov",      "Demianov",
    "Kosarev",      "Belikov",      "Sukharev",      "Belkin",
    "Bespalov",     "Kulagin",      "Savitskii",     "ZHarov",
    "KHromov",      "Eremeev",      "Kartashov",     "Astakhov",
    "Rusanov",      "Sukhov",       "Veshniakov",    "Voloshin",
    "Kozin",        "KHudiakov",    "ZHilin",        "Malakhov",
    "Sizov",        "Ezhov",        "Tolkachev",     "Anokhin",
    "Vdovin",       "Babushkin",    "Usov",          "Lykov",
    "Gorlov",       "Korshunov",    "Markelov",      "Postnikov",
    "Chernyi",      "Dorokhov",     "Sveshnikov",    "Gushchin",
    "Kalugin",      "Blokhin",      "Surkov",        "Kochergin",
    "Grekov",       "Kazantsev",    "Shvetsov",      "Ermilov",
    "Paramonov",    "Agapov",       "Minin",         "Kornev",
    "Cherniaev",    "Gurov",        "Ermolov",       "Somov",
    "Dobrynin",     "Barsukov",     "Glushkov",      "Chebotarev",
    "Moskvin",      "Uvarov",       "Bezrukov",      "Muratov",
    "Rakov",        "Snegirev",     "Gladkov",       "Zlobin",
    "Morgunov",     "Polikarpov",   "Riabinin",      "Sudakov",
    "Kukushkin",    "Kalachev",     "Gribov",        "Elizarov"
};





// Закрывает сокет, при этом корректирует счётчик цикла проверки сокетов. 
void closeSocket(int &index);
void closeAllSockets();
int readStrFromClient(int fd,  string &str);

template<typename T>
int count_pos(vector<T> vec, T value)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == value)
        {
            return i;
            break;
        }
    }
}


ssize_t nwritten;
stringstream ss;

class Student {
public:
    string name;
    int group;
    double mid_score ;

    Student(const  string& name, int group, double mid_score)
        : name(name), group(group), mid_score(mid_score) {}
    Student(const string& info){ 
        vector<string> inf = split(info, '|');
        name = inf[0];
        group = stoi(inf[1]);
        mid_score = stod(inf[2]);
    }

    bool operator==(const Student& student) {
        return name == student.name &&
           group == student.group &&
           mid_score == student.mid_score;
    }
    friend ostream& operator<<(ostream& os, const Student& student) {
        os << setw(10) << student.name << setw(5) << student.group << setw(5) << student.mid_score << endl;
        return os;
    }
};

class Group {
public:
    int gId;
    vector<Student> students;

    Group(int id) : gId(id) { }

    void addStudent(const Student& st) {
        students.push_back(st);
    }

    void removeStudent(const Student& subject) {
        for (int i = 0; i < int(students.size()); i++) {
            if (students[i] == subject) {
                students.erase(students.begin() + i);
                return;
            }
        }
        throw invalid_argument("Subject not found for removal.");
    }

    int getStudentsCount() const {
        return students.size();
    }

    vector<Student> getStudents() const {
        return students;
    }

    vector<Student> Group_sel(int gr, vector<Student> students)
    {
        vector<Student> group_students;
        for (auto& student : students)
        {
            if (student.group == gr)
            {
                group_students.push_back(student);
            }
        }
        return group_students;
    }
};

// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================


#define eps 1e-6

typedef enum{ n, g, m }PARAM;

class Database {
private:
    vector<Group> selectedGroups;
    vector<Group> groups;
    vector<Student> students;
    vector<Student> selectedStudents;
    string filename;
    string output;

    Student parseStudentInfo(const string& StudentInfo) const {
        istringstream iss(StudentInfo);
        string token;
        string name;
        int group;
        double mid_score;
        if (!getline(iss, token, '|') || token.empty()) {
            throw invalid_argument("Invalid Student name.");
        }
        name = token;
        if (!getline(iss, token, '|')) {
            throw invalid_argument("Invalid group value.");
        }
        group = stoi(token);
        if (!getline(iss, token, '|')) {
            throw invalid_argument("Invalid mid_score value.");
        }
        mid_score = stod(token);
        Student st(name, group, mid_score);
        return st;
    }

public:
    Database(string name1, string name2): filename(name1), output(name2) {
        ifstream file(filename);
        string line;
        string str = "";
        while (getline(file, line)) {
            vector<string> q = split(line, '|');
            addStudentToGroup(line, stoi(q[1]));
            students.push_back(Student(line));
        }
    };

    void to_file() {
        ofstream file;
        file.open(output, ios::trunc);
        if (file.is_open()) { // открыт ли файл

            file << setw(10) << "Name" << setw(10) << "Group" << setw(10) << "Mid_score";
            file << endl << endl;
            for (auto& st : students)
            {
                file << setw(10) << st.name << setw(10) << st.group << setw(10) << st.mid_score << endl;
            }
            file.close(); // Закрытие файла
            cout << "File created and written successfully." << endl;
        } else {
            cout << "Unable to create/open the file." << endl;
        }
    }

    void addGroup(const Group& gr) {
        groups.push_back(gr);
    }

    void clear_selected_students()
    {
        selectedStudents.clear();
    }

    void select(const string& condition) {
        clear_selected_students();
        vector<string> q = split(condition, '=');

        for (const auto& student : students)
        {
            bool match = true;
            if (q[0] == "name")
            {
                if (student.name == q[1])
                {
                    selectedStudents.push_back(student);
                }
            }
            else if(q[0] == "group")
            {
                if (student.group == stoi(q[1]))
                {
                    selectedStudents.push_back(student);
                }
            }
            else if(q[0] == "mid_score")
            {
                if (abs(student.mid_score - stod(q[1])) < eps)
                {
                    selectedStudents.push_back(student);
                }
            }
        }
    }

    vector<Student> reselect(const string& condition) {
        vector<Student> selected_2;
        vector<string> q = split(condition, '=');

        for (const auto& student : selectedStudents)
        {
            bool match = true;
            if (q[0] == "name")
            {
                if (student.name == q[1])
                {
                    selected_2.push_back(student);
                }
            }
            else if(q[0] == "group")
            {
                if (student.group == stoi(q[1]))
                {
                    selected_2.push_back(student);
                }
            }
            else if(q[0] == "mid_score")
            {
                if (abs(student.mid_score - stod(q[1])) <= eps)
                {
                    selected_2.push_back(student);
                }
            }
        }

        return selected_2;
    }

    void addStudentToGroup(const string& studentInfo, const int& gId) {
        Student student = parseStudentInfo(studentInfo);
        int flag = 0;
        for (auto& group : groups) {
            if (group.gId == gId) {
                group.addStudent(student);
                flag++;
                return;
            }
        }
        if (flag == 0)
        {
            Group G(student.group);
            addGroup(G);
            addStudentToGroup(studentInfo, student.group);
        }
    }

    void removeStudentFromGroup(const string& studentInfo, const int& groupName) {
        Student st = parseStudentInfo(studentInfo);
        for (auto& group : groups) {
            if (group.gId == groupName) {
                group.removeStudent(st);
                return;
            }
        }
        for (int i = 0; i < selectedStudents.size(); i++)
        {
            if (selectedStudents[i] == st)
            {
                selectedStudents.erase(selectedStudents.begin() + i);
            }
        }
        throw invalid_argument("Teacher not found for subject removal.");
    }


    void print() const 
    {
        ss << setw(10) << "Name" << setw(10) << "Group" << setw(10) << "Mid_score";
        ss << endl << endl;
        for (auto& st : selectedStudents)
        {
            ss << st << endl;
        }
    }
    void print_all() const 
    {
        ss << setw(10) << "Name" << setw(10) << "Group" << setw(10) << "Mid_score";
        ss << endl << endl;
        for (auto& st : students)
        {
            ss << st << endl;
        }
    }
};



int countCharacter(const string& str, char character) {
    int count = 0;
    for (char c : str) {
        if (c == character) {
            count++;
        }
    }
    return count;
}

bool isCharacter(const string& str, char character) {
    return countCharacter(str, character) > 0;
}



// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================



struct Query {
    Database* database;
    Query(Database* db): database(db) {};
    void processQuery(const string& query) {
        istringstream iss(query);
        vector<string > command = split(query, ' ');

        if (command[0] == "print") {
            if (command.size() != 1) {
                throw invalid_argument("Invalid print command format.");
            }
            (*database).print();
        }
        else if (command[0] == "printall") {
            if (command.size() != 1) {
                throw invalid_argument("Invalid print command format.");
            }
            (*database).print_all();
        }
        else if (command[0] == "select") {
            if (command.size() != 2) {
                throw invalid_argument("Invalid select command format.");
            }
            (*database).select(command[1]);
        }
        // else if (command[0] == "update") {
        //     if (command.size() != 3) {
        //         throw invalid_argument("Invalid update command format.");
        //     }
        //     (*database).updateHierarchy(command[1], command[2]);
        // }
        else if (command[0] == "add") {
            if (command.size() != 3) {
                throw invalid_argument("Invalid add command format.");
            }
            (*database).addStudentToGroup(command[1], stoi(command[2]));
        }
        else if (command[0] == "remove") {
            if (command.size() != 3) {
                throw invalid_argument("Invalid remove command format.");
            }
            (*database).removeStudentFromGroup(command[1], stoi(command[2]));
        }
        else if (command[0] == "reselect") {
            if (command.size() != 2) {
                throw invalid_argument("Invalid reselect command format.");
            }
            vector<Student> vec = (*database).reselect(command[1]);
            for(auto &i : vec)
            {
                ss << i << endl;
            }
        }
        else {
            throw invalid_argument("Invalid command.");
        }
    }
};




// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================
// ========================================================================================================================




void send_int(int fd, int number)
{
    send(fd, &number, sizeof(number), MSG_WAITALL);
}


void send_str(int fd, const char *str)
{
    int len = strlen(str);
    send_int(fd, len);
    send(fd, str, len, MSG_WAITALL);
}

#define PORT 5555
#define QUEUE_SIZE 3		// размер очереди входящих запросов соединения
#define MAX_CONNECTIONS	101	// это число больше количества одновременных соединений

pollfd act_set[MAX_CONNECTIONS];
int num_set = 0;

// Закрывает сокет, при этом корректирует счётчик цикла проверки сокетов. 
void closeSocket(int &index);
void closeAllSockets();
int readStrFromClient(int fd, string &str);

int main(void)
{
    
    Database db("database.txt", "output.txt");
    Query q(&db);

	int err, opt = 1;
	int sock, new_sock;
	struct sockaddr_in server;
	struct sockaddr_in client;

	// Заполняем структуру адреса, на котором будет работать сервер. 
	server.sin_family = AF_INET; // IP
	server.sin_addr.s_addr = htonl(INADDR_ANY); // любой сетевой интерфейс
	server.sin_port = htons(PORT);	// избегаем проблем с порядком байт в записи числа

	// Создаём канал для сетевого обмена, задаём семейство протоколов и конкретный протокол обмена. 
	sock = socket(PF_INET, SOCK_STREAM, 0); // TCP сокет
	if (sock < 0) {
		perror("Server cannot create socket");
		exit(EXIT_FAILURE);
	}

	// Сокет будет использоваться без ожидания таймаута закрытия. 
	err = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *> (&opt), sizeof(opt));
	if (err < 0) {
		perror("Server cannot set socket options");
		if (close(sock) < 0)
			perror("Server cannot close socket");
		exit(EXIT_FAILURE);
	}

	// Привязываем локальный адрес server к сокету, т.е. присваиваем сокету имя 
	err = ::bind(sock, reinterpret_cast<sockaddr *> (&server), sizeof(server));
	if (err < 0) {
		perror("Server cannot bind socket");
		if (close(sock) < 0)
			perror("Server cannot close socket");
		exit(EXIT_FAILURE);
	}
	
	// Сокет sock используется для приёма соединений. Устанавливаем длину очереди. 
	err = listen(sock, QUEUE_SIZE);
	if (err < 0) {
		perror("Server listen failure");
		if (close(sock) < 0)
			perror("Server cannot close socket");
		exit(EXIT_FAILURE);
	}
	
	num_set = 1;				// изначально только слушающий сокет 
	act_set[0].fd = sock;
	act_set[0].events = POLLIN; // запрошенные события (INput - наличие данных для чтения)
	act_set[0].revents = 0;		// информация о произошедших событиях


	// Бесконечный цикл проверки состояния сокетов. 
	while (true)
	{
		int act_discr;	// количество описателей с обнаруженными событиями или ошибками
		cout << "Number of connections: " << num_set - 1 << endl;
		act_discr = poll(act_set, num_set, -1); // ждём появления данных в каком-либо сокете
		if (act_discr < 0) {
			perror("Server poll failure");
			closeAllSockets();
			exit(EXIT_FAILURE);
		}
		
		for (int i = 0; i < num_set; ++i)
		{
			if (act_set[i].revents ^ POLLIN)
				continue;
			
			act_set[i].revents &= ~POLLIN;
			if (i == 0)
			{
		
				socklen_t size = sizeof(client);
				new_sock = accept(act_set[i].fd, reinterpret_cast<sockaddr *> (&client), &size);
				if (sock < 0) {
					perror("Server accept failure");
					closeAllSockets();
					exit(EXIT_FAILURE);
				}
				if (num_set < MAX_CONNECTIONS) {
					act_set[num_set].fd = new_sock;
					act_set[num_set].events = POLLIN;
					act_set[num_set].revents = 0;
					++num_set;
				} else {
		
					cout << "Too many connections! The last client was not connected.\n";
					if (close(new_sock) < 0) {
						perror("Server cannot close socket");
						exit(EXIT_FAILURE);
					}
				}
			}
			else
			{
				string query;
				err = readStrFromClient(act_set[i].fd, query);
                
				if (err < 0) {
					cout << "Server cannot read string from client\n";
					closeSocket(i);
					continue;
				}                

				if (query == "exit") {
                    send_int(act_set[i].fd, 0);
					send_str(act_set[i].fd, "exit");
					closeSocket(i);
                    db.to_file();
				}

                else if (query == "shutdown") {
                    for (int j = 1; j <= num_set; j++) {
                        send_int(act_set[j].fd, 1);
                        send_str(act_set[j].fd, "shutdown");
                        closeSocket(j);
                    }
                    return 0;
                }

				else if (split(query, ' ')[0] == "print") {
                    send_int(act_set[i].fd, 2);
                    q.processQuery(query);
                    string output = ss.str();     
                    send_str(act_set[i].fd, output.c_str());
                    // Очистка потока вывода
                    ss.str("");
                }

                else {
                    send_int(act_set[i].fd, 3);
                    q.processQuery(query);
                    send_str(act_set[i].fd, "Request fulfilled");
                }
			}
		}
		cout << endl;
	}
}

void closeSocket(int &index)
{
	if (close(act_set[index].fd) < 0) {
		perror("Server cannot close socket");
		exit(EXIT_FAILURE);
	}
	if (index < num_set - 1) {
		act_set[index] = act_set[num_set - 1];
		--index;
	}
	--num_set;
}

void closeAllSockets()
{
	for (int i = 0; i < num_set; ++i)
		closeSocket(i);
}

int readStrFromClient(int fd, string &str)
{
	int len;
	int bytes_read;
	bytes_read = recv(fd, &len, sizeof(len), MSG_WAITALL); // считываем длину сообщения
	if (bytes_read != sizeof(len)) {
		return -1;
	}
	if(len < 0){
		return -1;
	}
	char *msg = new char[len];
	bytes_read = recv(fd, msg, len, MSG_WAITALL); // читаем сообщение целиком
	if (bytes_read != len) {
		delete[] msg;
		return -1;
	}
	str = string(msg, len);
	delete[] msg;
	return 0;
}
