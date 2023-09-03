#pragma once
#include <cstdlib>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <algorithm>
#include <sstream>

void menu();
void chooseOption();
void displayArray(int* array, int size);

void displayDescriptiveStatisticsMenu()
{
	cout << "3> Descriptive Statistics" << endl;
	cout << "************************************************************" << endl;
	cout << "A> Read, store, and display data set   M> Mid Range" << endl;
	cout << "B> Minimum                             N> Quartiles " << endl;
	cout << "C> Maximum                             O> Interquartile Range" << endl;
	cout << "D> Range                               P> Outliers" << endl;
	cout << "E> Size                                Q> Sum of Squares" << endl;
	cout << "F> Sum                                 R> Mean Absolute Deviation" << endl;
	cout << "G> Mean                                S> Root Mean Square" << endl;
	cout << "H> Median                              T> Standard Error of the Mean" << endl;
	cout << "I> Frequencies                         U> Coefficient of Variation" << endl;
	cout << "J> Mode                                V> Relative Standard Deviation" << endl;
	cout << "K> Standard Deviation                  W> Display and write all results to text file" << endl;
	cout << "L> Variance                                         " << endl;
	cout << "************************************************************" << endl;
	cout << "X. Return" << endl;
	cout << "************************************************************" << endl;
	cout << "Option: ";
}

void insertSorted(int*& arr, int& n, int num) {
	int* newArr = new int[n + 1];

	int i;
	for (i = 0; i < n; ++i) {
		if (arr[i] > num) break;
		newArr[i] = arr[i];
	}

	newArr[i] = num;

	for (; i < n; ++i) {
		newArr[i + 1] = arr[i];
	}

	delete[] arr;
	arr = newArr;
	++n;
}

void readIntsFromFile(const string& filename, int*& arrayInts, int& count) {
	ifstream file(filename);

	if (!file.is_open()) {
		throw runtime_error("Unable to open the file");
	}

	count = 0;
	int number;

	while (file >> number) {
		insertSorted(arrayInts, count, number);
	}

	file.close();
}

int findMinimum(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find minimum.");
	}

	int minVal = numeric_limits<int>::max();
	for (int i = 0; i < count; ++i) {
		if (arrayInts[i] < minVal) {
			minVal = arrayInts[i];
		}
	}

	return minVal;
}

int findMaximum(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find maximum.");
	}

	int maxVal = numeric_limits<int>::min();
	for (int i = 0; i < count; ++i) {
		if (arrayInts[i] > maxVal) {
			maxVal = arrayInts[i];
		}
	}

	return maxVal;
}

double calculateAverage(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot calculate average.");
	}

	int sum = 0;
	for (int i = 0; i < count; ++i) {
		sum += arrayInts[i];
	}

	return static_cast<double>(sum) / count;
}

double calculateStandardDeviation(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot calculate standard deviation.");
	}

	double mean = calculateAverage(arrayInts, count);
	double sumOfSquares = 0;

	for (int i = 0; i < count; ++i) {
		sumOfSquares += (arrayInts[i] - mean) * (arrayInts[i] - mean);
	}

	return sqrt(sumOfSquares / count - 1);
}

int findSum(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find sum.");
	}

	int sum = 0;
	for (int i = 0; i < count; ++i) {
		sum += arrayInts[i];
	}

	return sum;
}

double findMean(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find mean.");
	}

	return calculateAverage(arrayInts, count);  // average and mean are the same
}

double findMedian(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find median.");
	}

	sort(arrayInts, arrayInts + count);

	if (count % 2 == 0) {
		return (arrayInts[count / 2 - 1] + arrayInts[count / 2]) / 2.0;
	}
	else {
		return arrayInts[count / 2];
	}
}

int findRange(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find range.");
	}

	int minVal = arrayInts[0];
	int maxVal = arrayInts[0];

	for (int i = 1; i < count; ++i) {
		if (arrayInts[i] < minVal) minVal = arrayInts[i];
		if (arrayInts[i] > maxVal) maxVal = arrayInts[i];
	}

	return maxVal - minVal;
}

