using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NeuralUtil
{
    public class SuperRand : Random
    {
        public double NextDouble(double min, double max)
        {
            return NextDouble() * (max - min) + min;
        }
    }
}