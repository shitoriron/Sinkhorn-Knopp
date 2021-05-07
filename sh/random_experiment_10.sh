# compile 
clang++ src/mincostflow.cpp -o src/mincostflow -std=c++17 -I /Users/akagiyasunori/Work/procon/lib/ac-library/ -O2
clang++ src/mincostflow_cost_double.cpp -o src/mincostflow_cost_double -std=c++17 -I /Users/akagiyasunori/Work/procon/lib/ac-library/ -O2
clang++ src/Sinkhorn-Knopp.cpp -o src/Sinkhorn-Knopp -O2

rm input/*

# generate testcases
trials=3
multiplier=1
for n in 20 200 2000
do
    m=$((n * multiplier))
    for trial in $(seq 0 $trials)
    do
        python3 src/generate_random_case.py --n ${n} --m ${m} > input/n_${n}_m_${m}_trial_${trial}.in
    done
done

# solve

for n in 20 200 2000
do
    m=$((n * multiplier))
    for trial in $(seq 0 $trials)
    do
        #res_mcf=$(src/mincostflow < input/n_${n}_m_${m}_trial_${trial}.in)
        res_mcf=$(src/mincostflow_cost_double < input/n_${n}_m_${m}_trial_${trial}.in)
        echo mcf, $n, $m, $trial, $res_mcf

        res_SK=$(src/Sinkhorn-Knopp 2000 < input/n_${n}_m_${m}_trial_${trial}.in)
        echo SK, $n, $m, $trial, $res_SK
    done
done