#include "funcs/file.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Not enough arguments. Please try again!";
        return 1;
    }

    const string algorithms[12] = {"selection-sort", "insertion-sort", "shell-sort", "bubble-sort", "heap-sort", "merge-sort", "quick-sort", "radix-sort", "counting-sort", "binary-insertion-sort", "shaker-sort", "flash-sort"};
    const string orders[4] = {"Randomize", "Nearly Sorted", "Sorted", "Reversed"};
    string mode = argv[1];
    if (mode == "-a") {
        cout << "ALGORITHM MODE" << endl;
        string algorithm = argv[2];
        bool isValid = false;
        for (int i = 0; i < 12; i++) if (algorithm == algorithms[i]) isValid = true;
        if (!isValid) {
            cout << "Invalid algorithm. Please check README.txt" << endl;
            return 1;
        } 
        int* a;
        long long comparisons;
        bool measureTime = false, measureComp = false;

        if (isdigit(argv[3][0])) {
            int size = stoi(string(argv[3]));
            if (size < 0 || size > 1000000) {
                cout << "Invalid input size, please pick a size ranging from 1 to 1000000" << endl;
                return 1;
            }
            a = new int[size];
            if (argc > 4 && argc <= 5) {
                string param = argv[4];
                measureTime = (param == "-time" || param == "-both");
                measureComp = (param == "-comp" || param == "-both");

                cout << "Input size: " << size << endl;
                cout << endl;
                for (int i = 0; i < 4; i++) {
                    cout << "Input order: " << orders[i] << endl;
                    cout << "--------------------------------" << endl;
                    GenerateData(a, size, i);
                    ofstream fi("input_" + to_string(i + 1) + ".txt");
                    if (!fi.is_open()) {
                        cout << "Failed to write input!";
                        return 1;
                    }
                    fi << size << endl;
                    for (int i = 0; i < size; i++) fi << a[i] << " "; 
                    fi.close();
                    RunAlgorithm(algorithm, a, size, measureTime, measureComp);
                    cout << endl;
                }
            }
            else if (argc > 5) {
                ofstream fi("input.txt");
                if (!fi.is_open()) {
                    cout << "Unable to write file";
                    return 1;
                }
                fi << size << endl;

                string order = argv[4];
                if (order == "-rand") {
                    GenerateData(a, size, 0);
                    order = orders[0];
                    for (int i = 0; i < size; i++) fi << a[i] << " ";
                }
                else if (order == "-nsorted") {
                    GenerateData(a, size, 1);
                    order = orders[1];
                    for (int i = 0; i < size; i++) fi << a[i] << " ";
                }
                else if (order == "-sorted") {
                    GenerateData(a, size, 2);
                    order = orders[2];
                    for (int i = 0; i < size; i++) fi << a[i] << " ";
                }
                else if (order == "-rev") {
                    GenerateData(a, size, 3);
                    order = orders[3];
                    for (int i = 0; i < size; i++) fi << a[i] << " ";
                }
                else {
                    cout << "Invalid order. Please use '-order' or '-nsorted' or '-sorted' or 'rev'" << endl;
                    return 1;
                }
                fi.close();

                string param = argv[5];

                measureTime = (param == "-time" || param == "-both");
                measureComp = (param == "-comp" || param == "-both");

                cout << "Input size: " << size << endl;
                cout << "Input order: " << order << endl;
                cout << "--------------------------------" << endl;
                RunAlgorithm(algorithm, a, size, measureTime, measureComp);

                ofstream fo("output.txt");
                if (!fo.is_open()) {
                    cout << "Failed to write output!";
                    return 1;
                }
                fo << size << endl;
                for (int i = 0; i < size; i++) fo << a[i] << " ";
                fo.close(); 
            }
        }
        else {
            string filename = argv[3];
            int size;
            a = ParseData(filename, size);
            if (size <= 0 || size > 1000000) {
                cout << "File might not exist or damaged or input range exceeded limit";
                return 1; // Abort when failed to open Input file
            }
            string param = argv[4];

            measureTime = (param == "-time" || param == "-both");
            measureComp = (param == "-comp" || param == "-both");

            cout << "Input file: " << filename << endl;
            cout << "Input size: " << size << endl;
            cout << "--------------------------------" << endl;
            RunAlgorithm(algorithm, a, size, measureTime, measureComp);

            ofstream fo("output.txt");
            if (!fo.is_open()) {
                cout << "Failed to write output!";
                return 1;
            }
            fo << size << endl;
            for (int i = 0; i < size; i++) fo << a[i] << " ";
            fo.close(); 
        }
    }
    else if (mode == "-c") {
        if (argc < 5) {
            cout << "Not enough arguments. Please try again!" << endl;
            return 1;
        }

        string algo1 = argv[2], algo2 = argv[3];
        bool isValid1 = false, isValid2 = false;
        for (int i = 0; i < 12; i++) {
            if (algo1 == algorithms[i]) isValid1 = true;
            if (algo2 == algorithms[i]) isValid2 = true;
        }
        if (!isValid1 || !isValid2) {
            cout << "Invalid algorithm. Please check README.txt" << endl;
            return 1;
        }
        int* a;
        cout << "COMPARE MODE" << endl;

        if (isdigit(argv[4][0])) {
            int size = stoi(string(argv[4]));
            a = new int[size];
            ofstream fi("input.txt");
            if (!fi.is_open()) {
                cout << "Unable to write file";
                return 1;
            }
            fi << size << endl;

            string order = argv[5];

            if (order == "-rand") {
                GenerateData(a, size, 0);
                order = orders[0];
                for (int i = 0; i < size; i++) fi << a[i] << " ";
            }
            else if (order == "-nsorted") {
                GenerateData(a, size, 1);
                order = orders[1];
                for (int i = 0; i < size; i++) fi << a[i] << " ";
            }
            else if (order == "-sorted") {
                GenerateData(a, size, 2);
                order = orders[2];
                for (int i = 0; i < size; i++) fi << a[i] << " ";
            }
            else if (order == "-rev") {
                GenerateData(a, size, 3);
                order = orders[3];
                for (int i = 0; i < size; i++) fi << a[i] << " ";
            }
            else {
                cout << "Invalid order. Please use '-order' or '-nsorted' or '-sorted' or 'rev'" << endl;
                return 1;
            }
            fi.close();

            cout << "Input size: " << size << endl;
            cout << "Input order: " << order << endl;
            cout << "--------------------------------" << endl;

            CompareAlgorithm(algo1, algo2, a, size);
        }
        else {
            string filename = argv[4];
            int size;
            a = ParseData(filename, size);
            if (size <= 0 || size > 1000000) {
                cout << "File might not exist or damaged or input range exceeded limit";
                return 1; // Abort when failed to open Input file
            }

            cout << "Input file: " << filename << endl;
            cout << "Input size: " << size << endl;
            cout << "--------------------------------" << endl;
            CompareAlgorithm(algo1, algo2, a, size);
        }
    }
    else {
        cout << "Invalid mode! Please use '-a' for algorithm mode or '-c' for compare mode"; 
    }

    return 0;
}




// gjonhoenhoeheojheojhbeijhbejyjbeyojeyejy

// bexuanmailonton