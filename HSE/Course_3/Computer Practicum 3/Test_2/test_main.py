# test_main.py
import unittest
from main import add


class TestAddFunction(unittest.TestCase):

    def test_add_positive_numbers(self):
        result = add(1, 2)
        self.assertEqual(result, 3)
        print(f"test_add_positive_numbers: {result} == 3")

    def test_add_negative_numbers(self):
        result = add(-1, -1)
        self.assertEqual(result, -2)
        print(f"test_add_negative_numbers: {result} == -2")

    def test_add_mixed_numbers(self):
        result = add(-1, 1)
        self.assertEqual(result, 0)
        print(f"test_add_mixed_numbers: {result} == 0")

    def test_add_zero(self):
        result = add(0, 0)
        self.assertEqual(result, 0)
        print(f"test_add_zero: {result} == 0")


if __name__ == '__main__':
    unittest.main()
