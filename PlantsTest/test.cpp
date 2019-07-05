#include "pch.h"
#include "../Plants/Garden.h"
#include "../Plants/Garden.cpp"

struct MyClassCombo : public testing::Test {
	Plant *tree;
	Plant *shrub;
	Plant *flower;
	Plant *plant;
	ifstream file_i;
	void SetUp()
	{
		tree = new Tree();
		shrub = new Shrub();
		flower = new Flower();
	}
	void Erase() { delete tree; delete shrub; delete flower; }

};

TEST_F(MyClassCombo, EmptyFileTest)
{
	file_i.open("Test1_empty.txt");
	tree->name = "test";
	tree->In(file_i);
	ASSERT_EQ(-1, ((Tree*)tree)->age);
	file_i.close();
	file_i.open("Test1_empty.txt");
	shrub->name = "test";
	shrub->InCommon(file_i);
	shrub -> In(file_i);
	ASSERT_EQ(0, ((Shrub*)shrub)->month);
	file_i.close();
	file_i.open("Test1_empty.txt");
	flower->name = "test";
	flower->InCommon(file_i);
	flower -> In(file_i);
	ASSERT_EQ(0, ((Flower*)flower)->type);
	file_i.close();
}

TEST_F(MyClassCombo, WrongFileFormatTest)
{
	file_i.open("Test2_Wrong_Format.txt");
	tree->name = "test";
	tree->In(file_i);
	ASSERT_EQ(-3, ((Tree*)tree)->age);
	file_i.close();
	file_i.open("Test1_empty.txt");
	shrub->name = "test";
	shrub->InCommon(file_i);
	shrub->In(file_i);
	ASSERT_EQ(0, ((Shrub*)shrub)->month);
	file_i.close();
	file_i.open("Test1_empty.txt");
	flower->name = "test";
	flower->InCommon(file_i);
	flower->In(file_i);
	ASSERT_EQ(0, ((Flower*)flower)->type);
	file_i.close();
}

TEST_F(MyClassCombo, WrongFileFormatTest2)
{
	file_i.open("Test3_Wrong_Format.txt");
	tree->name = "test";
	tree->In(file_i);
	ASSERT_EQ(0, ((Tree*)tree)->age);
	file_i.close();
	file_i.open("Test1_empty.txt");
	shrub->name = "test";
	shrub->InCommon(file_i);
	shrub->In(file_i);
	ASSERT_EQ(0, ((Shrub*)shrub)->month);
	file_i.close();
	file_i.open("Test1_empty.txt");
	flower->name = "test";
	flower->InCommon(file_i);
	flower->In(file_i);
	ASSERT_EQ(0, ((Flower*)flower)->type);
	file_i.close();
}

TEST_F(MyClassCombo, WrongFileFormatTest3)
{
	file_i.open("Test4_Wrong_Format.txt");
	tree->name = "test";
	tree->In(file_i);
	ASSERT_EQ(-2, ((Tree*)tree)->age);
	file_i.close();
	file_i.open("Test1_empty.txt");
	shrub->name = "test";
	shrub->InCommon(file_i);
	shrub->In(file_i);
	ASSERT_EQ(0, ((Shrub*)shrub)->month);
	file_i.close();
	file_i.open("Test1_empty.txt");
	flower->name = "test";
	flower->InCommon(file_i);
	flower->In(file_i);
	ASSERT_EQ(0, ((Flower*)flower)->type);
	file_i.close();
}

TEST_F(MyClassCombo, WrongFileFormatTest4)
{
	file_i.open("Test5_Wrong_Format.txt");
	tree->name = "test";
	tree->In(file_i);
	ASSERT_EQ(-2, ((Tree*)tree)->age);
	file_i.close();
	file_i.open("Test1_empty.txt");
	shrub->name = "test";
	shrub->InCommon(file_i);
	shrub->In(file_i);
	ASSERT_EQ(0, ((Shrub*)shrub)->month);
	file_i.close();
	file_i.open("Test1_empty.txt");
	flower->name = "test";
	flower->InCommon(file_i);
	flower->In(file_i);
	ASSERT_EQ(0, ((Flower*)flower)->type);
	file_i.close();
}

TEST_F(MyClassCombo, WrongPlantInTest)
{
	file_i.open("Test1_empty.txt");
	Plant *res;
	res = plant-> InPlant(file_i);
	ASSERT_EQ(NULL, res);
	file_i.close();
}

TEST_F(MyClassCombo, WrongPlantInTest2)
{
	file_i.open("Test6_empty.txt");
	Plant *res;
	res = plant->InPlant(file_i);
	ASSERT_EQ(NULL, res);
	file_i.close();
}