#include <iostream>
#include <iomanip>
#include <string.h>
#include <string>

using namespace std;

int pilihmenu, cari_nomor_kependudukan,index_search = 0, index_perbarui=0, cari_no_data_dihapus;
char menu_kembali = 'y' || 'Y';

struct kependudukan
{
    int nomor_kependudukan;
    char nama[30];
    char alamat[50];
    char jenis_kelamin;
};

void Sequiental_Search(){//search yang digunakan
    FILE *filedata;
    filedata = fopen("datakependudukan.dat", "rb");


    kependudukan data[100];
    int index = 0;

    while (fread(&data[index], sizeof(kependudukan), 1, filedata))
    {
        index++;
    }

    bool found;

    cout << "\n====== MENCARI DATA PENDUDUK ======\n" << endl;
    cout << "Masukkan nomer data penduduk yang ingin dicari : ";
    cin >> cari_nomor_kependudukan;
    found = false;
    int i = 0;
    while ((i < index) && (!found))
    {
        if (data[i].nomor_kependudukan == cari_nomor_kependudukan)
            found = true;
        else
            i = i + 1;
    }

    index_search = i;
    if (found)
    {
        cout<<"data ditemukan"<<endl;
        cout << left << setfill(' ') << setw(20) << "Nomer Penduduk " << ": "<<data[index_search].nomor_kependudukan<<endl;
        cout << left << setfill(' ') << setw(20) << "Nama " << ": "<<data[index_search].nama<<endl;
        cout << left << setfill(' ') << setw(20) << "Alamat " << ": "<<data[index_search].alamat<<endl;
        cout << left << setfill(' ') << setw(20) << "Jenis Kelamin " << ": "<<data[index_search].jenis_kelamin<<endl;
    
    }else
    {
        cout <<cari_nomor_kependudukan<< " tidak ada dalam file tersebut";
        return;
    }

    fclose(filedata);
}

void Bubble_Sort()//search bubble sorting
{
    FILE *filedata;
    filedata = fopen("datakependudukan.dat", "rb");

    kependudukan data[100];
    int index = 0;

    //untuk mencari jumlah index array
    while (fread(&data[index], sizeof(kependudukan), 1, filedata))
    {
        index++;
    }
    fclose(filedata);

    for (int i = 0; i < index - 1; ++i)
    {
        for (int j = 0; j < index - 1 - i; ++j)
        {
            if (data[j].nomor_kependudukan > data[j + 1].nomor_kependudukan)
            {
                swap(data[j], data[j + 1]);
            }
        }
    }

    filedata = fopen("datakependudukan.dat", "wb");
    for (int i = 0; i < index; ++i)
    {
        fwrite(&data[i], sizeof(kependudukan), 1, filedata);
    }
    fclose(filedata);
}

void Input_Data() //input data
{
    // temp sebagai vaiabel sementara untuk penginputan
    kependudukan temp;
    FILE *filedata;
    filedata = fopen("datakependudukan.dat", "ab");
    if (!filedata)
    {
        cout <<"File tidak ditemukan!\n"<< endl;
        return;
    }
    cout << "\n====== INPUT DATA ======\n" << endl;
    cout << left << setfill(' ') << setw(30) << "Masukkan Nomer Kependudukan " << ":";
    cin >> temp.nomor_kependudukan;
    cout << left << setfill(' ') << setw(30) << "Masukkan nama " << ":";
    cin >> temp.nama;
    cout << left << setfill(' ') << setw(30) << "Masukkan alamat " << ":";
    cin >> temp.alamat;
    cout << left << setfill(' ') << setw(30) << "Masukkan jenis kelamin " << ":";
    cin >> temp.jenis_kelamin;

    fwrite(&temp, sizeof(kependudukan), 1, filedata);
    fclose(filedata);

    cout << "Data kependudukan berhasil ditambahkan!" << endl;
}

void Output_Data()
{
    FILE *filedata;
    filedata = fopen("datakependudukan.dat", "rb");
    if (!filedata)
    {
        cout << "Tidak ada data!\n" << endl;
        return;
    }

    Bubble_Sort(); // Selalu urutkan data sebelum ditampilkan

    // temp sebagai vaiabel sementara untuk penginputan
    kependudukan temp;
    cout << "\n====== Daftar Data kependudukan ======\n"<<endl;
    cout << left <<setfill(' ') << setw(5) << "No." <<"|"
         <<setfill(' ') << setw(20) << "Nama" <<"|"<<setfill(' ')<< setw(30)
         <<setfill(' ') << "Alamat" <<"|"<< "Jenis Kelamin"<<"|"<< endl;
    while (fread(&temp, sizeof(kependudukan), 1, filedata))
    {
        cout << left <<setfill(' ')<<setw(5) << temp.nomor_kependudukan <<"|"
             <<setfill(' ')<< setw(20) << temp.nama <<"|"
             <<setfill(' ')<<setw(30) << temp.alamat <<"|"
             << setfill(' ')<<setw(13)<<temp.jenis_kelamin <<"|"<< endl;
    }
    fclose(filedata);
}

