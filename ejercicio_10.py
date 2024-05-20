import multiprocessing

def generar_serie(start, end):
    serie = [(i + 1) * 2 for i in range(start, end)]
    return serie

def main():
    N = int(input("Ingrese el número de términos (N): "))
    M = int(input("Ingrese el número de procesos (M): "))

    # Calcular el número de términos por proceso
    terms_per_process = N // M
    remaining_terms = N % M

    pool = multiprocessing.Pool(processes=M)
    tasks = []

    start = 0
    for i in range(M):
        end = start + terms_per_process
        if i == M - 1:
            end += remaining_terms  # El último proceso toma los términos restantes
        tasks.append((start, end))
        start = end

    results = pool.starmap(generar_serie, tasks)

    # Unir los resultados en una sola lista
    serie_completa = [item for sublist in results for item in sublist]

    # Imprimir la serie generada
    print("Serie generada:")
    print(serie_completa)

if __name__ == "__main__":
    main()
