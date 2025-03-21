#include "funcs/file.h"
#include <vector>

double averageT(vector<long long> a, int n)
{
    double res = 0;
    for (int i = 0; i < n; i++)
        res += (long long)a[i];
    return (double)res / n;
}

long long averageC(vector<long long> a, int n)
{
    long long res = 0;
    for (int i = 0; i < n; i++)
        res += (long long)a[i];
    return (long long)res / n;
}

int main(int argc, char *argv[])
{
    // if (argc < 4) {
    //     cout << "Not enough arguments. Please try again!";
    //     return 1;
    // }

    const string algorithms[12] = {"selection-sort", "insertion-sort", "shell-sort", "bubble-sort", "heap-sort", "merge-sort", "quick-sort", "radix-sort", "counting-sort", "binary-insertion-sort", "shaker-sort", "flash-sort"};
    const string orders[4] = {"Randomize", "Nearly Sorted", "Sorted", "Reversed"};
    string mode = argv[1];
    if (mode == "-a")
    {
        cout << "ALGORITHM MODE" << endl;
        string algorithm = argv[2];
        bool isValid = false;
        for (int i = 0; i < 12; i++)
            if (algorithm == algorithms[i])
                isValid = true;
        if (!isValid)
        {
            cout << "Invalid algorithm. Please check README.txt" << endl;
            return 1;
        }
        int *a;
        long long comparisons;
        bool measureTime = false, measureComp = false;

        if (isdigit(argv[3][0]))
        {
            int size = stoi(string(argv[3]));
            if (size < 0 || size > 1000000)
            {
                cout << "Invalid input size, please pick a size ranging from 1 to 1000000" << endl;
                return 1;
            }
            a = new int[size];
            if (argc > 4 && argc <= 5)
            {
                string param = argv[4];
                measureTime = (param == "-time" || param == "-both");
                measureComp = (param == "-comp" || param == "-both");
                if (!measureTime && !measureComp)
                {
                    cout << "Parameters might be incorrect. Please check README.txt!" << endl;
                    return 1;
                }
                cout << "Input size: " << size << endl;
                cout << endl;
                for (int i = 0; i < 4; i++)
                {
                    cout << "Input order: " << orders[i] << endl;
                    cout << "--------------------------------" << endl;
                    GenerateData(a, size, i);
                    ofstream fi("input_" + to_string(i + 1) + ".txt");
                    if (!fi.is_open())
                    {
                        cout << "Failed to write input!";
                        return 1;
                    }
                    fi << size << endl;
                    for (int i = 0; i < size; i++)
                        fi << a[i] << " ";
                    fi.close();
                    RunAlgorithm(algorithm, a, size, measureTime, measureComp);
                    cout << endl;
                }
            }
            else if (argc > 5)
            {
                ofstream fi("input.txt");
                if (!fi.is_open())
                {
                    cout << "Unable to write file";
                    return 1;
                }
                fi << size << endl;

                string order = argv[4];
                if (order == "-rand")
                {
                    GenerateData(a, size, 0);
                    order = orders[0];
                    for (int i = 0; i < size; i++)
                        fi << a[i] << " ";
                }
                else if (order == "-nsorted")
                {
                    GenerateData(a, size, 1);
                    order = orders[1];
                    for (int i = 0; i < size; i++)
                        fi << a[i] << " ";
                }
                else if (order == "-sorted")
                {
                    GenerateData(a, size, 2);
                    order = orders[2];
                    for (int i = 0; i < size; i++)
                        fi << a[i] << " ";
                }
                else if (order == "-rev")
                {
                    GenerateData(a, size, 3);
                    order = orders[3];
                    for (int i = 0; i < size; i++)
                        fi << a[i] << " ";
                }
                else
                {
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
                if (!fo.is_open())
                {
                    cout << "Failed to write output!";
                    return 1;
                }
                fo << size << endl;
                for (int i = 0; i < size; i++)
                    fo << a[i] << " ";
                fo.close();
            }
        }
        else
        {
            string filename = argv[3];
            int size;
            a = ParseData(filename, size);
            if (size <= 0 || size > 1000000)
            {
                cout << "File might not exist or damaged or input range exceeded limit";
                return 1; // Abort when failed to open Input file
            }
            string param = argv[4];

            measureTime = (param == "-time" || param == "-both");
            measureComp = (param == "-comp" || param == "-both");
            if (!measureTime && !measureComp)
            {
                cout << "Parameters might be incorrect. Please check README.txt!" << endl;
                return 1;
            }
            cout << "Input file: " << filename << endl;
            cout << "Input size: " << size << endl;
            cout << "--------------------------------" << endl;
            RunAlgorithm(algorithm, a, size, measureTime, measureComp);

            ofstream fo("output.txt");
            if (!fo.is_open())
            {
                cout << "Failed to write output!";
                return 1;
            }
            fo << size << endl;
            for (int i = 0; i < size; i++)
                fo << a[i] << " ";
            fo.close();
        }
    }
    else if (mode == "-c")
    {
        if (argc < 5)
        {
            cout << "Not enough arguments. Please try again!" << endl;
            return 1;
        }

        string algo1 = argv[2], algo2 = argv[3];
        bool isValid1 = false, isValid2 = false;
        for (int i = 0; i < 12; i++)
        {
            if (algo1 == algorithms[i])
                isValid1 = true;
            if (algo2 == algorithms[i])
                isValid2 = true;
        }
        if (!isValid1 || !isValid2)
        {
            cout << "Invalid algorithm. Please check README.txt" << endl;
            return 1;
        }
        int *a;
        cout << "COMPARE MODE" << endl;

        if (isdigit(argv[4][0]))
        {
            int size = stoi(string(argv[4]));
            a = new int[size];
            ofstream fi("input.txt");
            if (!fi.is_open())
            {
                cout << "Unable to write file";
                return 1;
            }
            fi << size << endl;

            string order = argv[5];

            if (order == "-rand")
            {
                GenerateData(a, size, 0);
                order = orders[0];
                for (int i = 0; i < size; i++)
                    fi << a[i] << " ";
            }
            else if (order == "-nsorted")
            {
                GenerateData(a, size, 1);
                order = orders[1];
                for (int i = 0; i < size; i++)
                    fi << a[i] << " ";
            }
            else if (order == "-sorted")
            {
                GenerateData(a, size, 2);
                order = orders[2];
                for (int i = 0; i < size; i++)
                    fi << a[i] << " ";
            }
            else if (order == "-rev")
            {
                GenerateData(a, size, 3);
                order = orders[3];
                for (int i = 0; i < size; i++)
                    fi << a[i] << " ";
            }
            else
            {
                cout << "Invalid order. Please use '-order' or '-nsorted' or '-sorted' or 'rev'" << endl;
                return 1;
            }
            fi.close();

            cout << "Input size: " << size << endl;
            cout << "Input order: " << order << endl;
            cout << "--------------------------------" << endl;

            CompareAlgorithm(algo1, algo2, a, size);
        }
        else
        {
            string filename = argv[4];
            int size;
            a = ParseData(filename, size);
            if (size <= 0 || size > 1000000)
            {
                cout << "File might not exist or damaged or input range exceeded limit";
                return 1; // Abort when failed to open Input file
            }

            cout << "Input file: " << filename << endl;
            cout << "Input size: " << size << endl;
            cout << "--------------------------------" << endl;
            CompareAlgorithm(algo1, algo2, a, size);
        }
    }
    // else {
    //     cout << "Invalid mode! Please use '-a' for algorithm mode or '-c' for compare mode";
    // }

    // FOR TESTING PURPOSE
    // ====================================================================
    const string algorithmsDB[12] = {"selection-sort", "insertion-sort", "bubble-sort", "heap-sort", "merge-sort", "quick-sort", "counting-sort", "radix-sort", "flash-sort", "shaker-sort", "shell-sort", "binary-insertion-sort"};
    const int siz[6] = {10000, 30000, 50000, 100000, 300000, 500000};
    string testmode = argv[1];
    if (testmode == "-t") {

        long long comp;
        milliseconds tim(0);
        bool issorted = false;
        vector<long long> resT(10, 0), resC(10, 0);

        if (argc > 2) {
            int SIZE = stoi(argv[2]);
            vector<int> arr(SIZE);
            ofstream fo("results_" + to_string(SIZE) + ".txt");
            for (int i = 0; i < 4; i++)
            { // 4 data types
                fo << "Order: " << orders[i] << endl;
                if (i == 0 || i == 1)
                {
                    for (int k = 0; k < 12; k++)
                    { // Each algorithm
                        resT.assign(10, 0);
                        resC.assign(10, 0);
                        for (int j = 0; j < 10; j++)
                        { // 10 tests for each algorithm
                            GenerateData(arr.data(), SIZE, i);
                            RunAlgorithmtest(algorithmsDB[k], arr.data(), SIZE, comp, tim, issorted);
                            resT[j] = tim.count();
                            resC[j] = comp;
                        }
                        // Enable to show results
                        // for (int i = 0; i < 100; i++) fo << resT[i] << " ";
                        // for (int i = 0; i < 100; i++) fo << resC[i] << " ";
                        fo << endl;
                        fo << "Algorithm: " << algorithmsDB[k] << endl;
                        fo << "Average Time: " << averageT(resT, 10) << endl;
                        fo << "Average Comparisons " << averageC(resC, 10) << endl;
                        fo << "===============================================" << endl;
                    }
                }
                else if (i == 2 || i == 3)
                {
                    issorted = true;
                    for (int k = 0; k < 12; k++)
                    { // Each algorithm
                        resT.assign(10, 0);
                        GenerateData(arr.data(), SIZE, i);
                        for (int j = 0; j < 10; j++) {
                            RunAlgorithmtest(algorithmsDB[k], arr.data(), SIZE, comp, tim, issorted);
                            resT[j] = tim.count();
                        }
                        fo << endl;
                        fo << "Algorithm: " << algorithmsDB[k] << endl;
                        fo << "Average Time: " << averageT(resT, 10) << endl;
                        sortwithcomp(algorithmsDB[k], arr.data(), SIZE, comp);
                        fo << "Comparisons: " << comp << endl;
                        fo << "==============================================";
                    }
                    fo << "+++++++++++++++++++++++++++++++++++++++" << endl;
                    fo << "+++++++++++++++++++++++++++++++++++++++" << endl;
                }
            }
            return 1;
        }

        // TO RUN ALL IN ONE "-t"
        
        for (int sz = 0; sz < 6; sz++)
        { // 6 size
            int SIZE = siz[sz];
            ofstream fo("size_" + to_string(SIZE) + ".txt");
            fo << "SIZE: " << SIZE << endl;
            vector<int> arr(SIZE);
            for (int i = 0; i < 4; i++)
            { // 4 data types
                fo << "Order: " << orders[i] << endl;
                if (i == 0 || i == 1)
                {
                    for (int k = 0; k < 12; k++)
                    { // Each algorithm
                        resT.assign(10, 0);
                        resC.assign(10, 0);
                        for (int j = 0; j < 10; j++)
                        { // 10 tests for each algorithm
                            GenerateData(arr.data(), SIZE, i);
                            RunAlgorithmtest(algorithmsDB[k], arr.data(), SIZE, comp, tim, issorted);
                            resT[j] = tim.count();
                            resC[j] = comp;
                        }
                        // Enable to show results
                        // for (int i = 0; i < 100; i++) fo << resT[i] << " ";
                        // for (int i = 0; i < 100; i++) fo << resC[i] << " ";
                        fo << endl;
                        fo << "Algorithm: " << algorithmsDB[k] << endl;
                        fo << "Average Time: " << averageT(resT, 10) << endl;
                        fo << "Average Comparisons " << averageC(resC, 10) << endl;
                        fo << "===============================================" << endl;
                    }
                }
                else if (i == 2 || i == 3)
                {
                    issorted = true;
                    for (int k = 0; k < 12; k++)
                    { // Each algorithm
                        resT.assign(10, 0);
                        GenerateData(arr.data(), SIZE, i);
                        for (int j = 0; j < 10; j++) {
                            RunAlgorithmtest(algorithmsDB[k], arr.data(), SIZE, comp, tim, issorted);
                            resT[j] = tim.count();
                        }
                        fo << endl;
                        fo << "Algorithm: " << algorithmsDB[k] << endl;
                        fo << "Average Time: " << averageT(resT, 10) << endl;
                        sortwithcomp(algorithmsDB[k], arr.data(), SIZE, comp);
                        fo << "Comparisons: " << comp << endl;
                        fo << "==============================================";
                    }
                    fo << "+++++++++++++++++++++++++++++++++++++++" << endl;
                    fo << "+++++++++++++++++++++++++++++++++++++++" << endl;
                }
            }
            fo << "---------------------------------------------" << endl;
            fo << "---------------------------------------------" << endl;
            fo.close();
        }
    }
    return 0;
}