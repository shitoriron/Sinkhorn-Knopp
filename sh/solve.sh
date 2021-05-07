for n in 10 100 1000
do
    for m in 10 100 1000 1000
    do
        python3 src/generate_random_case.py --n ${n} --m ${m} > input/n_${n}_m_${m}.in
    done
done