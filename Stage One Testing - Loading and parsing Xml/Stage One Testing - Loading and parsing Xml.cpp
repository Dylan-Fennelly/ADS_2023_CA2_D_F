#include "pch.h"
#include "CppUnitTest.h"
#include"Tree.h"
#include "../ADS_2023_CA2_D_F/XmlParser.h"
#include "../ADS_2023_CA2_D_F/XmlParser.cpp"
#include "../ADS_2023_CA2_D_F/XmlNode.h"
#include "../ADS_2023_CA2_D_F/XmlNode.cpp"
#include "../ADS_2023_CA2_D_F/XmlFileLoader.h"
#include "../ADS_2023_CA2_D_F/XmlFileLoader.cpp"
#include "../ADS_2023_CA2_D_F/FileNode.h"
#include "../ADS_2023_CA2_D_F/FileNode.cpp"
#include "../ADS_2023_CA2_D_F/FolderNode.h"
#include "../ADS_2023_CA2_D_F/FolderNode.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StageOneTestingLoadingandparsingXml
{
    TEST_CLASS(XmlParserTests)
    {
    public:
        // Test for validateXML function
        TEST_METHOD(ValidateXML_ValidXml_ShouldReturnTrue)
        {
            // Arrange
            XmlParser xmlParser;
            std::string validXml = "<root><tag1></tag1><tag2></tag2></root>";

            // Act
            bool result = xmlParser.validateXML(validXml);

            // Assert
            Assert::IsTrue(result);
        }

        TEST_METHOD(ValidateXML_InvalidXml_ShouldReturnFalse)
        {
            // Arrange
            XmlParser xmlParser;
            std::string invalidXml = "<root><tag1></tag1><tag2></tag2></invalid>";

            // Act
            bool result = xmlParser.validateXML(invalidXml);

            // Assert
            Assert::IsFalse(result);
        }

        // Test for parseXml function
        TEST_METHOD(ParseXml_ValidXml_ShouldReturnNonNullTree)
        {
            // Arrange
            XmlParser xmlParser;
            std::string validXml = R"(
            <dir>
                <name>ADS_Single_LinkedList_Exercises</name>
                <dir>
                    <name>.git</name>
                    <file>
                        <name>config</name>
                        <length>353 b</length>
                        <type>config</type>
                    </file>
                    <file>
                        <name>description</name>
                        <length>73 b</length>
                        <type>description</type>
                    </file>
                    <file>
                        <name>HEAD</name>
                        <length>23 b</length>
                        <type>HEAD</type>
                    </file>
                </dir>
                <dir>
                    <name>.vs</name>
                    <dir>
                        <name>ADS_Single_LinkedList_Exercises</name>
                        <dir>
                            <name>v17</name>
                        </dir>
                    </dir>
                </dir>
                <dir>
                    <name>Debug</name>
                    <file>
                        <name>SinglyLinkedList.pdb</name>
                        <length>978944 b</length>
                        <type>pdb</type>
                    </file>
                    <file>
                        <name>TestSinglyLinkedList.exp</name>
                        <length>41528 b</length>
                        <type>exp</type>
                    </file>
                    <file>
                        <name>TestSinglyLinkedList.pdb</name>
                        <length>1945600 b</length>
                        <type>pdb</type>
                    </file>
                </dir>
            </dir>
        )";

            // Act
            Tree<XmlNode*>* result = xmlParser.parseXml(validXml);

            // Assert
            Assert::IsNotNull(result);

            // Additional assertion to check the tree structure
            Assert::IsTrue(result->getData()->getName() == "ADS_Single_LinkedList_Exercises");

            // Add more assertions as needed to validate the tree structure
        }

        TEST_METHOD(ParseXml_InvalidXml_ShouldReturnNullTree)
        {
            // Arrange
            XmlParser xmlParser;
            std::string invalidXml = "<invalid><tag></tag></invalid>";

            // Act
            Tree<XmlNode*>* result = xmlParser.parseXml(invalidXml);

            // Assert
            Assert::IsNull(result);
        }
    };
    TEST_CLASS(XmlFileLoaderTests)
    {
    public:
        TEST_METHOD(LoadFile_ValidFilePath_ShouldReturnFileContent)
        {
            // Arrange
            XmlFileLoader xmlFileLoader;
            std::string filePath = "valid_file.xml";
            std::string expectedContent = "<root><tag>Content</tag></root>";

            // Create a sample file for testing
            std::ofstream outFile(filePath);
            outFile << expectedContent;
            outFile.close();

            // Act
            std::string result = xmlFileLoader.loadFile(filePath);

            // Remove newline characters from both expected and actual content
            expectedContent.erase(std::remove(expectedContent.begin(), expectedContent.end(), '\n'), expectedContent.end());
            result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());

            // Assert
            Assert::AreEqual(expectedContent, result);

            // Cleanup: Delete the temporary file
            std::remove(filePath.c_str());
        }

        TEST_METHOD(LoadFile_NonExistentFilePath_ShouldThrowException)
        {
            // Arrange
            XmlFileLoader xmlFileLoader;
            std::string nonExistentFilePath = "nonexistent_file.xml";

            // Act & Assert
            Assert::ExpectException<std::exception>([&]() {
                xmlFileLoader.loadFile(nonExistentFilePath);
                });
        }

        TEST_METHOD(LoadFile_EmptyFile_ShouldReturnEmptyString)
        {
            // Arrange
            XmlFileLoader xmlFileLoader;
            std::string filePath = "empty_file.xml";

            // Create an empty file for testing
            std::ofstream outFile(filePath);
            outFile.close();

            // Act
            std::string result = xmlFileLoader.loadFile(filePath);

            // Assert
            Assert::AreEqual(std::string(), result);

            // Cleanup: Delete the temporary file
            std::remove(filePath.c_str());
        }
    };
 };
    
    