using System;
using System.Collections.Generic;

namespace CalculatorLibrary
{
    public class PostfixCalculator
    {
        public double EvaluatePostfixExpression(string expression)
        {
            Stack<double> stack = new Stack<double>();
            string[] tokens = expression.Split(' ');

            foreach (string token in tokens)
            {
                if (double.TryParse(token, out double number))
                {
                    stack.Push(number);
                }
                else
                {
                    double operand2 = stack.Pop();
                    double operand1 = stack.Pop();
                    double result = PerformOperation(token, operand1, operand2);
                    stack.Push(result);
                }
            }

            return stack.Pop();
        }

        private double PerformOperation(string operation, double operand1, double operand2)
        {
            if (operation == "+")
            {
                return operand1 + operand2;
            }
            else if (operation == "-")
            {
                return operand1 - operand2;
            }
            else if (operation == "*")
            {
                return operand1 * operand2;
            }
            else if (operation == "/")
            {
                return operand1 / operand2;
            }
            else
            {
                throw new InvalidOperationException("Operación no válida");
            }
        }
    }
}
