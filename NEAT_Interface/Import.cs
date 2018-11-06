using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace NEAT_Interface
{
    internal static class Import
    {
        internal const string dllname = "NEAT_C++";

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int TestDLL();

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool GenomeExists(int id);

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int CreateNewGenome(int inputcount, int outputcount, int ltmemorycount, int stmemorycount);

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int CloneGenome(int genomeid);

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int CreateNewGenomeWithID(int inputcount, int outputcount, int ltmemorycount, int stmemorycount, int genomeid);

        [DllImport(dllname,CallingConvention=CallingConvention.Cdecl)]
        internal static extern int CloneGenomeWithID(int genomeid, int newgenomeid);

        [DllImport(dllname,CallingConvention=CallingConvention.Cdecl)]
        internal static extern void SaveGenome(int id, string filepath);

        [DllImport(dllname,CallingConvention=CallingConvention.Cdecl)]
        internal static extern int ParseGenome(string filepath);

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void RemoveGenome(int id);

        [DllImport(dllname,CallingConvention = CallingConvention.Cdecl)]
        internal static extern double GetOutputFromGenome(int genome, int inputcount, double[] inputs, int outputnum);

        [DllImport(dllname,CallingConvention=CallingConvention.Cdecl)]
        internal static extern void ResetMemory(int genomeid);

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void Mutate(int genomeid, int iterations);

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void RemoveNode(int genomeid, int intermediateindex);

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void CreateNode(int genomeid, int previousNode, int nextNode);

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void CreateLink(int genomeid, int source, int destination, double weight);

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void AlterLinkWeight(int genomeid, int source, int destination, double weight);

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void RemoveLink(int genomeid, int source, int destination);

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void CreateIntermediateNode(int genomeid, int inputNode, int outputNode);

        [DllImport(dllname,CallingConvention = CallingConvention.Cdecl)]
        internal static extern int InputCount(int genomeid);

        [DllImport(dllname,CallingConvention = CallingConvention.Cdecl)]
        internal static extern int OutputCount(int genomeid);

        [DllImport(dllname,CallingConvention = CallingConvention.Cdecl)]
        internal static extern int LTMemoryCount(int genomeid);

        [DllImport(dllname,CallingConvention = CallingConvention.Cdecl)]
        internal static extern int STMemoryCount(int genomeid);

        [DllImport(dllname, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int NodeCount(int genomeid);
    }

    public static class Interface
    {
        public static bool DLLExistsLocally()
        {
            bool output = File.Exists(Import.dllname + ".dll");
            if (!output)
            {
                Output.GenerateOutput("{0}.dll doesn't exist, what the hell are you?", Import.dllname);
                return false;
            }
            try
            {
                int val = Import.TestDLL();
                return val == 5;
            }
            catch (Exception err)
            {
                Output.GenerateOutput(err.Message);
                return false;
            }
        }

        public static bool GenomeExists(int id)
        {
            if (DLLExistsLocally())
            {
                return Import.GenomeExists(id);
            }
            return false;
        }

        public static int CreateNewGenome(int inputcount, int outputcount, int ltmemorycount, int stmemorycount)
        {
            if (DLLExistsLocally())
            {
                return Import.CreateNewGenome(inputcount, outputcount, ltmemorycount, stmemorycount);
            }
            return -1;
        }

        public static int CloneGenome(int genomeid)
        {
            if (DLLExistsLocally())
            {
                return Import.CloneGenome(genomeid);
            }
            return -1;
        }

        public static int CreateNewGenomeWithID(int inputcount, int outputcount, int ltmemorycount, int stmemorycount, int genomeid)
        {
            if (DLLExistsLocally())
            {
                return Import.CreateNewGenomeWithID(inputcount, outputcount, ltmemorycount, stmemorycount, genomeid);
            }
            return -1;
        }

        public static int CloneGenomeWithID(int genomeid, int newgenomeid)
        {
            if (DLLExistsLocally())
            {
                return Import.CloneGenomeWithID(genomeid, newgenomeid);
            }
            return -1;
        }

        public static void SaveGenome(int id, string filepath)
        {
            if (DLLExistsLocally())
            {
                Import.SaveGenome(id, filepath);
            }
        }

        public static int ParseGenome(string filepath)
        {
            if (DLLExistsLocally())
            {
                return Import.ParseGenome(filepath);
            }
            return -1;
        }

        public static void RemoveGenome(int id)
        {
            if (DLLExistsLocally())
            {
                Import.RemoveGenome(id);
            }
        }

        public static double GetOutputFromGenome(int genome, int inputcount, double[] inputs, int outputnum)
        {
            if (DLLExistsLocally())
            {
                return Import.GetOutputFromGenome(genome, inputcount, inputs, outputnum);
            }
            return -1d;
        }

        public static void ResetMemory(int genomeid)
        {
            if (DLLExistsLocally())
            {
                Import.ResetMemory(genomeid);
            }
        }

        public static void Mutate(int genomeid, int iterations)
        {
            if (DLLExistsLocally())
            {
                Import.Mutate(genomeid, iterations);
            }
        }

        public static void RemoveNode(int genomeid, int intermediateindex)
        {
            if (DLLExistsLocally())
            {
                Import.RemoveNode(genomeid, intermediateindex);
            }
        }

        public static void CreateNode(int genomeid, int previousNode, int nextNode)
        {
            if (DLLExistsLocally())
            {
                Import.CreateNode(genomeid, previousNode, nextNode);
            }
        }

        public static void CreateLink(int genomeid, int source, int destination, double weight)
        {
            if (DLLExistsLocally())
            {
                Import.CreateLink(genomeid, source, destination, weight);
            }
        }

        public static void AlterLinkWeight(int genomeid, int source, int destination, double weight)
        {
            if (DLLExistsLocally())
            {
                Import.AlterLinkWeight(genomeid, source, destination, weight);
            }
        }

        public static void RemoveLink(int genomeid, int source, int destination)
        {
            if (DLLExistsLocally())
            {
                Import.RemoveLink(genomeid, source, destination);
            }
        }
        
        public static void CreateIntermediateNode(int genomeid, int inputNode, int outputNode)
        {
            if (DLLExistsLocally())
            {
                Import.CreateIntermediateNode(genomeid, inputNode, outputNode);
            }
        }

        public static int InputCount(int genomeid)
        {
            if (DLLExistsLocally())
            {
                return Import.InputCount(genomeid);
            }
            return -1;
        }

        public static int OutputCount(int genomeid)
        {
            if (DLLExistsLocally())
            {
                return Import.OutputCount(genomeid);
            }
            return -1;
        }

        public static int LTMemoryCount(int genomeid)
        {
            if (DLLExistsLocally())
            {
                return Import.LTMemoryCount(genomeid);
            }
            return -1;
        }

        public static int STMemoryCount(int genomeid)
        {
            if (DLLExistsLocally())
            {
                return Import.STMemoryCount(genomeid);
            }
            return -1;
        }

        public static int NodeCount(int genomeid)
        {
            if (DLLExistsLocally())
            {
                return Import.NodeCount(genomeid);
            }
            return -1;
        }
    }
}