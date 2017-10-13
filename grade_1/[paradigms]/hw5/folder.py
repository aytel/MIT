from yat.model import *


class ConstantFolder:
    def visit(self, tree):
        ret = tree.accept(self)
        return ret

    def visit_num(self, num):
        return num

    def visit_ref(self, ref):
        return ref

    def visit_bin(self, bin_op):
        ops = {
            '+': lambda a, b: a + b,
            '-': lambda a, b: a - b,
            '*': lambda a, b: a * b,
            '/': lambda a, b: a // b,
            '%': lambda a, b: a % b,
            '==': lambda a, b: a == b,
            '!=': lambda a, b: a != b,
            '<': lambda a, b: a < b,
            '>': lambda a, b: a > b,
            '<=': lambda a, b: a <= b,
            '>=': lambda a, b: a >= b,
            '&&': lambda a, b: a and b,
            '||': lambda a, b: a or b
        }

        bin_op.lhs = self.visit(bin_op.lhs)
        bin_op.rhs = self.visit(bin_op.rhs)
        if isinstance(bin_op.lhs, Number) and isinstance(bin_op.rhs, Number):
            return Number(ops[bin_op.op](bin_op.lhs.val,
                                         bin_op.rhs.val))
        if isinstance(bin_op.lhs,
                      Number) and isinstance(bin_op.rhs,
                                             Reference) and not bin_op.lhs.val:
            return Number(0)
        if isinstance(bin_op.rhs,
                      Number) and isinstance(bin_op.lhs,
                                             Reference) and not bin_op.rhs.val:
            return Number(0)
        if bin_op.op == '-' and isinstance(
            bin_op.rhs, Reference) and isinstance(
                bin_op.lhs, Reference) and bin_op.lhs.name == bin_op.rhs.name:
            return Number(0)

    def visit_un(self, un_op):
        ops = {
            '!': lambda a: not a,
            '-': lambda a: -a
        }

        un_op.expr = self.visit(un_op.expr)
        if isinstance(un_op.expr, Number):
            return Number(ops[un_op.op](un_op.expr.val))

    def visit_call(self, call):
        call.fun_expr = self.visit(call.fun_expr)
        args = call.args
        for arg in args:
            arg = self.visit(arg)
        return call

    def visit_cond(self, cond):
        cond.condition = self.visit(cond.condition)
        for expr in cond.if_true:
            expr = self.visit(expr)
        for expr in cond.if_false:
            expr = self.visit(expr)
        return cond

    def visit_def(self, fdef):
        args = fdef.function.args
        for expr in fdef.function.body:
            expr = self.visit(expr)
        return fdef

    def visit_print(self, print_exp):
        print_exp.expr = self.visit(print_exp.expr)
        return print_expr

    def visit_read(self, read_exp):
        return read_exp


def tests():
    folder = ConstantFolder()

    assert(folder.visit(BinaryOperation(
        Number(42),
        '*',
        Number(10))) == Number(420))
    assert(folder.visit(UnaryOperation(
        '-',
        Number(42))) == Number(-42))
    assert(folder.visit(BinaryOperation(
        Number(0),
        '*',
        Reference('name'))) == Number(0))
    assert(folder.visit(BinaryOperation(
        Reference('name'),
        '*',
        Number(0))) == Number(0))
    assert(folder.visit(BinaryOperation(
        Reference('name'),
        '-',
        Reference('name'))) == Number(0))

if __name__ == '__main__':
    tests()
