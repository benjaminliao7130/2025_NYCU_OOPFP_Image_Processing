#include "gray_image.h"
#include "rgb_image.h"
#include "bit_field_filter.h"
#include "image_encryption.h"
#include "image_restore.h"
#include "puzzle_game.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string filename, msg, postfix;
    int type = -1, bitfield = 0;
    Image* img = nullptr;
    vector<string> operations;
    char op;
    bool skipSave = false;

    cout << "===== Image System =====" << endl;
    cout << "Select mode:\n1. Puzzle Game\n2. Image Processor\nChoice: ";
    int mode;
    cin >> mode;
    cin.ignore();

    if (mode == 1) {
        runPuzzleGame();
        return 0;
    }

    cout << "===== Image Processor =====" << endl;
    cout << "Enter image filename (in Image-Folder): ";
    getline(cin, filename);
    string path = "Image-Folder/" + filename;

    while (type != 1 && type != 2) {
        cout << "Select image type:\n1. Gray Image\n2. RGB Image\nChoice: ";
        cin >> type;

        if (filename.find("_enc") != string::npos && type == 1) {
            char confirm;
            cout << "This file seems to be encrypted. Gray Image cannot be decrypted.\n";
            cout << "Are you sure you want to choose Gray Image? (y/n): ";
            cin >> confirm;
            if (confirm == 'n' || confirm == 'N') {
                type = -1;
            }
        }
    }

    if (type == 1) {
        img = new GrayImage();
        operations.push_back("gray");
    } else {
        img = new RGBImage();
        operations.push_back("rgb");
    }

    if (!img->LoadImage(path)) {
        cerr << "Failed to load image." << endl;
        delete img;
        return 1;
    }

    cout << "Select filters to apply (bitfield, e.g., 3 = Flip + Mosaic):\n";
    cout << "0. Skip\n1. Flip\n2. Mosaic\n4. Gaussian\n8. Laplacian\n16. Restore\nEnter: ";
    cin >> bitfield;

    if (filename.find("_enc") != string::npos && bitfield > 0) {
        char confirm;
        cout << "This file seems to be encrypted. Applying filters may destroy the hidden message.\n";
        cout << "Are you sure you want to apply bitfield value " << bitfield << "? (y/n): ";
        cin >> confirm;
        if (confirm == 'n' || confirm == 'N') {
            bitfield = 0;
        } else {
            size_t pos = filename.find("_enc");
            if (pos != string::npos) filename.erase(pos, 4);
        }
    }

    ImageEncryption enc;
    bool encrypted = false;

    if (type == 2) {
        if (filename.find("_enc") != string::npos && bitfield == 0) {
            cout << "This file seems to be encrypted. Do you want to attempt decryption? (y/n): ";
            cin >> op;
            if (op == 'y' || op == 'Y') {
                try {
                    string result = enc.decrypt(dynamic_cast<RGBImage*>(img)->getData(), img->getWidth(), img->getHeight());
                    cout << "Recovered message: " << result << endl;
                    skipSave = true;
                } catch (const exception& e) {
                    cerr << "Decryption failed: " << e.what() << endl;
                }
            }
        } else if (bitfield == 0) {
            cout << "Encrypt a message? (y/n): ";
            cin >> op;
            if (op == 'y') {
                cin.ignore();
                while (true) {
                    cout << "Enter message (length < 100): ";
                    getline(cin, msg);
                    try {
                        enc.encrypt(dynamic_cast<RGBImage*>(img)->getData(), img->getWidth(), img->getHeight(), msg);
                        encrypted = true;
                        break;
                    } catch (const exception& e) {
                        cerr << "Encryption failed: " << e.what() << endl;
                        cout << "Try again? (y/n): ";
                        cin >> op;
                        cin.ignore();
                        if (op != 'y') break;
                    }
                }
            }
        }
    }

    ImageRestore restorer;
    if (bitfield & FILTER_RESTORE) {
        if (type == 1) {
            restorer.restoreGray(dynamic_cast<GrayImage*>(img)->getData(), img->getWidth(), img->getHeight());
        } else {
            restorer.restoreRGB(dynamic_cast<RGBImage*>(img)->getData(), img->getWidth(), img->getHeight());
        }
    }

    if (bitfield & FILTER_FLIP || bitfield & FILTER_MOSAIC || bitfield & FILTER_GAUSSIAN || bitfield & FILTER_LAPLACIAN || bitfield & FILTER_RESTORE) {
        if (type == 1) {
            auto gimg = dynamic_cast<GrayImage*>(img);
            if (gimg) gimg->applyFilters(bitfield);
        } else {
            auto rimg = dynamic_cast<RGBImage*>(img);
            if (rimg) rimg->applyFilters(bitfield);
        }
    }

    if (bitfield & FILTER_FLIP) operations.push_back("flip");
    if (bitfield & FILTER_MOSAIC) operations.push_back("mosaic");
    if (bitfield & FILTER_GAUSSIAN) operations.push_back("gaussian");
    if (bitfield & FILTER_LAPLACIAN) operations.push_back("laplacian");
    if (bitfield & FILTER_RESTORE) operations.push_back("restore");
    if (encrypted) operations.push_back("enc");

    for (const auto& op_str : operations) {
        postfix += "_" + op_str;
    }

    if (!skipSave) {
        int viewChoice = -1;
        while (viewChoice < 0 || viewChoice > 2) {
            cout << "View result before saving?\n";
            cout << "0. Skip\n1. Show by XServer\n2. Show by ASCII\nChoice: ";
            cin >> viewChoice;
        }

        if (viewChoice == 1) img->Display_X_Server();
        else if (viewChoice == 2) img->Display_ASCII();

        cout << "Save result? (y/n): ";
        cin >> op;
        if (op == 'y') {
            string outname;
            if (encrypted)
                outname = "Image-Folder/" + filename.substr(0, filename.find_last_of('.')) + postfix + ".bmp";
            else
                outname = "Image-Folder/" + filename.substr(0, filename.find_last_of('.')) + postfix + ".jpg";

            img->DumpImage(outname);
            cout << "Output saved as: " << outname << endl;
        } else {
            cout << "Image not saved." << endl;
        }
    }

    delete img;
    return 0;
}
