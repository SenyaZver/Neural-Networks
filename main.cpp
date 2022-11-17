#include <vector>
#include <iostream>
#include "ConvolutionalBrain/ConvolutionalLayer.h"
#include "ConvolutionalBrain/ReshapeLayer.h"
#include "ConvolutionalBrain/DenseLayer.h"
#include "ConvolutionalBrain/ConvolutionBrain.h"
#include "BrainSaver.h"
#include "BrainLoader.h"
#include "Common.h"
#include "Tests/ConvolutionTest.h"
#include "Tests/PerceptronTest.h"
#include "Tests/ConvolutionalNEAT_Test.h"
#include "Tests/NEAT_layer_Test.h"
#include "Tests/NEATcopyTest.h"


int main() {

//	convTest();
//	PerceptronTest();
//	convNEAT_test();
//	NEAT_layer_Test();
	NEATcopyTest();
}


