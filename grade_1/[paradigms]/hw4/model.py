import sys
from io import StringIO


class Scope:
    def __init__(self, parent=None):
        self.parent = parent
        self.dc = {}

    def __getitem__(self, key):
        if key in self.dc:
            return self.dc[key]
        if self.parent:
            return self.parent[key]
        raise NoSuchElement

    def __setitem__(self, key, val):
        self.dc[key] = val


class Number:
    def __init__(self, val):
        self.val = val

    def evaluate(self, scope):
        return self

    def __eq__(self, other):
        return Number(int(self.val is other.val))

    def __ne__(self, other):
        return Number(int(self.val is not other.val))

    def __hash__(self):
        return self.val


class Function:
    def __init__(self, args, body):
        self.args = args
        self.body = body

    def evaluate(self, scope):
        return self


class FunctionDefinition:
    def __init__(self, name, function):
        self.name = name
        self.function = function

    def evaluate(self, scope):
        scope[self.name] = self.function
        return scope[self.name]


class Conditional:
    def __init__(self, condition, if_true, if_false=None):
        self.condition = condition
        self.if_true = if_true
        self.if_false = if_false

    def evaluate_array(self, array, scope):
        if not array:
            return Number(0)
        res = Number(0)
        for item in array:
            a = item.evaluate(scope)
        return a

    def evaluate(self, scope):
        if not self.condition.evaluate(scope).val:
            return self.evaluate_array(self.if_false, scope)
        else:
            return self.evaluate_array(self.if_true, scope)


class Print:
    def __init__(self, expr):
        self.expr = expr

    def evaluate(self, scope):
        val = self.expr.evaluate(scope)
        print(val.val)
        return val


class Read:
    def __init__(self, name):
        self.name = name

    def evaluate(self, scope):
        val = Number(int(input()))
        scope[self.name] = val
        return val


class FunctionCall:
    def __init__(self, fun_expr, args):
        self.fun_expr = fun_expr
        self.args = args

    def evaluate(self, scope):
        function = self.fun_expr.evaluate(scope)
        new_scope = Scope(scope)
        for i in range(len(function.args)):
            new_scope[function.args[i]] = self.args[i].evaluate(scope)
        res = Number(0)
        for i in function.body:
            res = i.evaluate(new_scope)
        return res


class Reference:
    def __init__(self, name):
        self.name = name

    def evaluate(self, scope):
        return scope[self.name]


class BinaryOperation:
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

    def __init__(self, lhs, op, rhs):
        self.lhs = lhs
        self.op = op
        self.rhs = rhs

    def evaluate(self, scope):
        a = self.lhs.evaluate(scope).val
        b = self.rhs.evaluate(scope).val
        return Number(self.ops[self.op](a, b))


class UnaryOperation:
    ops = {
        '!': lambda a: not a,
        '-': lambda a: -a
    }

    def __init__(self, op, expr):
        self.op = op
        self.expr = expr

    def evaluate(self, scope):
        return Number(self.ops[self.op](self.expr.evaluate(scope).val))


def unary_op_tests():
    scope = Scope()
    assert UnaryOperation('-', Number(1)).evaluate(scope) == Number(-1)
    assert UnaryOperation('!', Number(1)).evaluate(scope) == Number(0)


def binary_op_tests():
    scope = Scope()
    assert BinaryOperation(Number(1), '+',
                           Number(1)).evaluate(scope) == Number(2)
    assert BinaryOperation(Number(1), '-',
                           Number(1)).evaluate(scope) == Number(0)
    assert BinaryOperation(Number(1), '*',
                           Number(-1)).evaluate(scope) == Number(-1)
    assert BinaryOperation(Number(1), '/',
                           Number(2)).evaluate(scope) == Number(0)
    assert BinaryOperation(Number(10), '%',
                           Number(3)).evaluate(scope) == Number(1)
    assert BinaryOperation(Number(7), '&&',
                           Number(9)).evaluate(scope) == Number(1)
    assert BinaryOperation(Number(7), '||',
                           Number(9)).evaluate(scope) == Number(15)
    assert BinaryOperation(Number(7), '<',
                           Number(9)).evaluate(scope) == Number(1)
    assert BinaryOperation(Number(7), '<=',
                           Number(9)).evaluate(scope) == Number(1)
    assert BinaryOperation(Number(7), '>',
                           Number(9)).evaluate(scope) == Number(0)
    assert BinaryOperation(Number(7), '==',
                           Number(9)).evaluate(scope) == Number(0)
    assert BinaryOperation(Number(7), '!=',
                           Number(9)).evaluate(scope) == Number(1)


def conditional_tests():
    scope = Scope()
    fr = Conditional(Number(1), [Number(1)], [Number(0)]).evaluate(scope)
    sc = Conditional(Number(0), [Number(1)], [Number(0)]).evaluate(scope)
    assert fr == Number(1) and sc == Number(0)


def function_tests():
    scope = Scope()
    func = Function(['x'], [BinaryOperation(Reference('x'), '+', Number(1))])
    FunctionDefinition('inc', func).evaluate(scope)
    assert FunctionCall(Reference('inc'),
                        [Number(0)]).evaluate(scope) == Number(1)


def io_tests():
    scope = Scope()
    backup_in = sys.stdin
    backup_out = sys.stdout
    inp = '1\n2\n'
    sys.stdin = StringIO(inp)
    sys.stdout = StringIO()

    Read('a').evaluate(scope)
    Read('b').evaluate(scope)
    Print(Number(BinaryOperation(Reference('a'), '+', Reference('b'))
                 .evaluate(scope).val)).evaluate(scope)
    assert sys.stdout.getvalue() == '3\n'

    sys.stdout = backup_out
    sys.stdin = backup_in


def do_tests():
    unary_op_tests()
    binary_op_tests()
    conditional_tests()
    function_tests()
    io_tests()


if __name__ == '__main__':
    do_tests()
