using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NEAT_Interface
{
    public delegate void GenericOutput(string format, params object[] args);
    public static class Output
    {
        static GenericOutput genericOutput = Console.WriteLine;
        public static void SetGenericOutput(GenericOutput go)
        {
            if (go != null)
            {
                genericOutput = go;
            }
            else
            {
                GenerateOutput("Attempted to set the output method to null. CANNOT BE DONE! YOU ARE A DISGRACE IN THE NAME OF GORD!");
            }
        }
        public static void GenerateOutput(string format, params object[] args)
        {
            GenerateOutput(format, false, args);
            //genericOutput(format, args);
        }
        public static void GenerateOutput(string text)
        {
            GenerateOutput(text, new object[0]);
        }
        public static void GenerateOutput(string format, bool stacktrace, params object[] args)
        {
            format = stacktrace ? format + "\n\n" + Environment.StackTrace : format;
            genericOutput(format, args);
        }
    }
}
