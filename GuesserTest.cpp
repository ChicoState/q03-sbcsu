/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};


TEST(GuesserTest, CorrectGuess) {
	Guesser secret("secret");
	ASSERT_TRUE(secret.match("secret"));
}
  
TEST(GuesserTest, IncorrectGuess) {
	Guesser secret("secret");
	ASSERT_FALSE(secret.match("aecret"));
}
  
TEST(GuesserTest, GuessWithLeadingWhitespaceFails) {
	Guesser secret("secret");
	ASSERT_FALSE(secret.match(" secret"));
}
  
TEST(GuesserTest, GuessWithTrailingWhitespaceFails) {
	Guesser secret("secret");
	ASSERT_FALSE(secret.match("secret "));
}
  
TEST(GuesserTest, GuessWithBothWhitespaceFails) {
	Guesser secret("secret");
	ASSERT_FALSE(secret.match(" secret "));
}
  
TEST(GuesserTest, BruteForceLock) {
	Guesser secret("secret");
	ASSERT_FALSE(secret.match("aaaaaa")); 
	ASSERT_FALSE(secret.match("secret")); 
}

TEST(GuesserTest, BruteForceDistanceMoreThanTwo) {
	Guesser secret("secret");
	ASSERT_FALSE(secret.match("aaaaaa")); 
	ASSERT_FALSE(secret.match("secret")); 
}
  
TEST(GuesserTest, BruteForceLockRemainingCount) {
	Guesser secret("secret");
	secret.match("aaaaaa"); 
	ASSERT_EQ(secret.remaining(), 3); 
  }
  
TEST(GuesserTest, CorrectGuessResetsRemaining1) {
	Guesser secret("secret");
	secret.match("aecret"); 
	secret.match("secret"); 
	ASSERT_EQ(secret.remaining(), 3);
}

TEST(GuesserTest, CorrectGuessResetsRemaining2) {
	Guesser secret("secret");
	secret.match("aecret"); 
	secret.match("aecret"); 
	secret.match("secret"); 
	ASSERT_EQ(secret.remaining(), 3);
}

TEST(GuesserTest, ThreeIncorrectGuessesLock) {
	Guesser secret("secret");
	secret.match("aecret");
	secret.match("aecret"); 
	secret.match("aecret"); 
	ASSERT_FALSE(secret.match("secret")); 
}

TEST(GuesserTest, DecrementRemainingAfterLock) {
	Guesser secret("secret");
	secret.match("aaaaaa"); 
	secret.match("aecret"); 
	secret.match("aecret"); 
	ASSERT_EQ(secret.remaining(), 1);
}

TEST(GuesserTest, GuessTruncated) {
	Guesser secret("secretsecretsecretsecretsecretsecret");
	ASSERT_TRUE(secret.match("secretsecretsecretsecretsecretse"));
}