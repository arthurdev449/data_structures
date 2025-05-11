run_editor: editor_cli.c
	gcc -o editor editor_cli.c -Wall -Wextra -g
	./editor
# Rule to build and run the array test (test_array.c needs main())
test_array: array.c test_array.c
	gcc -o test_array array.c test_array.c -lm # Added -lm just in case
	./test_array

# Rule to build and run the linked list test (test_linked_list.c needs main())
test_linked_list: linked_list.c test_linked_list.c
	gcc -o test_linked_list linked_list.c test_linked_list.c -lm # Added -lm just in case
	./test_linked_list

# Rule to build and run the stack test (test_stack.c needs main()) - ADDED THIS RULE
test_stack: stack.c test_stack.c
	gcc -o test_stack stack.c test_stack.c -lm # Added -lm just in case
	./test_stack

# Target to clean up compiled files
clean:
	rm -f array linked_list stack test_array test_linked_list test_stack # Added 'stack' to clean list