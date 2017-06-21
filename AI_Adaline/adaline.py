# Pseudocode


# 1. Initialize weigths at arbitrary values
# 2. Define a learning rate η
# 3. Repeat:
#         For each pattern in the training set
#         Apply xp to the adaline input
#         Observe the output and compute the error 
#         For each weight k accumulate the product
#         After processing all patterns, update each weight k




import random


class adalineAlgorithm(object):
    """adaline neuron"""

    def __init__(self, numInputElements=768, numOutputElements=7, learningRate=0.099, minError=.13, bias=0, maxIterations=10000, outputElements=[], weights=[]):
        self.numInputElements = numInputElements
        self.numOutputElements = numOutputElements
        self.learningRate = learningRate
        self.minError = minError
        self.bias = bias
        self.maxIterations = maxIterations

        self.outputElements = outputElements
        self.weights = self.initWeights()

    def initWeights(self):
        weights = []
        for randomWeights in range(0, self.numOutputElements):
            weights.append(random.randint(1, 50))
        return weights

    def procces(self, tData, iters):
        output = 0
        for j in range(0, 6):  # len(tData[iters])):
            output += tData[iters][j] * self.weights[j]
        return output

    # def test(self, testSet):

    def train(self, trainSet):
        for iters in range(1, self.maxIterations):
            "Iterate" + str(iters)
            output = 0
            for i in range(0, len(trainSet)):
                output = self.procces(trainSet, i)
                desiredOutput = output
                print (output)
                for data in range(0, 6):  # len(self.weights)):
                    self.weights[data] = self.weights[data] + self.learningRate * \
                        (self.outputElements[i] -
                         desiredOutput) * trainSet[i][data]

    def loadDataset(self, filename, tData, trainSet, testSet):
        with open(filename) as f:
            for line in f:
                # for numstr in line.split():
                inner_list = [float(elt.strip()) for elt in line.split()]
                #fline = float(numstr)
                tData.append(inner_list)

            test = len(tData) / 3
            trainSet = tData[:int(test)]
            testSet = tData[int(test):]

            print(tData)
            print(trainSet)
            print(testSet)


def main():

    tData = []
    dTrain = []
    dTest = []
    adaline = adalineAlgorithm()
    adaline.loadDataset("pimadiabetes.data.txt", tData, dTrain, dTest)

    adaline.train(dTrain)

    # adaline.test(testSet)


main()
#trainginData = [[-1, -1, 1, 1], [1, 1, 1, 1], [1, 1, -1, 1], [-1, -1, -1, 1]]
#adaline = adalineAlgorithm()
# adaline.train(trainginData)
