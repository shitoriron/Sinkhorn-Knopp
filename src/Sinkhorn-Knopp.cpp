#include<iostream>
#include<iomanip>
#include<vector>
#include<cmath>
#include<chrono>
#include<atcoder/mincostflow>
using namespace std;
using namespace atcoder;
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { for (auto &e : v) os << e << ' '; return os; }
#define dump(x)  cerr << "Line " << __LINE__ << ": " <<  #x << " = " << (x) << "\n";

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

double calculate_violation(const vector<vector<double>> &X, const vector<double> &a, const vector<double> &b){
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

vector<vector<double>> calculate_X(const vector<vector<double>> &K, const vector<double> &u, const vector<double> &v){
    int n = K.size();
    vector<vector<double>> X(n, vector<double>(n));    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            X[i][j] = u[i] * K[i][j] * v[j];
        }
    }
    return X;
}

vector<vector<double>> solve_by_Sinkhorn_Knopp(int n, vector<vector<double>> &C, const vector<double> &a, const vector<double> &b, double lambda){
    vector<vector<double>> K(n, vector<double>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            K[i][j] = exp(-lambda * C[i][j]);
        }
    }

    vector<double> u(n, 1), v(n, 1);
    double obj_old = 0;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            obj_old += C[i][j] * u[i] * K[i][j] * v[j];
        }
    }

    while(true){
        vector<double> p(n), q(n), u_old;

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                p[i] += K[j][i] * u[j];
            }
        }

        for(int i=0;i<n;i++){
            v[i] = b[i] / p[i];
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                q[i] += K[i][j] * v[j];
            }
        }

        for(int i=0;i<n;i++){
            u[i] = a[i] / q[i];
        }

        auto X = calculate_X(K, u, v);
        auto obj = calculate_objective_value(X, C);
        auto violation = calculate_violation(X, a, b);

        // dump(obj)
        // dump(violation)

        if(abs(obj - obj_old) < 1e-5) break;

        swap(obj_old, obj);
    }

    // calculate X, obj, violation
    auto X = calculate_X(K, u, v);

    return X;
}

int main(int argc, char *argv[]){

    int n;
    cin >> n;
    double lambda = stod(argv[1]);

    vector<double> a(n), b(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<n;i++) cin >> b[i];

    vector<vector<double>> C(n, vector<double>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> C[i][j];            
        }
    }

    auto start = chrono::system_clock::now();
    auto X = solve_by_Sinkhorn_Knopp(n, C, a, b, lambda);
    auto end = chrono::system_clock::now();
    auto msec = chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

    auto obj = calculate_objective_value(X, C);
    auto violation = calculate_violation(X, a, b);

    // output objective value and constraint violation
    // cout << obj << ", " << violation << ", " << msec << "\n";
    cout << obj << "\n";
    cout << violation << "\n";
    cout << msec << "\n";

    // output the solution matrix
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << fixed << setprecision(2) << X[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}