import matplotlib.pyplot as plt


def plot_time(buffer, t_3, t_30, t_100):
    
    plt.grid()
    plt.title("Tempo de Transmissão")
    plt.xlabel('Tamanho do Buffer')
    plt.ylabel('Tempo Gasto (segundos)')
    
    plt.plot(buffer, t_3, color='g', label='3 MB')
    plt.plot(buffer, t_30, color='y', label='30 MB')
    plt.plot(buffer, t_100, color='r', label='100 MB')
    plt.legend(loc='best')
    plt.show()


def plot_rate(buffer, r_3, r_30, r_100):
    
    plt.grid()
    plt.title("Tempo de Transmissão")
    plt.xlabel('Tamanho do Buffer')
    plt.ylabel('Taxa de Transmissão (Kbps)')
    
    plt.plot(buffer, r_3, color='g', label='3 MB')
    plt.plot(buffer, r_30, color='y', label='30 MB')
    plt.plot(buffer, r_100, color='r', label='100 MB')
    plt.legend(loc='best')
    plt.show()


def main():
    
    buffer = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048]

    t_3 = [1.058, 0.401, 0.176, 0.096, 0.11, 0.047, 0.023, 0.047, 0.028, 0.048, 0.07]
    t_30 = [10.238, 3.901, 1.725, 0.785, 0.48, 0.306, 0.27, 0.27, 0.28, 0.294, 0.368]
    t_100 = [43.45, 12.807, 5.67, 2.625, 1.513, 0.959, 0.802, 0.809, 0.856, 0.996, 1.287]

    r_3 = [45476.94 , 80976.67, 161368.36, 287237.03, 265458.71, 655793.7, 1579705.18, 1559720.75, 5188823.98, 6165063.97, 8406721.68]
    r_30 = [46975.68, 83176.28, 164777.43, 352121.73, 607541.81, 1003639.5, 1363187.58, 2735397.89, 5262338.96, 10035287.11, 16010119.24]
    r_100 = [36897.98, 84456.54, 167056.68, 351025.27, 642762.61, 1068174.35, 1532469.57, 3037892.07, 5741720.69, 9867997.07, 19474089.03]

    plot_time(buffer, t_3, t_30, t_100)
    plot_rate(buffer, r_3, r_30, r_100)


if __name__ == '__main__':
    main()
