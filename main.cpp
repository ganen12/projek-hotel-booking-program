#include <iostream>
#include <string>
#include <array>
#include <iomanip>

using namespace std;

void getInformation();
void displayMainMenu();
void displayResHistory();
void displayAvailable();

const int numFloors = 3;
const int numRoomsPerFloor = 10;
int reservationCounter = 1;

struct Reservation {
    string name;
    string contact;
    string checkInDate;
    string checkOutDate;
    int duration = 0;
    int numGuests = 0;
    int roomType = 0;
    int totalPrice = 0;
    bool available = true;

    void ordered() {
        available = false;
    }
};

Reservation room[numFloors][numRoomsPerFloor]; // membuat 3 baris (lantai) dan 10 kolom (kamar) array 

Reservation reservation;

int main() {

    char mainMenuOption;
    char anotherReservation;
    int i[numFloors] = { 0 };

    while (true) {
        displayMainMenu();
        cout << "\nPilih opsi: ";
        cin >> mainMenuOption;

        if (mainMenuOption == '4') {
            break;
        }

        switch (mainMenuOption) {
        case '1':
            do {
                system("cls");
                getInformation();

                reservation.ordered();

                room[reservation.roomType - 1][i[reservation.roomType - 1]] = reservation;

                i[reservation.roomType - 1]++;

                cout << "Reservation successful!\n\n";
                cout << "Your booking reference number is: " << reservation.roomType << '0' << i[reservation.roomType - 1] << endl;

                cout << "Do you want to make another reservation? (y/n): ";
                cin >> anotherReservation;

            } while (anotherReservation == 'y' || anotherReservation == 'Y');

            system("cls");
            displayResHistory();
            system("pause");

            break;
        case '2':

            system("cls");
            displayResHistory();
            cout << "\nPencet keyboard untuk kembali ke main menu. \n";
            system("pause");

            break;

        case '3':
            system("cls");
            displayAvailable();

            cout << "\nPencet keyboard untuk kembali ke main menu. \n\n";
            system("pause");


            break;
        default:
            system("cls");
            cout << "Pilih opsi yang tersedia..\n";
            system("pause");

            break;
        }

    }

    return 0;
}

void displayMainMenu() {
    system("cls");
    cout << "Selamat Datang di Hotel Amikom\n";
    cout << "\n  1. Pesan kamar\n";
    cout << "\n  2. Lihat Riwayat Pesanan Kamar\n";
    cout << "\n  3. Lihat Kamar yang Tersedia\n";
    cout << "\n  4. Keluar\n";
}

void getInformation() {
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, reservation.name);

    cout << "Enter your contact information: ";
    getline(cin, reservation.contact);

    cout << "Enter duration of stay (in nights): ";
    cin >> reservation.duration;

    cout << "Enter the number of guests: ";
    cin >> reservation.numGuests;

    cout << "Enter room type: \n1. (Single), \n2. (Double), \n3. (Deluxe): ";
    cin >> reservation.roomType;

    switch (reservation.roomType) {
    case 1:
        reservation.totalPrice = 500000 * reservation.numGuests * reservation.duration;
        break;
    case 2:
        reservation.totalPrice = 700000 * reservation.numGuests * reservation.duration;
        break;
    case 3:
        reservation.totalPrice = 1000000 * reservation.numGuests * reservation.duration;
        break;
    }

}


void displayResHistory() {
    cout << "\nRiwayat Reservasi Anda:\n\n";

    for (int a = 0; a < numFloors; ++a) {
        for (int b = 0; b < numRoomsPerFloor; ++b) {
            if (!room[a][b].available) {
                cout << "Reservation " << reservationCounter++ << ":\n";
                cout << "  +----------------------------------------------------+\n";
                cout << "  |      NAMA       :   " << setw(30) << left << room[a][b].name << " |\n";
                cout << "  |      KONTAK     :   " << setw(30) << left << room[a][b].contact << " |\n";
                cout << "  |      JML TAMU   :   " << setw(30) << left << room[a][b].numGuests << " |\n";
                cout << "  |      TIPE KAMAR :   " << setw(30) << left << room[a][b].roomType << " |\n";
                cout << "  |      NO KAMAR   :   " << a + 1 << 0 << b + 1 << "                            |\n";
                cout << "  |      TOTAL      :   Rp " << setw(27) << room[a][b].totalPrice << " |\n";
                cout << "  +----------------------------------------------------+\n";
                cout << "  |      CHECK-IN   :   " << setw(30) << left << room[a][b].checkInDate << " |\n";
                cout << "  |      CHECK-OUT  :   " << setw(30) << left << room[a][b].checkOutDate << " |\n";
                cout << "  +----------------------------------------------------+\n\n";
            }
        }
    }
}


void displayAvailable() {
    cout << "\n\nKamar yang tersedia (ditandai kosong):\n\n";

    for (int a = 0; a < numFloors; a++) {
        // Menampilkan nomor kamar untuk setiap lantai
        cout << " L" << a + 1;
        for (int b = 1; b <= numRoomsPerFloor; b++) {
            cout << "        " << b;
        }
        cout << endl;

        // Menampilkan ketersediaan untuk setiap kamar di lantai a
        cout << setw(9);
        for (int b = 0; b < numRoomsPerFloor; b++) {
            if (room[a][b].available) {
                cout << "    " << "[   ]";
            }
            else {
                cout << "    " << "[ X ]";
            }
        }

        cout << "\n\n";
    }
}


