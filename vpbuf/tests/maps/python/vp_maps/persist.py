# Software released under the MIT license (see project root for license file)

class Header():
    def __init__(self):
        self.version = 1
        self.test_name = "not set"

# ------------------------------------------------------------------------------

class Base:
     def __init__(self):
        pass

class Derived1(Base):
    def __init__(self, i1 = 7, s2 = "Derived2"):
        self.i1 = i1
        self.s1 = s2

class Derived2(Base):
    def __init__(self, i1 = 9, s2 = "Derived2"):
        self.i1 = i1
        self.s1 = s2

class OuterG:
    def __init__(self):
        self.v = []

# ------------------------------------------------------------------------------

class A:
    def __init__(self, i = 0, s = "not set"):
        self.i1 = i
        self.s1 = s

class OuterA:
    def __init__(self):
        self.lookup = {}

class OuterB:
    def __init__(self):
        self.lookup = {}

class OuterC:
    def __init__(self):
        self.lookup = {}

class D1:
    def __init__(self, i = 0, s = "not set"):
        self.apod = A(i + 5, 'apod' + s)
        self.i = i
        self.s = s
        self.aref = A(i - 5, 'aref' + s)

class OuterD:
    def __init__(self):
        self.lookup = {}

# ------------------------------------------------------------------------------

class IdentityScrambler:
    def __init__(self, base_arr = [], seed = 1):
        self.base_arr = base_arr

    def __call__(self):
        return self.base_arr

class EggScrambler:
    def __init__(self, base_arr = [], seed = 1):
        self.base_arr = base_arr
        self.seed = seed

    def __call__(self):
        # simple shuffle via two primes
        tmp = list(self.base_arr)
        j = len(tmp) - 1

        while (j > 0):
            self.seed = (self.seed * 61) % 233
            i = self.seed % j

#            print(self.seed, i, j)

            tmp[i], tmp[j] = tmp[j], tmp[i]
            j-=1

#        print(tmp)

        return tmp

# ------------------------------------------------------------------------------

class SaltShaker:
    def __init__(self, seed = 1):
        self.seed = seed

    def __call__(self):
        self.seed = (self.seed * 53) % 113
        return "SALT-" + str(self.seed)

class PepperShaker:
    def __init__(self, seed = 1):
        self.seed = seed

    def __call__(self):
        self.seed = (self.seed * 47) % 199
        return "PEPPER-" + str(self.seed)

# ------------------------------------------------------------------------------
