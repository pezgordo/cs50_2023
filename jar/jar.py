class Jar:
    def __init__(self, capacity=12):
        self._capacity = capacity
        if self._capacity < 0:
            raise ValueError("Capacity can't be nagative")

    def __str__(self):
        return f"there are {self.capacity} in the jar"

    def deposit(self, n):

        _level = 0

        _level = _level + n

        if _level > self._capacity:
            raise ValueError("capacity reached")



    def withdraw(self, n):

        self._capacity = self.capacity - n

        if self._capacity < 0:
            raise ValueError("no more cookies")




    @property
    def capacity(self):

       return self._capacity


    @property
    def size(self):
            return self._capacity

    @size.setter
    def size(self, n):
        self._size = n



def main():

    jar = Jar()

    jar.withdraw(1)

    print(str(jar.capacity))



if __name__ == "__main__":
    main()