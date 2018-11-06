using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NEAT_Interface
{
    public class Genome : IDisposable
    {
        readonly int _ID;
        readonly int _InputCount;
        readonly int _OutputCount;
        readonly int _LTMemoryCount;
        readonly int _STMemoryCount;
        public int ID
        {
            get
            {
                return _ID;
            }
        }
        public int InputCount
        {
            get
            {
                return _InputCount;
            }
        }
        public int OutputCount
        {
            get
            {
                return _OutputCount;
            }
        }
        public int LTMemoryCount
        {
            get
            {
                return _LTMemoryCount;
            }
        }
        public int STMemoryCount
        {
            get
            {
                return _STMemoryCount;
            }
        }
        private Genome(int id, int inputcount, int outputcount, int ltmemorycount, int stmemorycount)
        {
            _ID = id;
            _InputCount = inputcount;
            _OutputCount = outputcount;
            _LTMemoryCount = ltmemorycount;
            _STMemoryCount = stmemorycount;
        }
        public static bool CreateNewGenome(int inputcount, int outputcount, int ltmemorycount, int stmemorycount, out Genome genome)
        {
            int id = Interface.CreateNewGenome(inputcount, outputcount, ltmemorycount, stmemorycount);
            if (id > -1)
            {
                genome = new Genome(id, inputcount, outputcount, ltmemorycount, stmemorycount);
                return true;
            }
            genome = null;
            return false;
        }
        public Genome CloneGenome()
        {
            int cloneid = Interface.CloneGenome(_ID);
            return new Genome(cloneid, _InputCount, _OutputCount, _LTMemoryCount, _STMemoryCount);
        }
        public static bool CreateNewGenomeWithID(int inputcount, int outputcount, int ltmemorycount, int stmemorycount, int genomeid, out Genome genome)
        {
            int id = Interface.CreateNewGenomeWithID(inputcount, outputcount, ltmemorycount, stmemorycount, genomeid);
            if (id > -1)
            {
                genome = new Genome(id,inputcount, outputcount, ltmemorycount, stmemorycount);
                return true;
            }
            genome = null;
            return false;
        }
        public static bool CloneGenomeWithID(Genome parent, int newgenomeid, out Genome clonegenome)
        {
            int cloneid = Interface.CloneGenomeWithID(parent.ID, newgenomeid);
            if (cloneid > -1)
            {
                clonegenome = new Genome(cloneid, parent.InputCount, parent.OutputCount, parent.LTMemoryCount, parent.STMemoryCount);
                return true;
            }
            clonegenome = null;
            return false;
        }
        public void SaveGenome(string filepath)
        {
            Interface.SaveGenome(ID, filepath);
        }
        public static bool ParseGenome(string filepath, out Genome genome)
        {
            int parseid = Interface.ParseGenome(filepath);
            if (parseid > -1)
            {
                genome = new Genome(parseid, Interface.InputCount(parseid), Interface.OutputCount(parseid), Interface.LTMemoryCount(parseid), Interface.STMemoryCount(parseid));
                return true;
            }
            genome = null;
            return false;
        }
        public void Dispose()
        {
            Interface.RemoveGenome(ID);
        }
        public double[] GetOutputDynamic(params double[] inputs)
        {
            if (inputs.Length != InputCount)
            {
                return new double[OutputCount];
            }
            return GetOutput(inputs);
        }
        public double[] GetOutput(double[] inputs)
        {
            Interface.ResetMemory(ID);
            double[] outputarray = new double[OutputCount];
            for (int i = 0; i < OutputCount; i++)
            {
                outputarray[i] = Interface.GetOutputFromGenome(ID, InputCount, inputs, i);
            }
            return outputarray;
        }
        public void Mutate(int iterations)
        {
            Interface.Mutate(ID, iterations);
        }
        public void RemoveNode(int intermediateindex)
        {
            Interface.RemoveNode(ID, intermediateindex);
        }
        public void CreateNode(int previousNode, int nextNode)
        {
            Interface.CreateNode(ID, previousNode, nextNode);
        }
        public void CreateLink(int source, int destination, double weight)
        {
            Interface.CreateLink(ID, source, destination, weight);
        }
        public void AlterLinkWeight(int source, int destination, double weight)
        {
            Interface.AlterLinkWeight(ID, source, destination, weight);
        }
        public void RemoveLink(int source, int destination)
        {
            Interface.RemoveLink(ID, source, destination);
        }

        public void CreateIntermediateNode(int inputNode, int outputNode)
        {
            Interface.CreateIntermediateNode(ID, inputNode, outputNode);
        }

        public int NodeCount()
        {
            return Interface.NodeCount(ID);
        }
    }
}