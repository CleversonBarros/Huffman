#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "./structs/binary_tree.h"
#include "./structs/priority_queue.h"

int init_suite();

int clean_suite();

void test_tree();

void test_queue();

int main()
{
	CU_pSuite pSuite1 = NULL;

    if(CUE_SUCCESS != CU_initialize_registry() )
    {
        return CU_get_error();
    }

    /* suite to register */
    pSuite1 = CU_add_suite("Data Structs Test", init_suite, clean_suite);
    if (NULL == pSuite1)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
   /* pSuite2 = CU_add_suite("Data Structs Test 2", init_suite, clean_suite); if (NULL == pSuite2) { CU_cleanup_registry(); return CU_get_error(); }*/

    /* test to suite */
    if(NULL == CU_add_test(pSuite1, "Binary Tree Test", test_tree)){
        CU_cleanup_registry();
        return CU_get_error();
    }
    if(NULL == CU_add_test(pSuite1, "Priority Queue Test", test_queue)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    CU_cleanup_registry();
    return CU_get_error();
}

int init_suite()
{
    return 0;
}

int clean_suite()
{
    return 0;
}

void test_tree()
{
	binary_tree *bt = create_empty_binary_tree();
	CU_ASSERT_PTR_NULL(bt);							/* pointer == NULL */
	CU_ASSERT(get_item(bt = add_tree(1)) == 1);		/* compare expression */
	CU_ASSERT_PTR_NOT_NULL(bt);						/* pointer != NULL */
	CU_ASSERT_TRUE(is_child(bt));					/* value is true */
	CU_ASSERT(binary_tree_size(bt) == 1);
}

void test_queue()
{
	priority_queue *pq = create_empty_priority_queue();
	CU_ASSERT_PTR_NULL(pq);
	CU_ASSERT_PTR_NOT_NULL(pq = create_queue(pq));
	CU_ASSERT_TRUE(is_empty(pq));
	enqueue(pq, create_node(5, 10));
	enqueue(pq, create_node(8, 11));
	CU_ASSERT(size_queue(pq) == 2);
	CU_ASSERT_FALSE(is_empty(pq));
	dequeue(pq);
	CU_ASSERT(size_queue(pq) == 0);
}