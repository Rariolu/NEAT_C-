using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NEAT_Interface;
using NeuralUtil;

namespace NEAT_ZDemo
{
    //static class Program
    //{
    //    static SuperRand rand = new SuperRand();
    //    const int min = 0;
    //    const int max = 200;
    //    const int inputCount = 2;
    //    const int outputCount = 3;
    //    const int ltmCount = 0;
    //    const int stmCount = 0;
    //    static void Main(string[] args)
    //    {
    //        const int testMin = 0;
    //        const int testMax = 100;
    //        Genome g;
    //        if (!Genome.CreateNewGenome(inputCount,outputCount,ltmCount,stmCount,out g))
    //        {
    //            Console.WriteLine("Error in genome creation");
    //            Console.ReadKey();
    //            return;
    //        }
    //        Console.WriteLine("Genome created");
    //        Genome h = g.CloneGenome();
    //        int hr = GetNumericalOutput(h, 1, 1);//h.GetOutputDynamic(1d.Normalise(min,max), 1d.Normalise(min,max)).Single().ReverseNormalise(min,max);
    //        Console.WriteLine("hr: {0};", hr);
    //        h.CreateIntermediateNode(rand.Next(h.InputCount), rand.Next(h.OutputCount));
    //        h.CreateIntermediateNode(rand.Next(h.InputCount), rand.Next(h.OutputCount));
    //        h.CreateIntermediateNode(rand.Next(h.InputCount), rand.Next(h.OutputCount));
    //        Console.WriteLine("NodeCount: {0};", h.NodeCount());
    //        for (int i = 0; i < 10000 && (hr == 0 || hr == 1); i++)
    //        {
    //            int nodecount = h.NodeCount();
    //            if (nodecount == 0)
    //            {
    //                Console.WriteLine("This is silly");
    //                Console.ReadKey();
    //                return;
    //            }
    //            int prev = rand.Next(nodecount);
    //            int next = rand.Next(nodecount);
    //            if (rand.NextDouble() < 0.5)
    //            {
    //                h.CreateNode(prev, next);
    //            }
    //            else
    //            {
    //                h.CreateLink(prev, next, rand.NextDouble(-10, 10));//RandomDouble(-10, 10));
    //            }
    //            //h.Mutate(1);
    //            //hr = GetOutput(h, RandomDouble(testMin,testMax), RandomDouble(testMin, testMax));
    //            //hr = h.GetOutputDynamic(1d.Normalise(min, max), 1d.Normalise(min, max)).Single();
    //            hr = GetNumericalOutput(h, rand.Next(testMin, testMax), rand.Next(testMin, testMax));
    //        }
    //        const int fitnessIterationNo = 100;
    //        Console.WriteLine("HR:{0};", hr);
    //        int a=0;// = RandomDouble(-1000, 1000);
    //        int b=0;// = RandomDouble(-1000, 1000);
    //        int r=0;// = h.GetOutput(new double[] { a.Normalise(min,max), b.Normalise(min,max) }).Single().ReverseNormalise(min,max);
    //        double fitness = 0;// = AdditionFitness(a, b, r);
    //        for (int i = 0; i < fitnessIterationNo; i++)
    //        {
    //            a = rand.Next(testMin, testMax);//RandomDouble(testMin, testMax);
    //            b = rand.Next(testMin, testMax);//RandomDouble(testMin, testMax);
    //            r = GetNumericalOutput(h, a, b);
    //            //r = h.GetOutputDynamic(a, b).Single().ReverseNormalise(min, max);
    //            fitness += AdditionFitness(a, b, r);
    //        }
    //        fitness /= fitnessIterationNo;
    //        Console.WriteLine("According to {0}: {1} + {2} = {3}", h.ID, a, b, r);
    //        Console.WriteLine("Fitness: {0};", fitness);
    //        for (int i = 0; i < 2000; i++)
    //        {
    //            if (i % 10 == 0)
    //            {
    //                Console.WriteLine(i);
    //            }
    //            Genome clone = h.CloneGenome();
    //            //Console.WriteLine("Clone node count:{0};", clone.NodeCount());
    //            double num = rand.NextDouble();
    //            const int options = 6;
    //            double optioniterator = 1;
    //            for (int t = 0; t < 3; t++)
    //            {
    //                Train(clone, new double[] { a, b }, a+b);
    //            }
    //            if (num <= optioniterator++/options)
    //            {
    //                int inp = rand.Next(clone.InputCount);
    //                int outt = rand.Next(clone.OutputCount);
    //                clone.CreateIntermediateNode(inp, outt);
    //                //Console.WriteLine("Intermediate Node created");
    //            }
    //            else if (num <= optioniterator++/options)
    //            {
    //                int prevNode = rand.Next(clone.NodeCount());
    //                int nextNode = rand.Next(clone.NodeCount());
    //                clone.CreateNode(prevNode, nextNode);
    //                //Console.WriteLine("Node created");
    //            }
    //            else if (num <= optioniterator++/options)
    //            {
    //                int s = rand.Next(clone.NodeCount());
    //                int d = rand.Next(clone.NodeCount());
    //                double w = rand.NextDouble(-1, 1);//RandomDouble(-1, 1);
    //                clone.CreateLink(s, d, w);
    //                //Console.WriteLine("Link created");
    //            }
    //            else if (num <= optioniterator++/options)
    //            {
    //                int s = rand.Next(clone.NodeCount());
    //                int d = rand.Next(clone.NodeCount());
    //                double w = rand.NextDouble(-1, 1);//RandomDouble(-1, 1);
    //                clone.AlterLinkWeight(s, d, w);
    //                //Console.WriteLine("Link altered");
    //            }
    //            else if (num <= optioniterator++/options)
    //            {
    //                int s = rand.Next(clone.NodeCount());
    //                int d = rand.Next(clone.NodeCount());
    //                clone.RemoveLink(s, d);
    //                //Console.WriteLine("Link removed");
    //            }
    //            else if (num <= optioniterator++/options)
    //            {
    //                int interindex = rand.Next(clone.IntermediateNodeCount());
    //                clone.RemoveNode(interindex);
    //                //Console.WriteLine("Node removed");
    //            }
    //            double avgFitness = 0;
    //            for (int j = 0; j < fitnessIterationNo; j++)
    //            {
    //                a = rand.Next(testMin, testMax);//RandomDouble(testMin, testMax);
    //                b = rand.Next(testMin, testMax);//RandomDouble(testMin, testMax);
    //                r = GetNumericalOutput(clone, a, b);
    //                //r = GetOutput(clone, a, b);
    //                avgFitness += AdditionFitness(a, b, r);
    //                //Console.WriteLine("Raw output:{0};", singleoutput);
    //                if ((i+j) % 500 == 0)
    //                {
    //                    Console.WriteLine("According to {0}: {1} + {2} = {3}", clone.ID, a, b, r);
    //                }
    //            }
    //            avgFitness /= fitnessIterationNo;
    //            //clone.Mutate(5);
    //            if (i % 500 == 0)
    //            {
    //                Console.WriteLine("Fitness: {0};", avgFitness);
    //            }
    //            if (avgFitness < fitness)
    //            {
    //                h.Dispose();
    //                h = clone;
    //                fitness = avgFitness;
    //                Console.WriteLine("New fittest genome. ID: {0}; Fitness: {1};", h.ID, fitness);
    //            }
    //        }
    //        Console.WriteLine("Final Fitness: {0};", fitness);
    //        Console.WriteLine("Done");
    //        Console.ReadKey();
    //    }
    //    static void Train(Genome g, double[] inputs, double output)
    //    {
    //        string stroutput = output.ToString();
    //        stroutput = stroutput.PadLeft(outputCount, '0');
    //        double[] outputs = new double[outputCount];
    //        for (int i = 0; i < stroutput.Length; i++)
    //        {
    //            outputs[i] = int.Parse(stroutput[i].ToString());
    //        }
    //        g.Train(inputs, outputs);
    //    }
    //    static Genome FreshGenome()
    //    {
    //        Genome g;
    //        if (Genome.CreateNewGenome(inputCount, outputCount, ltmCount, stmCount,out g))
    //        {
    //            g.CreateIntermediateNode(rand.Next(inputCount), rand.Next(outputCount));
    //            g.CreateIntermediateNode(rand.Next(inputCount), rand.Next(outputCount));
    //            g.CreateIntermediateNode(rand.Next(inputCount), rand.Next(outputCount));

