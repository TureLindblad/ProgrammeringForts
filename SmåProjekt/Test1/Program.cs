using System.Reflection.Metadata.Ecma335;
using System.Runtime.InteropServices;

namespace Test1
{
    public enum DiceRolls
    {
        Ett, Två, Tre, Fyr, Femm, Sex
    }
    public enum GameChoices
    {
        rock, paper, scissor, secret, defaultChoice
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            //RollDice();

            //Console.WriteLine("Regnumber is: " + CheckValidRegNumber("ABC12D"));

            //Console.WriteLine("Password is: " + IsValidPassword("12BBccD34löseN2"));

            RockPaperScissor();
        }

        static void RockPaperScissor()
        {
            while (true)
            {
                Dictionary<GameChoices, GameChoices> winningPlays = new Dictionary<GameChoices, GameChoices>();
                winningPlays[GameChoices.rock] = GameChoices.scissor;
                winningPlays[GameChoices.paper] = GameChoices.rock;
                winningPlays[GameChoices.scissor] = GameChoices.paper;
                winningPlays[GameChoices.secret] = GameChoices.secret;

                Random rnd = new Random();
                GameChoices ai = (GameChoices)rnd.Next(0, 4);

                Console.WriteLine("Write your choice between rock, paper or scissor");
                string playerString = Console.ReadLine();
                GameChoices player = GameChoices.defaultChoice;

                if (playerString.ToLower() == "rock") player = GameChoices.rock;
                else if (playerString.ToLower() == "paper") player = GameChoices.paper;
                else if (playerString.ToLower() == "scissor") player = GameChoices.scissor;
                else
                {
                    Console.WriteLine("Wrong input");
                    continue;
                }

                Console.WriteLine($"AI plays {ai}");

                if (winningPlays[ai] == player || ai == GameChoices.secret)
                {
                    Console.WriteLine($"Ai won");
                }
                else if (winningPlays[player] == ai)
                {
                    Console.WriteLine($"You won");
                }
                else if (ai == player)
                {
                    Console.WriteLine($"Draw");
                }
            }
        }

        static bool IsValidPassword(string password)
        {
            bool[] checks = new bool[4];

            checks[0] = password.Length >= 8 ? true : false;
            checks[1] = NumberOfCaseChars(password, "lower") >= 2 ? true : false;
            checks[2] = NumberOfCaseChars(password, "upper") >= 2 ? true : false;
            checks[3] = CheckForInvalidSubstrings(password);

            foreach (bool check in checks)
            {
                if (!check) return false;
            }

            return true;
        }

        static bool CheckForInvalidSubstrings(string password)
        {
            string[] invalidStrings = { "hej", "lösen", "hopp" };

            foreach (string s in invalidStrings)
            {
                if (password.ToLower().Contains(s)) return false;
            }

            return true;
        }

        static int NumberOfCaseChars(string password, string key)
        {
            int counter = 0;

            for (int i = 0; i < password.Length; i++)
            {
                if (key == "upper")
                {
                    if (Char.IsUpper(password[i])) counter++;
                }
                else if (key == "lower")
                {
                    if (Char.IsLower(password[i])) counter++;
                }
                
            }

            return counter;
        }

        static bool CheckValidRegNumber(string regNum)
        {
            if (regNum.Length != 6)
            {
                return false;
            }
            else
            {
                bool[] checks = new bool[6];

                for (int i = 0; i < 3; i++)
                {
                    char.TryParse(regNum.Substring(i, 1), out char char1);
                    checks[i] = Char.IsLetter(char1);
                }
                for (int i = 3; i < 5; i++)
                {
                    checks[i] = int.TryParse(regNum.Substring(i, 1), out int int1);
                };

                char.TryParse(regNum.Substring(5, 1), out char char2);
                bool lastChar = Char.IsLetter(char2);
                bool lastInt = int.TryParse(regNum.Substring(5, 1), out int int2);

                if (lastChar || lastInt)
                {
                    checks[5] = true;
                }
                else
                {
                    checks[5] = false;
                }

                foreach (bool check in checks)
                {
                    if (!check) return false;
                }
            }

            return true;
        }

        static void RollDice()
        {
            Console.WriteLine("You roll three dice");

            int result1 = GetRandom();
            int result2 = GetRandom();
            int result3 = GetRandom();

            if (result1 == result2 && result2 == result3)
            {
                Console.WriteLine($"You rolled three {(DiceRolls)result1}or");
            }
            else if (result1 == result2)
            {
                Console.WriteLine($"You rolled two {(DiceRolls)result1}or and {(DiceRolls)result3}a");
            }
            else if (result2 == result3)
            {
                Console.WriteLine($"You rolled two {(DiceRolls)result2}or and {(DiceRolls)result1}a");
            }
            else if (result1 == result3)
            {
                Console.WriteLine($"You rolled two {(DiceRolls)result1}or and {(DiceRolls)result2}a");
            }
            else
            {
                Console.WriteLine($"You roll: {(DiceRolls)result1}a and {(DiceRolls)result2}a and {(DiceRolls)result3}a");
            }
        }

        static int GetRandom()
        {
            Random rnd = new Random();
            int roll = rnd.Next(0, 6);
            return roll;
        }
    }
}
