from yat.model import *
from io import StringIO


class PrettyPrinter:
    def __init__(self):
        self.stat = 1
        self.ind = ''

    def visit(self, tree):
        ret = tree.accept(self)
        if self.stat:
            print(';')
        return ret

    def visit_num(self, num):
        print(self.ind, num.val, end='', sep='')

    def visit_ref(self, ref):
        print(self.ind, ref.name, end='', sep='')

    def visit_bin(self, bin_op):
        print(self.ind+'(', end='')

        spr = self.stat
        self.stat = 0
        pr = self.ind
        self.ind = ''

        self.visit(bin_op.lhs)
        print(bin_op.op, end='')
        self.visit(bin_op.rhs)
        print(')', end='')

        self.ind = pr
        self.stat = spr

    def visit_un(self, un_op):
        print(self.ind+'(', end='')
        print(un_op.op, end='')

        spr = self.stat
        self.stat = 0
        pr = self.ind
        self.ind = ''

        self.visit(un_op.expr)
        print(')', end='')

        self.ind = pr
        self.stat = spr

    def visit_call(self, call):
        spr = self.stat
        self.stat = 0

        self.visit(call.fun_expr)
        print('(', end='')
        args = call.args

        pr = self.ind
        self.ind = ''

        for i in range(len(args)):
            self.visit(args[i])
            if i+1 != len(args):
                print(', ', end='')
        print(')', end='')

        self.ind = pr
        self.stat = spr

    def visit_cond(self, cond):
        print(self.ind+'if (', end='')

        spr = self.stat
        self.stat = 0
        pr = self.ind
        self.ind = ''

        self.visit(cond.condition)

        self.ind = pr
        self.stat = spr

        print(') {')
        self.ind += '    '
        for expr in cond.if_true:
            self.visit(expr)
        print(self.ind[:len(self.ind)-4]+'} else {')
        for expr in cond.if_false:
            self.visit(expr)
        self.ind = self.ind[:len(self.ind)-4]
        print(self.ind+'}', end='')

    def visit_def(self, fdef):
        print(self.ind+'def '+fdef.name+'(', end='')
        args = fdef.function.args
        for i in range(len(args)):
            print(args[i], end='')
            if i+1 != len(args):
                print(', ', end='')
        print(') {')
        self.ind += '    '
        for expr in fdef.function.body:
            self.visit(expr)
        self.ind = self.ind[:len(self.ind)-4]
        print(self.ind+'}', end='')

    def visit_print(self, print_exp):
        print(self.ind+'print ', end='')

        spr = self.stat
        self.stat = 0
        pr = self.ind
        self.ind = ''

        self.visit(print_exp.expr)

        self.ind = pr
        self.stat = spr

    def visit_read(self, read_exp):
        print(self.ind+'read '+read_exp.name, end='')


def io_tests():
    backup_out = sys.stdout
    printer = PrettyPrinter()

    sys.stdout = StringIO()
    printer.visit(Print(Number(42)))
    assert(sys.stdout.getvalue() == 'print 42;\n')

    sys.stdout = StringIO()
    printer.visit(Read('name'))
    assert(sys.stdout.getvalue() == 'read name;\n')

    sys.stdout = backup_out


def function_tests():
    backup_out = sys.stdout
    printer = PrettyPrinter()

    sys.stdout = StringIO()
    printer.visit(FunctionDefinition('foo',
                                     Function(['a', 'b'],
                                              [BinaryOperation(
                                                  Reference('a'),
                                                  '+',
                                                  Reference('b'))])))
    assert (sys.stdout.getvalue() == 'def foo(a, b) {\n    (a+b);\n};\n')

    sys.stdout = StringIO()
    printer.visit(FunctionCall(
        Reference('foo'),
        [Reference('a'),
         Number(3)]))
    assert(sys.stdout.getvalue() == 'foo(a, 3);\n')

    sys.stdout = backup_out


def condition_tests():
    backup_out = sys.stdout
    printer = PrettyPrinter()

    sys.stdout = StringIO()
    printer.visit(Conditional(
        Number(-1),
        [UnaryOperation('-', Number(10))],
        [BinaryOperation(Number(3), '&&', Number(7))]))
    assert (sys.stdout.getvalue() == '''if (-1) {\n    (-10);\n} else {
    (3&&7);\n};\n''')

    sys.stdout = backup_out


def tests():
    io_tests()
    function_tests()
    condition_tests()

if __name__ == '__main__':
    tests()
