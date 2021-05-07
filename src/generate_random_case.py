import numpy as np
import argparse

def generate_random(args):
    p = [1.0/args.n] * args.n
    a = np.random.multinomial(args.m, p, size=1)
    b = np.random.multinomial(args.m, p, size=1)
    # C = np.random.randint(1, 100, size=[args.n, args.n])
    C = np.random.rand(args.n, args.n)
    return a[0], b[0], C

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--n', type=int, default=10)
    parser.add_argument('--m', type=int, default=10)
    args = parser.parse_args()

    a, b, C = generate_random(args)

    print(args.n)

    for x in a:
        print(x, end=' ')
    print("")

    for x in b:
        print(x, end=' ')
    print("")

    for x in C:
        for y in x:
            print(y, end=' ')
        print("")

if __name__ == "__main__":
    main()
