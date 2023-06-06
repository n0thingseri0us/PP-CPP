#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <ctime>
#include <cstring>

using namespace std;

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
vector<string> groups = {"207", "208", "209", "210", "211", "212", "214", "215", "216", "217", "218", "219"}; 


double generate_mid_score()
{
    double r = floor(100.0*(3.0 + 2.0*(rand() / (RAND_MAX + 1.)))) / 100.0;
    return r;
}

std::string generateString(int k, int r) {

    std::string name = names[k];
    int f = r % 4;
    std::string group = groups[f];
    std::string hierarchy(42, '0');
    double mid_score = generate_mid_score();
    hierarchy[f] = '1';
    std::string str = name + "|";
    //str += hierarchy;
    //str += "#";
    str += group;
    str += "|"  + to_string(mid_score) + ",";
    //str += '!';
    return str;
}

int main() {
    std::vector<std::string> strings;
    strings.reserve(500);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < 500; i++) {
        int randomNumber = dist(gen);
        std::string str = generateString(i, randomNumber);
        strings.push_back(str);
    }

    std::ofstream outputFile("database.txt");
    if (outputFile.is_open()) {
        for (const auto& str : strings) {
            outputFile << str << std::endl;
        }
        outputFile.close();
        std::cout << "Written 'database.txt'\n" << std::endl;
    } else {
        std::cerr << "File 'database.txt' did not open\n" << std::endl;
    }

    return 0;
}