void findFrequencies(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find freqencies.");
	}

	cout << "ELEMENT\tFREQUENCY\tPECENTAGE" << endl;
	cout << "=======\t=========\t==========" << endl;

	int frequency = 1;
	for (int i = 0; i < count; ++i) {
		if (i < count - 1 && arrayInts[i] == arrayInts[i + 1]) {
			++frequency;
		}
		else {
			double percentage = ((double)frequency / count) * 100;
			cout << arrayInts[i] << "\t" << frequency << "\t\t" << percentage << "%" << endl;
			frequency = 1;
		}
	}
}

void findMode(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find mode.");
	}

	int highestFreq = 0;
	int mode = arrayInts[0];
	int freq = 1;

	for (int i = 1; i < count; ++i) {
		if (arrayInts[i] == arrayInts[i - 1]) {
			++freq;
		}
		else {
			freq = 1;
		}
		if (freq > highestFreq) {
			highestFreq = freq;
			mode = arrayInts[i];
		}
	}

	if (highestFreq == 1) {
		cout << "No mode found, all numbers appear only once." << endl;
	}
	else {
		cout << "Mode: " << mode << " (Frequency: " << highestFreq << ")" << endl;
	}
}

double findVariance(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find variance.");
	}
	if (count == 1) {
		throw runtime_error("Variance is undefined for a single-element dataset.");
	}

	// First calculate the mean
	int sum = 0;
	for (int i = 0; i < count; ++i) {
		sum += arrayInts[i];
	}
	double mean = static_cast<double>(sum) / count;

	// Now calculate the variance
	double variance = 0;
	for (int i = 0; i < count; ++i) {
		variance += pow(arrayInts[i] - mean, 2);
	}
	variance /= count - 1;

	return variance;
}

double findMidrange(int* arrayInts, int count) {
	if (count == 0) {
		throw runtime_error("The array is empty, cannot find midrange.");
	}

	int minVal = arrayInts[0];
	int maxVal = arrayInts[0];

	for (int i = 1; i < count; ++i) {
		if (arrayInts[i] < minVal) {
			minVal = arrayInts[i];
		}
		if (arrayInts[i] > maxVal) {
			maxVal = arrayInts[i];
		}
	}

	return static_cast<double>(minVal + maxVal) / 2;
}

void findQuartiles(int* arrayInts, int count) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot find quartiles.");
	}

	// calculate Q2 (second quartile / median)
	double q2 = findMedian(arrayInts, count);
	std::cout << "Q2 (Second Quartile/Median): " << q2 << std::endl;

	if (count < 4) {
		std::cout << "The dataset is too small for first and third quartile calculation." << std::endl;
		return;
	}

	int lowerCount = count / 2;
	int upperCount = lowerCount;

	// if the dataset has an odd number, the upper half will have one more element.
	if (count % 2 != 0) {
		++upperCount;
	}

	int* lowerHalf = new int[lowerCount];
	int* upperHalf = new int[upperCount];

	for (int i = 0; i < lowerCount; ++i) {
		lowerHalf[i] = arrayInts[i];
	}

	int startIdxForUpper = (count % 2 == 0) ? lowerCount : (lowerCount + 1);
	for (int i = 0; i < upperCount; ++i) {
		upperHalf[i] = arrayInts[startIdxForUpper + i];
	}

	// calculate Q1 (first quartile) and Q3 (third quartile)
	double q1 = findMedian(lowerHalf, lowerCount);
	double q3 = findMedian(upperHalf, upperCount);

	// output the quartiles
	std::cout << "Q1 (First Quartile): " << q1 << std::endl;
	std::cout << "Q3 (Third Quartile): " << q3 << std::endl;

	delete[] lowerHalf;
	delete[] upperHalf;
}

double findInterquartileRange(int* arrayInts, int count) {
	if (count < 4) {
		throw std::runtime_error("The dataset is too small to calculate the interquartile range.");
	}

	int lowerCount = count / 2;
	int upperCount = lowerCount;

	// if the dataset has an odd number, the upper half will have one more element.
	if (count % 2 != 0) {
		++upperCount;
	}

	int* lowerHalf = new int[lowerCount];
	int* upperHalf = new int[upperCount];

	for (int i = 0; i < lowerCount; ++i) {
		lowerHalf[i] = arrayInts[i];
	}

	int startIdxForUpper = (count % 2 == 0) ? lowerCount : (lowerCount + 1);
	for (int i = 0; i < upperCount; ++i) {
		upperHalf[i] = arrayInts[startIdxForUpper + i];
	}

	// calculate Q1 and Q3
	double q1 = findMedian(lowerHalf, lowerCount);
	double q3 = findMedian(upperHalf, upperCount);

	delete[] lowerHalf;
	delete[] upperHalf;

	// calculate and return the interquartile range
	return q3 - q1;
}

