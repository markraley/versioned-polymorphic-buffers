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
    def __init__(self, i = 0, s = ""):
        self.i1 = i
        self.s1 = s

class OuterA:
    def __init__(self):
        self.v = []

class OuterB:
    def __init__(self):
        self.v = []

class OuterC:
    def __init__(self):
        self.v = []

class OuterD:
    def __init__(self):
        self.v = []

class OuterE:
    def __init__(self):
        self.v = []

class OuterF:
    def __init__(self):
        self.v = []