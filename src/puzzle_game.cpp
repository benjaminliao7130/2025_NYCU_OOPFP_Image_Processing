#include "gray_image.h"
#include "rgb_image.h"
#include "data_loader.h"
#include <bits/stdc++.h>

using namespace std;

bool isCorrectOrder(const vector<int>& inputOrder, const vector<int>& correctOrder) {
    return inputOrder == correctOrder;
}

string getFullPathFromUser(string& filename) {
    cout << "Enter image filename (in Image-Folder): ";
    cin >> ws;
    getline(cin, filename);
    filename.erase(0, filename.find_first_not_of(" \t\r\n"));
    filename.erase(filename.find_last_not_of(" \t\r\n") + 1);
    return "Image-Folder/" + filename;
}

int getUserN() {
    int N;
    do {
        cout << "Enter number N to split into N x N pieces (max 10): ";
        cin >> N;
        if (N > 10) cout << "N cannot be greater than 10. Please try again.\n";
    } while (N > 10);
    return N;
}

vector<int> getShuffledOrder(int N) {
    vector<int> order(N * N);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end(), default_random_engine(time(0)));
    return order;
}

map<int, pair<int, int>> getPiecePositions(int N) {
    map<int, pair<int, int>> positions;
    for (int i = 0; i < N * N; ++i)
        positions[i + 1] = {i / N, i % N};
    return positions;
}

void displayAnswer(const vector<int>& correctOrder, int N) {
    cout << "Answer:\n";
    for (int i = 0; i < (int)correctOrder.size(); ++i)
        cout << correctOrder[i] << ((i + 1) % N == 0 ? "\n" : " ");
}

bool getUserOrder(vector<int>& order, int N, const vector<int>& correctOrder) {
    order.clear();
    int val;
    for (int i = 0; i < N * N; ++i) {
        if (!(cin >> val)) break;
        if (val == N * N + 1) {
            displayAnswer(correctOrder, N);
            cin.clear();
            cin.ignore(10000, '\n');
            return false;
        }
        order.push_back(val);
    }
    return (int)order.size() == N * N;
}

void runPuzzleGame() {
    string filename;
    int N, type;

    string fullPath = getFullPathFromUser(filename);

    cout << "Select image type:\n1. Gray Image\n2. RGB Image\nChoice: ";
    cin >> type;

    N = getUserN();
    vector<int> correctOrder = getShuffledOrder(N);
    map<int, pair<int, int>> piecePosition = getPiecePositions(N);
    Data_Loader loader;

    if (type == 1) {
        int width, height;
        int** data = loader.Load_Gray(fullPath, &width, &height);
        int pieceW = width / N, pieceH = height / N;

        for (int i = 0; i < N * N; ++i) {
            int pieceNum = correctOrder[i];
            pair<int, int> pos = piecePosition[i + 1];

            GrayImage piece;
            piece.setSize(pieceW, pieceH);
            int** pdata = piece.getData();
            for (int y = 0; y < pieceH; ++y)
                for (int x = 0; x < pieceW; ++x)
                    pdata[y][x] = data[pos.first * pieceH + y][pos.second * pieceW + x];

            piece.DumpImage("puzzle/" + filename + "_" + to_string(pieceNum) + ".jpg");
        }

        while (true) {
            cout << "Enter " << N * N << " space-separated numbers (1~" << N * N << ") for the piece order (or " << N * N + 1 << " to reveal answer):\n";
            vector<int> order;
            if (!getUserOrder(order, N, correctOrder)) continue;

            GrayImage result;
            result.setSize(pieceW * N, pieceH * N);
            int** rdata = result.getData();

            for (int i = 0; i < N * N; ++i) {
                int row = i / N, col = i % N;
                GrayImage piece;
                piece.LoadImage("puzzle/" + filename + "_" + to_string(order[i]) + ".jpg");
                int** pdata = piece.getData();

                for (int y = 0; y < pieceH; ++y)
                    for (int x = 0; x < pieceW; ++x)
                        rdata[row * pieceH + y][col * pieceW + x] = pdata[y][x];
            }

            result.Display_X_Server();
            if (isCorrectOrder(order, correctOrder)) {
                cout << "Correct order!" << endl;
                break;
            } else {
                cout << "Incorrect order. Try again." << endl;
            }
        }

    } else if (type == 2) {
        int width, height;
        int*** data = loader.Load_RGB(fullPath, &width, &height);
        int pieceW = width / N, pieceH = height / N;

        for (int i = 0; i < N * N; ++i) {
            int pieceNum = correctOrder[i];
            pair<int, int> pos = piecePosition[i + 1];

            RGBImage piece;
            piece.setSize(pieceW, pieceH);
            int*** pdata = piece.getData();
            for (int y = 0; y < pieceH; ++y)
                for (int x = 0; x < pieceW; ++x)
                    for (int c = 0; c < 3; ++c)
                        pdata[y][x][c] = data[pos.first * pieceH + y][pos.second * pieceW + x][c];

            piece.DumpImage("puzzle/" + filename + "_" + to_string(pieceNum) + ".jpg");
        }

        while (true) {
            cout << "Enter " << N * N << " space-separated numbers (1~" << N * N << ") for the piece order (or " << N * N + 1 << " to reveal answer):\n";
            vector<int> order;
            if (!getUserOrder(order, N, correctOrder)) continue;

            RGBImage result;
            result.setSize(pieceW * N, pieceH * N);
            int*** rdata = result.getData();

            for (int i = 0; i < N * N; ++i) {
                int row = i / N, col = i % N;
                RGBImage piece;
                piece.LoadImage("puzzle/" + filename + "_" + to_string(order[i]) + ".jpg");
                int*** pdata = piece.getData();

                for (int y = 0; y < pieceH; ++y)
                    for (int x = 0; x < pieceW; ++x)
                        for (int c = 0; c < 3; ++c)
                            rdata[row * pieceH + y][col * pieceW + x][c] = pdata[y][x][c];
            }

            result.Display_X_Server();
            if (isCorrectOrder(order, correctOrder)) {
                cout << "Correct order!" << endl;
                break;
            } else {
                cout << "Incorrect order. Try again." << endl;
            }
        }
    }
}
