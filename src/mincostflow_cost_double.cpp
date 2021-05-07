#include<iostream>
#include<iomanip>
#include<vector>
#include<atcoder/mincostflow>
using namespace std;
using namespace atcoder;

const int64_t integer_factor = 1e9;

double calculate_objective_value(const vector<vector<double>> &X, const vector<vector<double>> &C){
    int n = X.size();
    double obj = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            obj += X[i][j] * C[i][j];
        }
    }
    return obj;
}

double calculate_violation(const vector<vector<double>> &X, const vector<int> &a, const vector<int> &b){
    int n = X.size();
    double violation = 0;
    vector<double> row_sum(n, 0), col_sum(n, 0);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            row_sum[i] += X[i][j];
            col_sum[j] += X[i][j];
        }
    }
    for(int i=0;i<n;i++) violation += abs(a[i] - row_sum[i]);
    for(int i=0;i<n;i++) violation += abs(b[i] - col_sum[i]);
    return violation;
}

vector<vector<double>> solve_by_mincostflow_double(int n, vector<vector<double>> &C, const vector<int> &a, const vector<int> &b){
    mcf_graph<int, int64_t> graph(2*n+2);
    int s = 2 * n;
    int t = s + 1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int64_t integer_C = C[i][j] * integer_factor;
            graph.add_edge(i, n+j, a[i], integer_C);   
        }
    }
    for(int i=0;i<n;i++){
        graph.add_edge(s, i, a[i], 0);
    }
    for(int i=0;i<n;i++){
        graph.add_edge(n+i, t, b[i], 0);
    }

    graph.flow(s, t);

    vector<vector<double>> X(n, vector<double>(n));    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            X[i][j] = graph.get_edge(i*n+j).flow;
        }
    }

    return X;
}

int main(){

    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<n;i++) cin >> b[i];

    vector<vector<double>> C(n, vector<double>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> C[i][j];            
        }
    }

    auto start = chrono::system_clock::now();
    auto X = solve_by_mincostflow_double(n, C, a, b);
    auto end = chrono::system_clock::now();
    auto msec = chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

    auto obj = calculate_objective_value(X, C);
    auto violation = calculate_violation(X, a, b);

    cout << obj << ", " << violation << ", " << msec << "\n";

    // output the solution matrix
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << fixed << setprecision(2) << X[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}