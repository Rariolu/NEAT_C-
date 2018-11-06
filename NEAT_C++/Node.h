#ifndef _NODE_H
#define _NODE_H

#include<iostream>
#include "Operations.h"
#include<vector>

class Node
{
	public:
		class Link
		{
			public:
				Link(Node* source, Node*destination) : _source(source), _destination(destination), _weight(Operations::randd->NextDouble())
				{

				}
				Link(Node* source, Node* destination, double weight) : _source(source), _destination(destination), _weight(weight)
				{

				}
				~Link()
				{

				}
				Node* GetSource()
				{
					return _source;
				}
				Node* GetDestination()
				{
					return _destination;
				}
				double GetWeight()
				{
					return _weight;
				}
				void SetWeight(double val)
				{
					_weight = val;
				}
				Link* GetClone()
				{
					if (_source->GetClone() && _destination->GetClone())
					{
						Link* clone = new Link(_source->GetClone(), _destination->GetClone(), _weight);
						_source->GetClone()->AddOutput(clone);
						_destination->GetClone()->AddInput(clone);
						return clone;
					}
					return NULL;
				}
			private:
				Node* _source;
				Node* _destination;
				double _weight;
		};
		Node();
		Node(int id);
		~Node();
		void AddInput(Node* node);
		void AddInput(Link* link);
		void AddOutput(Node* node);
		void AddOutput(Link* link);
		std::vector<Link*> GetInputs();
		std::vector<Link*> GetOutputs();
		void CheckNodeNum(int value);
		virtual double GetNodeValue(double inputs[]);
		double GetSigmoid(double inputs[]);
		void ResetMemory();
		void RemoveInput(Link* link);
		void RemoveInput(int index);
		void RemoveOutput(Link* link);
		void RemoveOutput(int index);
		void DeleteLinks();
		double GetDistance();
		void SetDistance(double d);
		void SetInputWeight(int index, double weight);
		void SetOutputWeight(int index, double weight);
		int GetNodeID();
		virtual Node* GetClone();
		void RandomiseDistance();
		void RandomiseDistance(double min, double max);
		virtual bool IsGold() { return false; }
	protected:
		double Memorise(double value);
		bool memorised = false;
		double memorisedOutput;
		static int nodenum;
		Node* _clone;
		double distanceFromStart;
		static const int maxDistance;
	private:
		std::vector<Link*> _inputs;
		std::vector<Link*> _outputs;
		
		int nodeid;
};

#endif