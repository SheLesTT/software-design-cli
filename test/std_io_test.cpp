#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <std_input.hpp>
#include <std_output.hpp>

namespace coreutils::test {

class StdIOTest : public ::testing::Test {
 protected:
  void SetUp() override {
    original_cin = std::cin.rdbuf();
    original_cout = std::cout.rdbuf();
  }

  void TearDown() override {
    std::cin.rdbuf(original_cin);
    std::cout.rdbuf(original_cout);
  }

  void setInput(const std::string& input) {
    input_stream.str(input);
    std::cin.rdbuf(input_stream.rdbuf());
  }

  std::string getOutput() { return output_stream.str(); }

  void captureOutput() { std::cout.rdbuf(output_stream.rdbuf()); }

 private:
  std::streambuf* original_cin;
  std::streambuf* original_cout;
  std::istringstream input_stream;
  std::ostringstream output_stream;
};

TEST_F(StdIOTest, StdInputReadBasic) {
  setInput("hello");

  StdInput input;
  auto data = input.read(5);

  ASSERT_EQ(data.size(), 5);
  EXPECT_EQ(std::string(data.begin(), data.end()), "hello");
}

TEST_F(StdIOTest, StdInputReadZeroSize) {
  setInput("hello");

  StdInput input;
  auto data = input.read(0);

  EXPECT_TRUE(data.empty());
}

TEST_F(StdIOTest, StdInputReadMoreThanAvailable) {
  setInput("hi");

  StdInput input;
  auto data = input.read(100);

  ASSERT_EQ(data.size(), 2);
  EXPECT_EQ(std::string(data.begin(), data.end()), "hi");
}

TEST_F(StdIOTest, StdInputReadEmpty) {
  setInput("");

  StdInput input;
  auto data = input.read(10);

  EXPECT_TRUE(data.empty());
}

TEST_F(StdIOTest, StdInputReadPartial) {
  setInput("hello world");

  StdInput input;
  auto data1 = input.read(5);
  auto data2 = input.read(6);

  EXPECT_EQ(std::string(data1.begin(), data1.end()), "hello");
  EXPECT_EQ(std::string(data2.begin(), data2.end()), " world");
}

TEST_F(StdIOTest, StdInputReadBinaryData) {
  std::string binary_data = {'\0', '\1', '\2', 'a', 'b'};
  setInput(binary_data);

  StdInput input;
  auto data = input.read(5);

  ASSERT_EQ(data.size(), 5);
  EXPECT_EQ(data[0], '\0');
  EXPECT_EQ(data[1], '\1');
  EXPECT_EQ(data[2], '\2');
  EXPECT_EQ(data[3], 'a');
  EXPECT_EQ(data[4], 'b');
}

TEST_F(StdIOTest, StdOutputWriteBasic) {
  captureOutput();

  StdOutput output;
  std::string msg = "hello";
  output.write(std::vector<char>(msg.begin(), msg.end()));

  EXPECT_EQ(getOutput(), "hello");
}

TEST_F(StdIOTest, StdOutputWriteEmpty) {
  captureOutput();

  StdOutput output;
  output.write({});

  EXPECT_EQ(getOutput(), "");
}

TEST_F(StdIOTest, StdOutputWriteMultiple) {
  captureOutput();

  StdOutput output;
  output.write({'h', 'e', 'l', 'l', 'o'});
  output.write({' '});
  output.write({'w', 'o', 'r', 'l', 'd'});

  EXPECT_EQ(getOutput(), "hello world");
}

TEST_F(StdIOTest, StdOutputWriteBinaryData) {
  captureOutput();

  StdOutput output;
  output.write({'\0', '\1', '\2', 'a', 'b'});

  auto result = getOutput();
  ASSERT_EQ(result.size(), 5);
  EXPECT_EQ(result[0], '\0');
  EXPECT_EQ(result[1], '\1');
  EXPECT_EQ(result[2], '\2');
  EXPECT_EQ(result[3], 'a');
  EXPECT_EQ(result[4], 'b');
}

TEST_F(StdIOTest, StdOutputWriteNewlines) {
  captureOutput();

  StdOutput output;
  output.write({'l', 'i', 'n', 'e', '1', '\n'});
  output.write({'l', 'i', 'n', 'e', '2', '\n'});

  EXPECT_EQ(getOutput(), "line1\nline2\n");
}

TEST_F(StdIOTest, InputOutputIntegration) {
  setInput("test data");
  captureOutput();

  StdInput input;
  StdOutput output;

  auto data = input.read(9);
  output.write(data);

  EXPECT_EQ(getOutput(), "test data");
}

}  // namespace coreutils::test