void findOutliers(int* arrayInts, int count) {
	if (count < 4) {
		throw std::runtime_error("The dataset is too small to identify outliers.");
	}

	double iqr = findInterquartileRange(arrayInts, count);

	int lowerCount = count / 2;
	int upperCount = lowerCount;
	if (count % 2 != 0) {
		++upperCount;
	}

	int* lowerHalf = new int[lowerCount];
	int* upperHalf = new int[upperCount];

	for (int i = 0; i < lowerCount; ++i) {
		lowerHalf[i] = arrayInts[i];
	}

	int startIdxForUpper = (count % 2 == 0) ? lowerCount : (lowerCount + 1);
	for (int i = 0; i < upperCount; ++i) {
		upperHalf[i] = arrayInts[startIdxForUpper + i];
	}

	double q1 = findMedian(lowerHalf, lowerCount);
	double q3 = findMedian(upperHalf, upperCount);

	delete[] lowerHalf;
	delete[] upperHalf;

	double lowerFence = q1 - 1.5 * iqr;
	double upperFence = q3 + 1.5 * iqr;

	cout << "Outliers in the dataset: ";

	bool hasOutliers = false;
	for (int i = 0; i < count; ++i) {
		if (arrayInts[i] < lowerFence || arrayInts[i] > upperFence) {
			cout << arrayInts[i] << ' ';
			hasOutliers = true;
		}
	}

	if (!hasOutliers) {
		cout << "No outliers found.";
	}

	cout << endl;
}

double findSumOfSquares(int* arrayInts, int count) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot find sum of squares.");
	}

	double mean = findMean(arrayInts, count);
	double sumOfSquares = 0.0;

	for (int i = 0; i < count; ++i) {
		double deviation = static_cast<double>(arrayInts[i]) - mean;
		sumOfSquares += deviation * deviation;
	}

	return sumOfSquares;
}

double findSumAbsoluteDeviation(int* arrayInts, int count, double mean) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate sum of absolute deviations.");
	}

	double sumAbsoluteDeviation = 0;
	for (int i = 0; i < count; ++i) {
		sumAbsoluteDeviation += std::abs(arrayInts[i] - mean);
	}

	return sumAbsoluteDeviation;
}

double findMeanAbsoluteDeviation(int* arrayInts, int count) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate mean absolute deviation.");
	}

	double mean = findMean(arrayInts, count);  // use existing findMean function
	double sumAbsoluteDeviation = findSumAbsoluteDeviation(arrayInts, count, mean);
	double mad = sumAbsoluteDeviation / count;

	return mad;
}

double findRootMeanSquare(int* arrayInts, int count) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate root mean square.");
	}

	double sumSquared = 0;
	for (int i = 0; i < count; ++i) {
		sumSquared += arrayInts[i] * arrayInts[i];
	}

	double rms = sqrt(sumSquared / count);
	return rms;
}

double findStandardError(int* arrayInts, int count, double standardDeviation) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate standard error.");
	}

	double standardError = standardDeviation / sqrt(count);
	return standardError;
}

double findCoefficientOfVariation(int* arrayInts, int count, double standardDeviation, double mean) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate coefficient of variation.");
	}
	if (mean == 0) {
		throw std::runtime_error("Mean is zero, cannot calculate coefficient of variation.");
	}

	double coefficientOfVariation = (standardDeviation / mean) * 100;  // as a percentage
	return coefficientOfVariation;
}

double findRelativeStandardDeviation(int* arrayInts, int count, double standardDeviation, double mean) {
	if (count == 0) {
		throw std::runtime_error("The array is empty, cannot calculate relative standard deviation.");
	}
	if (mean == 0) {
		throw std::runtime_error("Mean is zero, cannot calculate relative standard deviation.");
	}

	double relativeStandardDeviation = (standardDeviation / mean) * 100;  // As a percentage
	return relativeStandardDeviation;
}

