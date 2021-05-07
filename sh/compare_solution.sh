# compile 
clang++ src/mincostflow_cost_double.cpp -o src/mincostflow_cost_double -std=c++17 -I /Users/akagiyasunori/Work/procon/lib/ac-library/ -O2
clang++ src/Sinkhorn-Knopp.cpp -o src/Sinkhorn-Knopp -O2

rm input/*

# generate testcases
trials=0
multiplier=10
for n in 10
do
    m=$((n * multiplier))
    for trial in $(seq 0 $trials)
    do
        python3 src/generate_random_case.py --n ${n} --m ${m} > input/n_${n}_m_${m}_trial_${trial}.in
    done
done

# solve

for n in 10
do
    m=$((n * multiplier))
    for trial in $(seq 0 $trials)
    do
        src/mincostflow_cost_double < input/n_${n}_m_${m}_trial_${trial}.in > output/mcf.out

        for lambda in 1 5 10 50 100 500
        do
            src/Sinkhorn-Knopp ${lambda} < input/n_${n}_m_${m}_trial_${trial}.in > output/SK_lambda_${lambda}.out
        done
    done
done