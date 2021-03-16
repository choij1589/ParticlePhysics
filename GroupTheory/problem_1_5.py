from sympy import *
init_printing(use_unicode=True)

# Define constants and transformation
sig_0 = Matrix([[1, 0], [0, 1]])
sig_1 = Matrix([[0, 1], [1, 0]])
sig_2 = Matrix([[0, -I], [I, 0]])
sig_3 = Matrix([[1, 0], [0, -1]])
Pauli = [sig_0, sig_1, sig_2, sig_3]
metric = diag(-1, 1, 1, 1)

a, b, c = symbols('a b c'); d = (1+b*c)/a
L = Matrix([[a, b], [c, d]])
L_dag = conjugate(L).T
def comp(mu, nu):       # component of lambda
    return Rational(1, 2)*Trace(Pauli[mu]*L*Pauli[nu]*L_dag).simplify()

Lambda = Matrix([[comp(0, 0), comp(0, 1), comp(0, 2), comp(0, 3)],
                 [comp(1, 0), comp(1, 1), comp(1, 2), comp(1, 3)],
                 [comp(2, 0), comp(2, 1), comp(2, 2), comp(2, 3)],
                 [comp(3, 0), comp(3, 1), comp(3, 2), comp(3, 3)]])

# problem 1
test_metric = (Lambda.T)*metric*Lambda
print("Problem 1:")
print(simplify(test_metric))
print()

# problem 2
# by hand
print("Problem 2:")
print("solved by hand\n")

# problem 3
print("Problem 3:")
print(simplify(Lambda.det()))
print()

# problem 4
a1, b1, c1 = symbols('a1 b1 c1'); d1 = (1+b1*c1)/a1
a2, b2, c2 = symbols('a2 b2 c2'); d2 = (1+b2*c2)/a2
L1 = Matrix([[a1, b1], [c1, d1]]); L1_dag = conjugate(L1).T
L2 = Matrix([[a2, b2], [c2, d2]]); L2_dag = conjugate(L2).T
def comp_L1(mu, nu):
    return Rational(1, 2)*Trace(Pauli[mu]*L1*Pauli[nu]*L1_dag).simplify()
def comp_L2(mu, nu):
    return Rational(1, 2)*Trace(Pauli[mu]*L2*Pauli[nu]*L2_dag).simplify()
def comp_L1L2(mu, nu):
    return Rational(1, 2)*Trace(Pauli[mu]*(L1*L2)*Pauli[nu]*conjugate(L1*L2).T).simplify()

Lambda1 = Matrix([[comp_L1(0, 0), comp_L1(0, 1), comp_L1(0, 2), comp_L1(0, 3)],
                  [comp_L1(1, 0), comp_L1(1, 1), comp_L1(1, 2), comp_L1(1, 3)],
                  [comp_L1(2, 0), comp_L1(2, 1), comp_L1(2, 2), comp_L1(2, 3)],
                  [comp_L1(3, 0), comp_L1(3, 1), comp_L1(3, 2), comp_L1(3, 3)]])
Lambda2 = Matrix([[comp_L2(0, 0), comp_L2(0, 1), comp_L2(0, 2), comp_L2(0, 3)],
                  [comp_L2(1, 0), comp_L2(1, 1), comp_L2(1, 2), comp_L2(1, 3)],
                  [comp_L2(2, 0), comp_L2(2, 1), comp_L2(2, 2), comp_L2(2, 3)],
                  [comp_L2(3, 0), comp_L2(3, 1), comp_L2(3, 2), comp_L2(3, 3)]])
Lambda12 = Matrix([[comp_L1L2(0, 0), comp_L1L2(0, 1), comp_L1L2(0, 2), comp_L1L2(0, 3)],
                  [comp_L1L2(1, 0), comp_L1L2(1, 1), comp_L1L2(1, 2), comp_L1L2(1, 3)],
                  [comp_L1L2(2, 0), comp_L1L2(2, 1), comp_L1L2(2, 2), comp_L1L2(2, 3)],
                  [comp_L1L2(3, 0), comp_L1L2(3, 1), comp_L1L2(3, 2), comp_L1L2(3, 3)]])

lhs = simplify(Lambda1*Lambda2)
rhs = simplify(Lambda12)
print("Problem 4:")
print(simplify(lhs-rhs))





