#include "funcs/file.h"

int main(int argc, char* argv[]) {
    if (argc < 5) { //Minimum amount of arguments needed is 5 (command 1 and command 3)
        cout << "Not enough arguments. Please try again!";
        return 1;
    }

    const string algorithms[12] = {"selection-sort", "insertion-sort", "shell-sort", "bubble-sort", "heap-sort", "merge-sort", "quick-sort", "radix-sort", "counting-sort", "binary-insertion-sort", "shaker-sort", "flash-sort"}; //Checking valid Algorithm input
    const string orders[4] = {"Randomize", "Nearly Sorted", "Sorted", "Reversed"}; //Used for command 3
    string mode = argv[1]; //Argument 2: [Mode]
    if (mode == "-a") {    //Algorithm mode
        cout << "ALGORITHM MODE" << endl;
        string algorithm = argv[2]; //Third argument : [Algorithm]
        bool isValid = false;
        for (int i = 0; i < 12; i++) if (algorithm == algorithms[i]) isValid = true; //Check if user algorithm input is correct
        if (!isValid) { //Invalid algorithm
            cout << "Invalid algorithm. Please check README.txt" << endl;
            return 1;
        } 
        int* a;
        long long comparisons; 
        bool measureTime = false, measureComp = false; //Checking valid input for [Output Parameters] 

        if (isdigit(argv[3][0])) {  //Checking if its a Generated Input or Manual Input, if its generated then Argument 4: [Input size]
            int size = stoi(string(argv[3]));
            if (size < 0 || size > 1000000) { //Input size : Integer (<= 1 000 000)
                cout << "Invalid input size, please pick a size ranging from 1 to 1000000" << endl;
                return 1;
            }
            a = new int[size];
            if (argc > 4 && argc <= 5) { //Command 3: Run sorting algorithm on ALL data arragements of a specific size
                string param = argv[4]; //Argument 5: [Output Paramaters]
                measureTime = (param == "-time" || param == "-both"); //[Output Parameters] time or both
                measureComp = (param == "-comp" || param == "-both"); //[Output Parameters] comparison or both
                if (!measureTime && !measureComp) { //Invalid input for [Output Parameters]
                    cout << "Parameters might be incorrect. Please check README.txt!" << endl;
                    return 1;
                }
                cout << "Input size: " << size << endl;
                cout << endl;
                for (int i = 0; i < 4; i++) { //Generating Data for all input order 
                    cout << "Input order: " << orders[i] << endl;
                    cout << "--------------------------------" << endl;
                    GenerateData(a, size, i);
                    ofstream fi("input_" + to_string(i + 1) + ".txt"); //Opening input file
                    if (!fi.is_open()) {
                        cout << "Failed to write input!";
                        return 1;
                    }
                    fi << size << endl; //Putting array size in input file
                    for (int i = 0; i < size; i++) fi << a[i] << " ";  //Putting generated data in input file
                    fi.close();
                    RunAlgorithm(algorithm, a, size, measureTime, measureComp); //Sorting generated array with an algorithm
                    cout << endl;
                }
            }
            else if (argc > 5) { //Command 2: Run a sorting algorithm on data generated with specified size and order
                ofstream fi("input.txt"); //Opening input file
                if (!fi.is_open()) { 
                    cout << "Unable to write file";
                    return 1;
                }
                fi << size << endl;

                string order = argv[4]; //Argument 5: [Input order]
                if (order == "-rand") { 
                    GenerateData(a, size, 0); //Generate array
                    order = orders[0]; 
                    for (int i = 0; i < size; i++) fi << a[i] << " "; //Put generated array in input file
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

                string param = argv[5]; //Argument 6: [Output paramaters]

                measureTime = (param == "-time" || param == "-both"); //[Output Parameters] time or both
                measureComp = (param == "-comp" || param == "-both"); //[Output Parameters] comparison or both

                cout << "Input size: " << size << endl;
                cout << "Input order: " << order << endl;
                cout << "--------------------------------" << endl;
                RunAlgorithm(algorithm, a, size, measureTime, measureComp); //Sorting generated array with an algorithm

                ofstream fo("output.txt"); //Opening output file
                if (!fo.is_open()) {
                    cout << "Failed to write output!";
                    return 1;
                }
                fo << size << endl;
                for (int i = 0; i < size; i++) fo << a[i] << " "; //Put sorted array in output file
                fo.close(); 
            }
        }
        else { //Manual input 
            string filename = argv[3]; //Argument 4: [Given input(file)]
            int size;
            a = ParseData(filename, size); //Putting input file data into the array
            if (size <= 0 || size > 1000000) { //Input size: Integer (<= 1 000 000) 
                cout << "File might not exist or damaged or input range exceeded limit";
                return 1; 
            }
            string param = argv[4]; //Argument 5: [Output Parameters]

            measureTime = (param == "-time" || param == "-both"); //[Output Paramaters] time or both
            measureComp = (param == "-comp" || param == "-both"); //[Output Paramaters] comparison or both
            if (!measureTime && !measureComp) { //Invalid input for [Output Parameters]
                cout << "Parameters might be incorrect. Please check README.txt!" << endl;
                return 1;
            }
            cout << "Input file: " << filename << endl;
            cout << "Input size: " << size << endl;
            cout << "--------------------------------" << endl;
            RunAlgorithm(algorithm, a, size, measureTime, measureComp); //Sorting array with an algorithm

            ofstream fo("output.txt"); //Opening output file
            if (!fo.is_open()) {
                cout << "Failed to write output!";
                return 1;
            }
            fo << size << endl;
            for (int i = 0; i < size; i++) fo << a[i] << " "; //Put sorted array in output file
            fo.close(); 
        }
    }
    else if (mode == "-c") { //Comparison mode
        if (argc < 5) { //Minimum amount of arguments needed is 5 (command 4)
            cout << "Not enough arguments. Please try again!" << endl;
            return 1;
        }

        string algo1 = argv[2], algo2 = argv[3]; //Argument 3: [Algorithm 1] , Argument 4: [Algorithm 2]
        bool isValid1 = false, isValid2 = false;
        for (int i = 0; i < 12; i++) { //Checking valid algorithms
            if (algo1 == algorithms[i]) isValid1 = true;
            if (algo2 == algorithms[i]) isValid2 = true;
        }
        if (!isValid1 || !isValid2) { //Same algorithms
            cout << "Invalid algorithm. Please check README.txt" << endl;
            return 1;
        }
        int* a;
        cout << "COMPARE MODE" << endl;

        if (isdigit(argv[4][0])) { ////Checking if its a Generated Input or Manual Input, if its generated then Argument 5: [Input size]
            int size = stoi(string(argv[4]));
            a = new int[size];
            ofstream fi("input.txt"); //Opening input file
            if (!fi.is_open()) {
                cout << "Unable to write file";
                return 1;
            }
            fi << size << endl; //Putting size in input file

            string order = argv[5]; //Argument 6: [Input order]

            if (order == "-rand") {
                GenerateData(a, size, 0); //Generate array
                order = orders[0];
                for (int i = 0; i < size; i++) fi << a[i] << " "; //Put generated array in file
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
            else { //Invalid input order
                cout << "Invalid order. Please use '-order' or '-nsorted' or '-sorted' or 'rev'" << endl;
                return 1;
            }
            fi.close();

            cout << "Input size: " << size << endl;
            cout << "Input order: " << order << endl;
            cout << "--------------------------------" << endl;

            CompareAlgorithm(algo1, algo2, a, size); //Output comparison result
        }
        else { //Manual input 
            string filename = argv[4]; //Argument 5: [Given input(file)]
            int size;
            a = ParseData(filename, size); //Putting input file data into the array
            if (size <= 0 || size > 1000000) { //Input size: Integer (<= 1 000 000)
                cout << "File might not exist or damaged or input range exceeded limit";
                return 1; 
            }

            cout << "Input file: " << filename << endl;
            cout << "Input size: " << size << endl;
            cout << "--------------------------------" << endl;
            CompareAlgorithm(algo1, algo2, a, size); //Output comparison result
        }
    }
    else { //Invalid mode
        cout << "Invalid mode! Please use '-a' for algorithm mode or '-c' for compare mode"; 
    }

    // // FOR TESTING PURPOSE
    // // ====================================================================
    // string testmode = argv[1];
    // string al = argv[2];
    // string ord = argv[3];
    // long long comp;
    // milliseconds tim;
    // int siz = stoi(argv[4]);
    // int *arr = new int[siz];

    // int resT[100] = {}, resC[100] = {};
    // for (int i = 0; i < 4; i++) {
    //     GenerateData(arr, siz, i);
    //     for (int j = 0; j < 100; j++) {
    //         RunAlgorithmtest(al, arr, siz, comp, tim);
    //         resT[j] = tim.count();
    //         resC[j] = comp;
    //     }
    //     for (int i = 0; i < 100; i++) cout << resT[i] << " ";
    //     for (int i = 0; i < 100; i++) cout << resC[i] << " ";
    //     cout << endl;
    // }
    return 0;
}
