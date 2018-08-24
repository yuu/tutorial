#include <stdio.h>
#include <glib.h>

struct input {
    int value1;
    int value2;
};

// build: gcc `pkg-config --cflags glib-2.0` gqueue-sample.c `pkg-config --libs glib-2.0`
int main()
{
    struct GQueue *input_queue = g_queue_new();
    struct input input1 = {1, 2};
    struct input input2 = {3, 4};

    g_queue_push_head(input_queue, &input1);
    g_queue_push_head(input_queue, &input2);

    struct input *value1 = (struct input*) g_queue_pop_tail(input_queue);
    struct input *value2 = (struct input*) g_queue_pop_tail(input_queue);

    printf("value1 = %d, %d\n", value1->value1, value1->value2);
    printf("value2 = %d, %d\n", value2->value1, value2->value2);

    printf("empty = %d\n", g_queue_is_empty(input_queue));

    return 0;
}
