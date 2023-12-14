#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2023_CA2_D_F/TreeManager.h"
#include "../ADS_2023_CA2_D_F/TreeManager.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StageTwoTestingManipulatingandUsingTree
{
	TEST_CLASS(TestCountItemsinTree)
	{
	public:
	TEST_METHOD(TestCountItemsinTreeSimpleSample)
		{
			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			treeManager.loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml");
			int expected = 12;
			int actual = treeManager.countItemsinTree();
			Assert::AreEqual(expected, actual);
		}
	TEST_METHOD(TestCountItemsinNullTree)
		{
			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			int expected = 0;
			int actual = treeManager.countItemsinTree();
			Assert::AreEqual(expected, actual);
		}
		
	};
	TEST_CLASS(TestcalculateMemoryUsage)
	{
		TEST_METHOD(TestCalculateMemoryUsagePathFound)
		{

			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			treeManager.loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml");

			int actual = treeManager.calculateMemoryUsage("ADS_Single_LinkedList_Exercises/.git");

			
			int expected = 449;
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestCalculateMemoryUsagePathNotFound)
		{
			
			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			treeManager.loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml");
			int actual = treeManager.calculateMemoryUsage("ADS_Single_LinkedList_Exercises/.git1");
			int expected = -1;
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestCalculateMemoryUsageEmptyPath)
		{

			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			treeManager.loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml");
			int actual = treeManager.calculateMemoryUsage("");
			int expected = -1;
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestCalculateMemoryUsageNullTree)
		{

			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			int actual = treeManager.calculateMemoryUsage("ADS_Single_LinkedList_Exercises/.git");
			int expected = -1;
			Assert::AreEqual(expected, actual);
		}

	};
}