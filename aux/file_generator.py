from Cryptodome.Random import random
import string
import os


def generate_file(n_bytes, file_name):

    size = n_bytes * 1000000
    with open(os.getcwd() + '/files/' + file_name + '.txt', 'w') as file:
        for i in range(size):
            
            if i > 0 and i % 100 == 0:
                file.write('\n')
            
            file.write(random.choice(string.ascii_letters))


def lorem_generator(n, file_name):

    lorem = '''Lorem ipsum dolor sit amet, consectetur adipiscing elit, 
sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. 
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. 
Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
Lorem ipsum dolor sit amet, consectetur adipiscing '''

    size = n * 2000
    with open(os.getcwd() + '/files/' + file_name + '.txt', 'w') as file:
        for i in range(size):
                       
            file.write(lorem)
            file.write('\n')


if __name__ == '__main__':

    os.chdir('..')
    
    if not os.path.isdir(os.getcwd() + '/files/'):
        os.mkdir(os.getcwd() + '/files/')

    file_name = str(random.randint(100, 999))

    # Gera os arquivos conforme a quantidade de MB desejada
    lorem_generator(3, file_name)
    #generate_file(3, file_name)
