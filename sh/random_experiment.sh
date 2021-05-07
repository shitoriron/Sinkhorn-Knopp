# compile 
clang++ src/mincostflow.cpp -o src/mincostflow -std=c++17 -I /Users/akagiyasunori/Work/procon/lib/ac-library/ -O2
clang++ src/Sinkhorn-Knopp.cpp -o src/Sinkhorn-Knopp -O2

# generate testcases
for n in 10 100 1000 1000
do
    for m in 1000
    do
        for trial in $(seq 0 9)
        do
            python3 src/generate_random_case.py --n ${n} --m ${m} > input/n_${n}_m_${m}_trial_${trial}.in
        done
    done
done

# solve

for n in 10 100 1000 1000
do
    for m in 1000
    do
        for trial in $(seq 0 9)
        do

            res_mcf=$(src/mincostflow < input/n_${n}_m_${m}_trial_${trial}.in)
            echo mcf, $n, $m, $trial, $res_mcf

            res_SK=$(src/Sinkhorn-Knopp 1 < input/n_${n}_m_${m}_trial_${trial}.in)
            echo SK, $n, $m, $trial, $res_SK
        done
    done
done