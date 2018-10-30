using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NEAT_Interface;

namespace NEAT_ZDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(Interface.DLLExistsLocally());
            Console.ReadKey();
        }
    }
}