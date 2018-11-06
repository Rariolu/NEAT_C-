using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NEAT_Interface;
using NeuralUtil;

namespace NEAT_ZDemo
{
    class Program
    {
        static Random rand = new Random();
        static void Main(string[] args)
        {
            const double min = -5000;
            const double max = 5000;
            Genome g;
            if (!Genome.CreateNewGenome(2,1,0,0,out g))
            {
                Console.WriteLine("Error in genome creation");
                Console.ReadKey();
                return;
            }
            Console.WriteLine("Genome created");
            Genome h = g.CloneGenome();
            double hr = h.GetOutputDynamic(1d.Normalise(min,max), 1d.Normalise(min,max)).Single().ReverseNormalise(min,max);
            Console.WriteLine("hr: {0};", hr);
            h.CreateIntermediateNode(rand.Next(h.InputCount), rand.Next(h.OutputCount));
            h.CreateIntermediateNode(rand.Next(h.InputCount), rand.Next(h.OutputCount));
            h.CreateIntermediateNode(rand.Next(h.InputCount), rand.Next(h.OutputCount));
            //for (int i = 0; i < 1000 && hr == 0; i++)
            //{
            //    int nodecount = h.NodeCount();
            //    if (nodecount == 0)
            //    {
            //        Console.WriteLine("This is silly");
            //        Console.ReadKey();
            //        return;
            //    }
            //    int prev = rand.Next(nodecount);
            //    int next = rand.Next(nodecount);
            //    if (rand.NextDouble() < 0.5)
            //    {
            //        h.CreateNode(prev, next);
            //    }
            //    else
            //    {
            //        h.CreateLink(prev, next, RandomDouble(-10, 10));
            //    }
            //    //h.Mutate(1);
            //    hr = h.GetOutputDynamic(1d.Normalise(min,max), 1d.Normalise(min,max)).Single().ReverseNormalise(min,max);
            //}
            double a = RandomDouble(-1000, 1000);
            double b = RandomDouble(-1000, 1000);
            double r = h.GetOutput(new double[] { a.Normalise(min,max), b.Normalise(min,max) }).Single().ReverseNormalise(min,max);
            double fitness = AdditionFitness(a, b, r);
            Console.WriteLine("According to {0}: {1} + {2} = {3}", h.ID, a, b, r);
            Console.WriteLine("Fitness: {0};", fitness);
            for (int i = 0; i < 100; i++)
            {
                Genome clone = h.CloneGenome();
                clone.Mutate(5);
                r = clone.GetOutput(new double[] { a.Normalise(min,max), b.Normalise(min,max) }).Single().ReverseNormalise(min,max);
                double newfitness = AdditionFitness(a, b, r);
                Console.WriteLine("According to {0}: {1} + {2} = {3}", h.ID, a, b, r);
                Console.WriteLine("Fitness: {0};", newfitness);
                if (newfitness < fitness)
                {
                    h.Dispose();
                    h = clone;
                    fitness = newfitness;
                }
            }
            Console.WriteLine("Done");
            Console.ReadKey();
        }
        static double AdditionFitness(double numa, double numb, double result)
        {
            double addition = numa + numb;
            double difference = addition - result;
            double abs = Math.Abs(difference);
            return abs;
        }
        static double RandomDouble(double min, double max)
        {
            return rand.NextDouble() * (max - min) + min;
        }
    }
}