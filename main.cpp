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


int main() {

//	convTest();

//	PerceptronTest();

	convNEAT_test();

}


