#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputfile>\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Error: cannot open input file.\n";
        return 1;
    }

    int n, m;
    fin >> n >> m;  // n processes, m resource types

    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> maxm(n, vector<int>(m));
    vector<int> avail(m);

    // Read Allocation matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fin >> alloc[i][j];

    // Read Max matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fin >> maxm[i][j];

    // Read Available vector
    for (int j = 0; j < m; j++)
        fin >> avail[j];

    fin.close();

    // Compute Need matrix
    vector<vector<int>> need(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maxm[i][j] - alloc[i][j];

    vector<int> work = avail;
    vector<bool> finish(n, false);
    vector<int> safeSeq;

    // Safety algorithm
    while ((int)safeSeq.size() < n) {
        bool progress = false;

        for (int i = 0; i < n; i++) {
            if (finish[i]) continue;

            bool canRun = true;
            for (int j = 0; j < m; j++) {
                if (need[i][j] > work[j]) {
                    canRun = false;
                    break;
                }
            }

            if (canRun) {
                // pretend process i finishes
                for (int j = 0; j < m; j++)
                    work[j] += alloc[i][j];

                finish[i] = true;
                safeSeq.push_back(i);
                progress = true;
            }
        }

        if (!progress) break; // no suitable process found => unsafe
    }

    if ((int)safeSeq.size() == n) {
        cout << "System is in a SAFE state.\nSafe sequence: ";
        for (int i = 0; i < n; i++) {
            cout << "P" << safeSeq[i];
            if (i != n - 1) cout << " -> ";
        }
        cout << "\n";
    } else {
        cout << "System is in an UNSAFE state. No safe sequence exists.\n";
    }

    return 0;
}
