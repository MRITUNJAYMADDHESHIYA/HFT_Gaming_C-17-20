#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        // Feasibility check
        if ((n % 2 == 0) && (k % 2 == 1)) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";
        vector<string> grid(n, string(n, 'R'));

        // Step 1: base pattern (2-cycles)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j % 2 == 0) grid[i][j] = 'R';
                else grid[i][j] = 'L';
            }
        }

        // Step 2: convert top-row dominoes to escape (U)
        int remaining = k;
        for (int i = 0; i < n && remaining > 0; ++i) {
            for (int j = 0; j + 1 < n && remaining > 0; j += 2) {
                if (remaining >= 2) {
                    // convert both to escape cells
                    grid[i][j] = 'U';
                    grid[i][j + 1] = 'U';
                    remaining -= 2;
                }
            }
        }

        // Step 3: if n is odd and we still need 1 more
        if (remaining == 1 && n % 2 == 1) {
            grid[n - 1][n - 1] = 'U';
            remaining--;
        }

        // Print grid
        for (int i = 0; i < n; ++i)
            cout << grid[i] << "\n";
    }

    return 0;
}
