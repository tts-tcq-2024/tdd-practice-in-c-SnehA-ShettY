using System;
using System.Linq;

public class StringCalculator
{
    public int Add(string input)
    {
        if (string.IsNullOrEmpty(input))
        {
            return 0;
        }

        string updatedInput = FindDelimiter(input);

        // Find and sum up the numbers
        int sum = FindSum(updatedInput);

        // Check for negative numbers
        FindNegatives(updatedInput);

        return sum;
    }

    private string ReplaceWithCommas(string input, string delimiter)
    {
        string numbersStr = input;
        numbersStr = new string(numbersStr.Select(c => (c == '\n' || delimiter.Contains(c)) ? ',' : c).ToArray());
        return numbersStr;
    }

    private string FindDelimiter(string input)
    {
        string delimiter = ",";
        string numbersStr = input;

        if (input.StartsWith("//"))
        {
            int delimiterPos = input.IndexOf('\n');
            if (delimiterPos != -1)
            {
                delimiter = input.Substring(2, delimiterPos - 2);
                numbersStr = input.Substring(delimiterPos + 1);
            }
        }

        return ReplaceWithCommas(numbersStr, delimiter);
    }

    private void FindNegatives(string updatedInput)
    {
        var segments = updatedInput.Split(',');

        var negativeNumbers = segments
            .Where(segment => int.Parse(segment) < 0)
            .Select(int.Parse)
            .ToList();

        if (negativeNumbers.Any())
        {
            throw new InvalidOperationException("negatives not allowed: " + string.Join(", ", negativeNumbers));
        }
    }

    private int FindSum(string updatedInput)
    {
        var segments = updatedInput.Split(',');
        int sum = 0;

        foreach (var segment in segments)
        {
            int number = int.Parse(segment);
            if (number <= 1000)
            {
                sum += number;
            }
        }

        return sum;
    }
}
