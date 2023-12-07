#include <iostream>
#include <string>
#include <array>
#include <iomanip>

using namespace std;

void getInformation();
void displayMainMenu();
void displayResHistory();
void displayAvailable();
void cancelReservation();

// memasukkan int 3 (lantai) dan 10 (kamar) ke variable const
const int numFloors = 3;
const int numRoomsPerFloor = 10;

// template untuk reservasi
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

    // setiap ordered() dipanggil, kamar menjadi tidak tersedia
    // akan digunakan setelah user memesan sebuah reservasi
    void ordered() {
        available = false;
    }
};

Reservation room[numFloors][numRoomsPerFloor]; // mendeklarasi array dua dimensi yang terdiri dari 3 baris (lantai) dan 10 kolom (kamar) 

Reservation reservation; // mendeklarasi nama struct, dengan menggunakan template Reservation

int main() {

    char mainMenuOption;
    char anotherReservation;

    while (true) {
        displayMainMenu();
        cout << "\nPilih opsi: ";
        cin >> mainMenuOption;

        if (mainMenuOption == '5') {
            break;
        }

        switch (mainMenuOption) {
            case '1':
                // loop akan terus berjalan sampai input user untuk anotherReservation tidak bernilai 'y'
                do {
                    system("cls");
                    getInformation();

                    // availableRoom akan digunakan sebagai nomor kamar yang tersedia
                    int availableRoom = -1;

                    // loop 10 kali untuk mengecek apakah ada kamar yang tersedia di lantai tertentu
                    // jika di lantai tersebut ada, maka masukkan no kamar yang tersedia ke variable availableRoom, lalu hentikan loop
                    for (int b = 0; b < numRoomsPerFloor; ++b) {
                        if (room[reservation.roomType - 1][b].available) {
                            availableRoom = b;
                            break;
                        }
                    }

                    // jika tidak ada kamar yang tersedia di lantai tertentu
                    if (availableRoom == -1) {
                        cout << "\n\nTidak tersedia kamar untuk tipe yang dipilih. Silakan pilih tipe kamar lain.\n";
                        system("pause");

                    } else {
                        reservation.ordered();

                        // memasukkan informasi reservasi ke nomor kamar yang tersedia melalui availableRoom dari loop tadi
                        room[reservation.roomType - 1][availableRoom] = reservation;

                        cout << "\nReservasi berhasil!\n\n";
                        cout << "Nomor referensi pemesanan Anda adalah: " << reservation.roomType << '0' << availableRoom + 1 << endl;

                        cout << "Apakah Anda ingin membuat reservasi lagi? (y/n): ";
                        cin >> anotherReservation;
                    }

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

            case '4':
                system("cls");
                cancelReservation();
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
    cout << "\n  4. Batalkan Reservasi\n";
    cout << "\n  5. Keluar\n";
}

void getInformation() {
    cout << "Enter your name:\n-> ";
    cin.ignore();
    getline(cin, reservation.name);

    cout << "\nEnter your contact information:\n-> ";
    getline(cin, reservation.contact);

    cout << "\nEnter duration of stay (in nights):\n-> ";
    cin >> reservation.duration;

    cout << "\nEnter the number of guests:\n-> ";
    cin >> reservation.numGuests;

    cout << "\nEnter room type: \n1. (Single), \n2. (Double), \n3. (Deluxe)\n-> ";
    cin >> reservation.roomType;

    switch (reservation.roomType) {
        case 1:
            reservation.totalPrice = 500000 * reservation.duration;
            break;
        case 2:
            reservation.totalPrice = 700000 * reservation.duration;
            break;
        case 3:
            reservation.totalPrice = 1000000 * reservation.duration;
            break;
    }

}

void displayResHistory() {

    int reservationCount = 0;

    cout << "\nRIWAYAT RESERVASI ANDA:\n\n";

    for (int a = 0; a < numFloors; ++a) {
        for (int b = 0; b < numRoomsPerFloor; ++b) {
            if (!room[a][b].available) {
                ++reservationCount;
                cout << "Reservation " << reservationCount << ":\n";
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

    if (reservationCount == 0) {
        cout << "  Belum ada riwayat reservasi.\n";
    }
}


void displayAvailable() {
    cout << "\nKAMAR YANG TERSEDIA (DITANDAI KOSONG):\n\n";

    for (int a = 0; a < numFloors; a++) {
        // Menampilkan nomor kamar untuk setiap lantai a
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

void cancelReservation() {
    int floor, roomNumber;

    cout << "Enter the floor number of the reservation to cancel: ";
    cin >> floor;

    cout << "Enter the room number of the reservation to cancel: ";
    cin >> roomNumber;

    // Validasi input
    if (floor < 1 || floor > numFloors || roomNumber < 1 || roomNumber > numRoomsPerFloor) {
        cout << "Invalid floor or room number. Please try again.\n";
        return;
    }

    // Validasi keberadaan reservasi
    if (room[floor - 1][roomNumber - 1].available) {
        cout << "No reservation found for the specified room. Please try again.\n";
        return;
    }

    // Tandai kamar yang di batalkan menjadi tersedia
    room[floor - 1][roomNumber - 1].available = true;

    cout << "Reservation canceled successfully for room " << floor << 0 << roomNumber << ".\n";
}