int descriptiveStatistics() {
	int* arrayInts = nullptr;
	int count = 0;
	char option;
	string inputLine;

	do {
		displayDescriptiveStatisticsMenu();
		std::getline(std::cin, inputLine);  // read the whole line

		std::stringstream ss(inputLine);
		ss >> option;  // try to extract a char

		if (ss.fail()) {  // failed to extract a char
			std::cin.clear();
			cout << "Invalid option. Please try again." << endl;
			system("pause");
			system("cls");
			continue;  // skip the remaining code in the loop and start from the beginning
		}

		// If the user entered extra characters after the first one
		if (!ss.eof()) {
			string extra;
			ss >> extra;
			if (!ss.fail()) {
				cout << "Invalid option. Please enter only a single character." << endl;
				system("pause");
				system("cls");
				continue;
			}
		}

		switch (toupper(option))
		{

		case 'A': // read, store, and display into sorted dynamic array
		{
			
			string filename;
			cout << "\nPlease enter the filename: ";
			cin >> filename;

			// clear the input buffer before reading the next line
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			try {
				readIntsFromFile(filename, arrayInts, count);
				displayArray(arrayInts, count);
			}
			catch (const runtime_error& e) {
				cout << e.what() << endl;
			}
			break;
		}

		case 'B': // minimum

			
			try {
				int minVal = findMinimum(arrayInts, count);
				cout << "\nThe minimum value of the given data set is: " << minVal << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			
			break;

		case 'C': // maximum

			try {
				int maxVal = findMaximum(arrayInts, count);
				cout << "\nThe maximum value of the given data set is: " << maxVal << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			
			break;

		case 'D': // range

			
			try {
				int range = findRange(arrayInts, count);
				cout << "\nThe range of the given data set is: " << range << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			
			break;

		case 'E': // size

			
			cout << "\nThe size of the given data set is: " << count << endl << endl;
			
			break;

		case 'F': // sum

	
			try {
				int sum = findSum(arrayInts, count);
				cout << "\nThe sum of the given data set is: " << sum << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			
			break;

		case 'G': // mean

			
			try {
				double meanVal = findMean(arrayInts, count);
				cout << "\nThe mean of the given data set is: " << meanVal << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			
			break;

		case 'H': // median

			
			try {
				double median = findMedian(arrayInts, count);
				cout << "\nThe median of the given data set is: " << median << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			
			break;

		case 'I': // frequencies

			
			try {
				cout << endl;
				findFrequencies(arrayInts, count);
				cout << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			
			break;

		case 'J': // mode

			
			try {
				cout << endl;
				findMode(arrayInts, count);
				cout << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			
			break;

		case 'K': // standard deviation

            // new line
            cout << endl;

            try {
                double stddev = calculateStandardDeviation(arrayInts, count);
                cout << "The standard deviation of the given data set is: " << stddev << endl;
               
            }
            catch (const runtime_error& e) {
                cerr << e.what() << endl;
            }

            // new line
            cout << endl;

            

            break; 

		case 'L': // variance

			
			try {
				double varianceVal = findVariance(arrayInts, count);
				cout << "\nThe variance of the given data set is: " << varianceVal << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			
			break;

		case 'M': // midrange

			
			try {
				double midrangeVal = findMidrange(arrayInts, count);
				cout << "\nThe midrange of the given data set is: " << midrangeVal << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
			}
			
			break;

		case 'N': // quartiles

			
			try {
				cout << endl;
				findQuartiles(arrayInts, count);
				cout << endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}
			
			break;

		case 'O': // interquartile range

			
			try {
				double iqr = findInterquartileRange(arrayInts, count);
				cout << "\nThe interquartile range (IQR) of the given data set is: " << iqr << endl << endl;
			}
			catch (const std::runtime_error& e) {
				cerr << e.what() << endl;
			}
			
			break;

		case 'P': // outliers

			
			try {
				findOutliers(arrayInts, count);
				cout << "\nThe outliers of the given data set is: " << findOutliers << endl << endl;
			}
			catch (const std::runtime_error& e) {
				cerr << e.what() << endl;
			}
			
			break;

		case 'Q': // sum of squares

			system("cls");
			try {
				double sumOfSquaresVal = findSumOfSquares(arrayInts, count);
				cout << "The sum of squares for the given data set is: " << sumOfSquaresVal << endl;
			}
			catch (const std::runtime_error& e) {
				cerr << e.what() << endl;
			}
			system("pause");
			system("cls");
			break;

		case 'R': // mean absolute deviation

			system("cls");
			try {
				double mad = findMeanAbsoluteDeviation(arrayInts, count);
				std::cout << "The Mean Absolute Deviation (MAD) of the given data set is: " << mad << std::endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}
			system("pause");
			system("cls");
			break;

		case 'S': // root mean square

			system("cls");
			try {
				double rms = findRootMeanSquare(arrayInts, count);
				std::cout << "The Root Mean Square (RMS) of the given data set is: " << rms << std::endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}
			system("pause");
			system("cls");
			break;

		case 'T': // standard error of the mean

			system("cls");
			try {
				double stdDev = calculateStandardDeviation(arrayInts, count);
				double standardError = findStandardError(arrayInts, count, stdDev);
				std::cout << "The Standard Error of the Mean for the given data set is: " << standardError << std::endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}
			system("pause");
			system("cls");
			break;

		case 'U': // coefficient of variation

			system("cls");
			try {
				double mean = findMean(arrayInts, count);
				double stdDev = calculateStandardDeviation(arrayInts, count);
				double coefficientOfVariation = findCoefficientOfVariation(arrayInts, count, stdDev, mean);
				std::cout << "The Coefficient of Variation for the given data set is: " << coefficientOfVariation << "%" << std::endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}
			system("pause");
			system("cls");
			break;

		case 'V': // relative standard deviation

			system("cls");
			try {
				double mean = findMean(arrayInts, count);
				double stdDev = calculateStandardDeviation(arrayInts, count);
				double relativeStandardDeviation = findRelativeStandardDeviation(arrayInts, count, stdDev, mean);
				std::cout << "The Relative Standard Deviation for the given data set is: " << relativeStandardDeviation << "%" << std::endl;
			}
			catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
			}
			system("pause");
			system("cls");
			break;

		case 'W': // display all results and write to an output text file
		{
			system("cls");
			std::ofstream outputFile("DescriptiveStatisticsResults.txt");
			if (!outputFile) {
				cerr << "Error opening output file." << endl;
				break;
			}
			try {
				// writing to file (and this will overwrite the file if it already exists)
				int minVal = findMinimum(arrayInts, count);
				outputFile << "Minimum Value: " << minVal << endl;
				cout << "Minimum Value: " << minVal << endl;

				int maxVal = findMaximum(arrayInts, count);
				outputFile << "Maximum Value: " << maxVal << endl;
				cout << "Maximum Value: " << maxVal << endl;

				int range = findRange(arrayInts, count);
				outputFile << "Range: " << range << endl;
				cout << "Range: " << range << endl;

				outputFile << "Size: " << count << endl;
				cout << "Size: " << count << endl;

				cout << "All results have been written to 'DescriptiveStatisticsResults.txt'." << endl;
			}
			catch (const runtime_error& e) {
				cerr << e.what() << endl;
				outputFile << "Error: " << e.what() << endl;
			}

			outputFile.close();
			system("pause");
			system("cls");
		}
		break;

		case 'X': // exit

			cout << "Exiting to previous menu." << endl;
			system("pause");
			system("cls");
			menu();
			chooseOption();
			break;

		default: // invalid option

			cout << "Invalid option. Please try again." << endl;
			system("pause");
			system("cls");
			break;

		}

		//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	} while (toupper(option) != 'X');
	delete[] arrayInts;
	return 0;
}
void displayArray(int* array, int size) {
	cout << "\nData set with " << size << " data: \n";
	cout << "{ ";
	for (int i = 0; i < size - 1; ++i) 
	{
		cout << array[i] << ", ";
	}
	cout << array[size - 1] << " }\n\n";
}








