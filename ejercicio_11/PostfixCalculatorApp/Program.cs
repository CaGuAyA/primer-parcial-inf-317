using System;
using CalculatorLibrary;

namespace PostfixCalculatorApp
{
    class Program
    {
        static void Main(string[] args)
        {
            PostfixCalculator calculator = new PostfixCalculator();

            while (true)
            {
                Console.WriteLine("Ingrese la expresión postfija (separada por espacios):");
                string expression = Console.ReadLine();

                if (string.IsNullOrWhiteSpace(expression))
                {
                    Console.WriteLine("Saliendo del programa...");
                    break;
                }

                try
                {
                    double result = calculator.EvaluatePostfixExpression(expression);
                    Console.WriteLine($"El resultado es: {result}");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error: {ex.Message}");
                }

                Console.WriteLine("Presione Enter para continuar o escriba 'exit' para salir.");
                string input = Console.ReadLine();
                if (input.Equals("exit", StringComparison.OrdinalIgnoreCase))
                {
                    break;
                }
            }
        }
    }
}
