import random


def create_pair(size_union: int, U: int = 2**30, J: float = 0.5) -> tuple[set, set]:
    """
    Genera una coppia di insiemi A, B tali che:
        - gli elementi sono compresi tra 0 e `U`-1
        - la Jaccard similarity tra A e B è **in media** `J`
        - la dimensione di A U B è `size_union`

    Parameters
    :param int size_union: numero di elementi nell'unione di A e B
    :param int U: numero di elementi totali nell'universo
    :param float J: Jaccard similarity tra A e B
    :return: the two sets A, B
    :rtype: tuple[set, set]
    """
    AUB = set(random.sample(range(U), size_union))

    I = set([x for x in AUB if random.random() <= J])

    A, B = set(), set()

    for x in AUB - I:
        if random.random() <= 0.5:
            A.add(x) 
        else:
            B.add(x)

    A = A | I
    B = B | I

    return A, B


def create_dataset(N: int, size_union: int, J: float, U: int = 2**30):
    """
    Genera un dataset di `N` coppie di insiemi (A, B) tali che:
        - gli elementi sono compresi tra 0 e `U`-1
        - la Jaccard similarity tra A e B è **in media** `J`
        - la dimensione di A U B è `size_union`

    Il file è strutturato nel seguente modo:
        - il nome del file è `dataset_{J}.txt`, per esempio `dataset_0.95.txt` quando J=0.95
        - il file è composto da blocchi di 3 righe, separate dal simbolo `#`, dove:
            - la prima riga contiene gli elementi di A
            - la seconda riga contiene gli elementi di B
            - la terza riga contiene la Jaccard similarity tra A e B

    Esempio:
        Abbiamo J=0.5 e le coppie di insiemi A_1 = {1,3,7}, B_1 = {3,5,7} e A_2 = {7,8,9,10,11,12,13,14,15}, B_2={7,9,11,12}

        Il file `dataset_0.5.txt` sarà così strutturato:
        ```
        1 3 7
        3 5 7
        0.5
        #
        7 8 9 10 11 12 13 14 15
        7 9 11 12
        0.444444
        #
        ```
    """
    with open(f"dataset_{J}.txt", "w") as f:
        for _ in range(N):
            A, B = create_pair(size_union, U, J)
            f.write(" ".join(map(str, A)) + "\n")
            f.write(" ".join(map(str, B)) + "\n")
            f.write(f"{len(A & B) / len(A | B)}\n")
            f.write("#\n")


if __name__ == "__main__":
    # A, B = create_pair(10_000, J=0.95)
    # print(len(A & B) / len(A | B), len(A), len(B))

    # esempio
    N = 1
    size_union = 100
    J = 0.47
    create_dataset(N, size_union, J)