void Search_Data()
{
    FILE *filedata;
    filedata = fopen("datakependudukan.dat", "rb");
    if (!filedata)
    {
        cout << "Tidak ada data yang dapat dicari\n" << endl;
        return;
    }

    Sequiental_Search();
    fclose(filedata);
}

void Edit_Data()
{
    FILE *filedata;
    FILE *tempfile;

    filedata = fopen("datakependudukan.dat", "rb");
    tempfile = fopen("temp.dat", "wb");

    if (!filedata || !tempfile)
    {
        cout << "File tidak dapat dibuka!" << endl;
        return;
    }

    kependudukan temp;
    bool found = false;

    cout << "Masukkan nomor kependudukan yang alamatnya akan diperbarui: ";
    cin >> cari_nomor_kependudukan;

    while (fread(&temp, sizeof(kependudukan), 1, filedata))
    {
        if (temp.nomor_kependudukan == cari_nomor_kependudukan)
        {
            found = true;
            cout << "Data ditemukan" << endl;
            cout << left << setfill(' ') << setw(20) << "Nomer Penduduk " << ": " << temp.nomor_kependudukan << endl;
            cout << left << setfill(' ') << setw(20) << "Nama " << ": " << temp.nama << endl;
            cout << left << setfill(' ') << setw(20) << "Alamat " << ": " << temp.alamat << endl;
            cout << left << setfill(' ') << setw(20) << "Jenis Kelamin " << ": " << temp.jenis_kelamin << endl;

            cout << "Masukkan alamat baru: ";
            cin>>temp.alamat;
        }
        fwrite(&temp, sizeof(kependudukan), 1, tempfile);
    }
    if(found)
    {
        cout << "Alamat berhasil diperbarui!" << endl;
    }else{
        cout << "Data tidak ditemukan!" << endl;
    }

    fclose(filedata);
    fclose(tempfile);

    remove("datakependudukan.dat");
    rename("temp.dat", "datakependudukan.dat");
}

void Hapus_Data()
{    
    FILE *filedata;
    FILE *tempfile;

    filedata = fopen("datakependudukan.dat", "rb");
    tempfile = fopen("temp.dat", "wb");

    if (!filedata || !tempfile)
    {
        cout << "File tidak dapat dibuka!" << endl;
        return;
    }

    kependudukan temp;
    bool found = false;

    cout << "Masukkan nomor kependudukan yang datanya ingin dihapus: ";
    cin >> cari_no_data_dihapus;

    while (fread(&temp, sizeof(kependudukan), 1, filedata))
    {
        if (temp.nomor_kependudukan != cari_no_data_dihapus)
        {
            fwrite(&temp, sizeof(kependudukan), 1, tempfile);
        }else{
            found=true;
        }
    }
    if(found)
    {
        cout << "Data Berhasil dihapus!" << endl;
    }else{
        cout << "Data tidak ditemukan!" << endl;
    }
    fclose(filedata);
    fclose(tempfile);

    remove("datakependudukan.dat");
    rename("temp.dat", "datakependudukan.dat");
}

int main()
{
    do
    {
        cout << "\n";
        cout << "MENU PILIHAN :" << endl;
        cout << "1. Input" << endl;
        cout << "2. Output (data otomatis urut)" << endl;
        cout << "3. Search data" << endl;
        cout << "4. Edit Data" << endl;
        cout << "5. Hapus Data" << endl;
        cout << "6. Exit" << endl;
        cout << "memilih : ";
        cin >> pilihmenu;

        switch (pilihmenu)
        {
        case 1:
        {
            Input_Data();
            break;
        }

        case 2:
        {
            Output_Data();
            break;
        }

        case 3:
        {
            Search_Data();
            break;
        }

        case 4:
        {
            Edit_Data();
            break;
        }

        case 5:
        {
            Hapus_Data();
            break;
        }

        case 6:
        {
            cout << "Terima Kasih Telah Menggunakan Program Kami" << endl;
            exit(0);
            break;
        }
        }
        cout << "Kembali Ke menu ? (y/n) : ";
        cin >> menu_kembali;
    } while (menu_kembali == 'y' || menu_kembali == 'Y');
}
