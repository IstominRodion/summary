using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace лр_1
{
    class Program
    {
        static string[] Split(string s)
        {
            string[] arr = new string[100]; //массив для хранения элементов
            int p = 0;
            for (int i = 0; i < s.Length; i++)  //разбиение на отдельные элементы
            {
                if (s[i] == '!')
                {
                    arr[p] += "!";
                }
                else arr[p++] += s[i];
            }
            Array.Resize(ref arr, p);
            return arr;
        }

        static string[] Distr(string[] s1, string[] s2)     //реализация дистрибутивного закона (дз)
        {
            string[] res = new string[s1.Length * s2.Length];  //массив для результатов применения дз
            int p = 0;
            for (int i = 0; i < s1.Length; i++)         //получение результатов
            {
                for (int j = 0; j < s2.Length; j++)
                {
                    if ( (s1[i] != s2[j]) && s1[i] != ("!" + s2[j]) && s2[j] != ("!" + s1[i]) )   //добавление в массив-результат только разных элементов,
                        res[p++] = s1[i] + s2[j];                                                   //не образующих 0 или 1 и исключение повторяющихся
                    if (s1[i] == s2[j])
                        res[p++] = s1[i];
                }
            }
            Array.Resize(ref res, p);
            return res;         //функция возвращает массив строк, полученных после выполнения дз, строки не содержат знаков операций 
        }

        static void Main(string[] args)
        {
            bool repeat = true; //переменная для повтора программы
            while (repeat) {
                bool f = false;     //переменная для повтора введения переменных
                int n = 0;      //количество элементов в результате
                string buf, m = "";     //промежуточная строка для преобразований и внешняя операция

                do      //ввод n и проверка по условиям
                {
                    Console.WriteLine("Введите число от 1 до 100");
                    buf = Console.ReadLine();
                    bool ok = Int32.TryParse(buf, out n);
                    if (ok && Convert.ToInt32(buf) <= 100 && Convert.ToInt32(buf) >= 1)
                    {
                        f = true;
                        n = Convert.ToInt32(buf);
                    }
                    else Console.WriteLine("Введите другое число");
                } while (!f);

                f = false;
                do      //ввод m и проверка по условиям
                {
                    Console.WriteLine("Выберите операцию 'v' или '&'");
                    buf = Console.ReadLine();
                    if (buf == "v" || buf == "&")
                    {
                        f = true;
                        m = buf;
                    }
                    else Console.WriteLine("Введите правильную операцию");
                } while (!f);

                string[] arr = new string[n];       //массив для хранения введённых элементов
                if (m == "v") Console.WriteLine("Введите конъюнкты");
                else Console.WriteLine("Введите дизъюнкты");
                for (int i = 0; i < n; i++)     //ввод элементов конъюнкций или дизъюнкций
                {
                    Console.Write((i + 1) + ") ");
                    arr[i] = Console.ReadLine();
                }

                string[][] forSplit = new string[arr.Length][];         //рваный массив для разделения входных данных на отдельные символы
                for (int i = 0; i < arr.Length; i++)
                {
                    forSplit[i] = Split(arr[i]);
                }

                for (int i = 0; i < forSplit.Length - 1; i++)       //применение дистрибутивного закона (дз) 
                {
                    string[] temp = new string[forSplit[i].Length * forSplit[i + 1].Length];        //временный массив для хранения результатов дз
                    temp = Distr(forSplit[i], forSplit[i + 1]);
                    Array.Resize(ref forSplit[i + 1], temp.Length);         //для сохранения результатов дз и последующего его выполнения с использованием ранее 
                    forSplit[i + 1] = temp;                                 //полченных результатов изменяю размерность рваного массива и сохраняю результаты в следующую
                }                                                           //ячейку массива

                Array.Resize(ref arr, forSplit[forSplit.Length - 1].Length);        //повторное использование массива для хранения конечного результата дз
                arr = forSplit[forSplit.Length - 1];
                string res = "";
                for(int i = 0; i < arr.Length; i++)         //составление строки-результата для вывода
                {
                    if (m == "v")       //выбор операции в результате
                    {
                        string[] temp = Split(arr[i]);      //т.к. данные хранились в виде строки без знаков операций необходимо её разделить и вставить знаки
                        res += "(";
                        for (int j = 0; j < temp.Length - 1; j++)
                        {
                            res += temp[j] + " v ";
                        }
                        res += temp[temp.Length - 1] + ")";
                    }
                    else
                    {
                        res += arr[i];
                        if (i!=arr.Length - 1)
                        {
                            res += " v ";
                        }
                    }
                }

                Console.WriteLine(res);

                Console.WriteLine("Запустить программу ещё раз? (введите 1 для продолжения)");      //повтор программы
                if (Console.ReadLine() != "1") repeat = false;
            }
        }
    }
}