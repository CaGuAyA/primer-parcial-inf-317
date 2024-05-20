import multiprocessing
import random
import time

def monte_carlo_pi_part(num_puntos):
    count = 0
    for _ in range(num_puntos):
        x = random.random()
        y = random.random()
        if x * x + y * y <= 1.0:
            count += 1
    return count

def calculate_pi(total_puntos, num_procesos):
    puntos_por_proceso = total_puntos // num_procesos
    pool = multiprocessing.Pool(processes=num_procesos)

    results = pool.map(monte_carlo_pi_part, [puntos_por_proceso] * num_procesos)

    cir_total = sum(results)
    pi_estimado = (4.0 * cir_total) / total_puntos

    return pi_estimado

if __name__ == "__main__":
    total_puntos = int(input("Ingresa el numero de puntos: "))
    num_procesos = int(input("Ingresa el numero de procesadores: "))

    start_time = time.time()
    pi_estimado = calculate_pi(total_puntos, num_procesos)
    end_time = time.time()

    print(f"Valor estimado de PI: {pi_estimado}")
    print(f"Time tomado: {end_time - start_time} segundos")