    //            return g;
    //        }
    //        return null;
    //    }
    //    //static double GetOutput(Genome g, double a, double b)
    //    //{
    //    //    double[] input = new double[] { a.Normalise(min,max), b.Normalise(min,max) };
    //    //    double[] output = g.GetOutput(input);
    //    //    double singleoutput = output[0];
    //    //    return singleoutput.ReverseNormalise(min, max);
    //    //}
    //    static double AdditionFitness(double numa, double numb, double result)
    //    {
    //        double addition = numa + numb;
    //        double difference = addition - result;
    //        double abs = Math.Abs(difference);
    //        return abs;
    //    }
    //    static int GetNumericalOutput(Genome g, int a, int b)
    //    {
    //        double[] input = new double[] {a.NormaliseInt(min,max),b.NormaliseInt(min,max) };
    //        double[] output = g.GetOutput(input);
    //        return output.GetNumber();
    //    }
    //    static int GetNumber(this double[] val)
    //    {
    //        int output = 0;
    //        for (int i = 0; i < val.Length; i++)
    //        {
    //            output += DenormaliseToDigit(val[i]) * (int)Math.Pow(10, i);
    //        }
    //        return output;
    //    }
    //    static int DenormaliseToDigit(double val)
    //    {
    //        return (int)Math.Round(val.ReverseNormalise(0, 9),MidpointRounding.AwayFromZero);
    //    }
    //}
    static class Program
    {
        static SuperRand superRand = new SuperRand();
        const int min = 0;
        const int max = 10;
        const int inputCount = 2;
        const int outputCount = 3;
        const int ltmCount = 0;
        const int stmCount = 0;
        const string file = "file_1.xml";
        public static void Main()
        {
            const int fitnessTestQuan = 100;
            const int iterations = 3000;
            Genome g;
            if (!Genome.ParseGenome(file,out g))
            {
                Console.WriteLine("Failed to parse.");
                if (!Genome.CreateNewGenome(inputCount,outputCount,ltmCount,stmCount, out g))
                {
                    Console.WriteLine("Failed to create genome.");
                    Console.ReadKey();
                    return;
                }
            }
            Console.WriteLine("Start");
            int o = 555;
            while (o == 555)
            {
                g.Mutate(1);
                int a = superRand.Next(100);
                int b = superRand.Next(100);
                g.Train(d(a, b),DigitArray(a+b));
                o = GetNumber(g.GetOutputDynamic(23, 42));
            }
            int[] aArr = GetRandomNumbers(fitnessTestQuan);//new int[fitnessTestQuan];
            int[] bArr = GetRandomNumbers(fitnessTestQuan);//new int[fitnessTestQuan];
            double weakness = GetAverageWeakness(g, aArr, bArr);
            Console.WriteLine("Start: {0}; Weakness: {1};", g.ID, weakness);
            int mutationDelay = 0;
            for (int i = 0; i < iterations; i++)
            {
                Console.WriteLine(i);
                Genome clone = g.CloneGenome();
                Train(clone, aArr, bArr);
                clone.Mutate(2);
                double cloneWeakness = GetAverageWeakness(clone, aArr, bArr);
                if (cloneWeakness < weakness)
                {
                    mutationDelay = 0;
                    g.Dispose();
                    weakness = cloneWeakness;
                    g = clone;
                    Console.WriteLine("New best genome {0} with weakness of {1}.", clone.ID, cloneWeakness);
                }
                else
                {
                    mutationDelay++;
                    clone.Dispose();
                }
                if (mutationDelay > 100)
                {
                    Console.WriteLine("Training time.");
                    for (int x = 0; x < 10; x++)
                    {
                        Train(g, aArr, bArr);
                        int[] testA = GetRandomNumbers(fitnessTestQuan);
                        int[] testB = GetRandomNumbers(fitnessTestQuan);
                        for(int y = 0; y < fitnessTestQuan; y++)
                        {
                            double[] testOut = g.GetOutputDynamic(testA[y], testB[y]);
                            int answer = GetNumber(testOut);
                            Console.WriteLine("{0} + {1} = {2}", testA[y], testB[y], answer);
                        }
                    }
                    mutationDelay = 0;
                }
            }
            g.SaveGenome(file);
            Console.WriteLine("Done.");
            Console.ReadKey();
        }
        static int[] GetRandomNumbers(int length)
        {
            int[] arr = new int[length];
            for (int i = 0; i < length; i++)
            {
                arr[i] = superRand.Next(100);
            }
            return arr;
        }
        static void Train(Genome g, int[] aArr, int[] bArr)
        {
            for (int i = 0; i < aArr.Length; i++)
            {
                g.Train(d(aArr[i], bArr[i]), DigitArray(aArr[i] + bArr[i]));
            }
        }
        static double GetAverageWeakness(Genome g, int[] aArr, int[] bArr)
        {
            double weakness = 0;
            for (int i = 0; i < aArr.Length; i++)
            {
                weakness += GetWeakness(g, aArr[i], bArr[i]);
            }
            return weakness / aArr.Length;
        }
        static double GetWeakness(Genome g,int a, int b)
        {
            double[] o = g.GetOutputDynamic(a, b);
            int answer = GetNumber(o);
            return Math.Abs((a + b) - answer);
        }
        static int GetNumber(double[] output)
        {
            return (int)output[0].ReverseNormalise(0, 200);
            //int num = 0;
            //for (int i = 0; i < outputCount;i++)
            //{
            //    num += output[i].GetDigit() * (int)Math.Pow(10, i);
            //}
            //return num;
        }
        static int GetDigit(this double num)
        {
            return (int)num.ReverseNormalise(0, 10);
        }
        static double[] DigitArray(double num)
        {
            num = (int)num;
            string strnum = num.ToString().PadLeft(3,'0');
            double[] darray = new double[strnum.Length];
            for (int i = 0; i < strnum.Length; i++)
            {
                darray[i] = int.Parse(strnum[i].ToString());
            }
            return darray;
        }
        static double[] d(params double[] nums)
        {
            return nums;
        }
    }
}