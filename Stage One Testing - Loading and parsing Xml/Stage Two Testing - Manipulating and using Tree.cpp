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
	TEST_CLASS(TestcalculateMemoryUsageLocal)
	{
		TEST_METHOD(TestCalculateMemoryUsagePathFound)
		{

			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			treeManager.loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml");

			int actual = treeManager.calculateMemoryUsage("ADS_Single_LinkedList_Exercises/.git",false);

			
			int expected = 449;
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestCalculateMemoryUsagePathNotFound)
		{
			
			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			treeManager.loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml");
			int actual = treeManager.calculateMemoryUsage("ADS_Single_LinkedList_Exercises/.git1",false);
			int expected = -1;
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestCalculateMemoryUsageEmptyPath)
		{

			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			treeManager.loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml");
			int actual = treeManager.calculateMemoryUsage("",false);
			int expected = -1;
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestCalculateMemoryUsageNullTree)
		{

			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			int actual = treeManager.calculateMemoryUsage("ADS_Single_LinkedList_Exercises/.git", false);
			int expected = -1;
			Assert::AreEqual(expected, actual);
		}
	};
	TEST_CLASS(TestcalculateMemoryUsageDeep)
	{
		TEST_METHOD(TestCalculateMemoryUsagePathFoundDeepfromgit)
		{

			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			treeManager.loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml");

			int actual = treeManager.calculateMemoryUsage("ADS_Single_LinkedList_Exercises/.git", true);
			int expected = 449;
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestCalculateMemoryUsagePathFoundDeepfromroot)
		{

			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			treeManager.loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml");

			int actual = treeManager.calculateMemoryUsage("ADS_Single_LinkedList_Exercises", true);
			int expected = 2966521;
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestCalculateMemoryUsagePathFoundDeepfromdebug)
		{
			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			treeManager.loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml");

			int actual = treeManager.calculateMemoryUsage("ADS_Single_LinkedList_Exercises/Debug", true);
			int expected = 2966072;
			Assert::AreEqual(expected, actual);
		}

	};
	TEST_CLASS(TestfindFileOrFolderRecursive)
	{
		TEST_METHOD(TestfindFileOrFolderRecursivePathFound)
		{

			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			treeManager.loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml");

			string actual = treeManager.findFileOrFolder("HEAD");
			string expected = "ADS_Single_LinkedList_Exercises/.git/HEAD";
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestfindFileOrFolderRecursivePathNotFound)
		{

			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);
			treeManager.loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml");

			string actual = treeManager.findFileOrFolder("HEAD1");
			string expected = "File or folder not found.";
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestfindFileOrFolderRecursiveEmptyPath)
		{

			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(xmlParser, xmlFileLoader);

			string actual = treeManager.findFileOrFolder("");
			string expected = "Tree is empty or filename is empty.";
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestfindFileOrFolderRecursiveNullTree)
		{

			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager treeManager(nullptr, nullptr);

			string actual = treeManager.findFileOrFolder("HEAD");
			string expected = "Tree is empty or filename is empty.";
			Assert::AreEqual(expected, actual);
		}
	};
	TEST_CLASS(TestPruneTree)
	{
		TEST_METHOD(TestPruneTreeSimpleSample)
		{
			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager* treeManager = new TreeManager(xmlParser, xmlFileLoader);
			treeManager->loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml");
			treeManager->pruneTree();
			int expected = 9;
			int actual = treeManager->countItemsinTree();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestPruneTreeNullTree)
		{
			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager* treeManager = new TreeManager(xmlParser, xmlFileLoader);
			treeManager->pruneTree();
			int expected = 0;
			int actual = treeManager->countItemsinTree();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(TestPruneTreeEmptyTree)
		{
			XmlParser* xmlParser = new XmlParser();
			XmlFileLoader* xmlFileLoader = new XmlFileLoader();
			TreeManager* treeManager = new TreeManager(xmlParser, xmlFileLoader);
			treeManager->loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_empty.xml");
			treeManager->pruneTree();
			int expected = 0;
			int actual = treeManager->countItemsinTree();
			Assert::AreEqual(expected, actual);
		}

	};


	
}