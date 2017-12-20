// тесты для стека

#include "stack.h"
#include <gtest.h>
TEST(Stack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(Stack<int> st(5));
}

TEST(Stack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(Stack<int> st(MAX_VECTOR_SIZE + 1));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> st(-5));
}


TEST(Stack, can_not_delete_if_stack_is_empty)
{
	Stack<int> st(1);
	ASSERT_ANY_THROW(st.Eject());
}

TEST(Stack, can_not_see_the_top_element_if_stack_is_empty)
{
	Stack<int> st(1);
	st.Push(1);
	st.Clean();
	ASSERT_ANY_THROW(st.Top());
}



TEST(Stack, can_get_quantity)
{
	Stack<int> st(10);
	for (int i = 0; i<4; i++)
		st.Push(i);
	EXPECT_EQ(4, st.GetSize());
}

TEST(Stack, can_push_elem1)
{
	Stack<int> st(3);
	st.Push(1);
	st.Push(2);
	st.Push(3);

	ASSERT_NO_THROW(st.Push(4));
}

TEST(Stack, can_push_elem2)
{
	Stack<int> st(4);
	st.Push(1);
	st.Push(2);
	st.Push(3);
	st.Push(4);
	ASSERT_NO_THROW(st.Push(4));
}

TEST(Stack, can_eject_elem)
{
	Stack<int> st(2);
	st.Push(1);
	st.Push(2);
	
	ASSERT_NO_THROW(st.Eject());
}

TEST(Stack, can_check_for_emptiness)
{
	Stack<int> st(2);
	st.Push(1);
	st.Push(2);
	st.Clean();
	EXPECT_EQ(true, st.IsEmpty());
}

TEST(Stack, can_check_for_completeness)
{
	Stack<int> st(2);
	st.Push(1);
	st.Push(2);
	EXPECT_EQ(true, st.IsFull());
}

