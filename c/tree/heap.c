#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


struct heap *new_heap(int value);
bool move_up(struct heap *heap, int idx);
void insert_value(struct heap *heap, int value);
void del_heap(struct heap *heap);


struct heap {
    size_t size;
    size_t capacity;
    int   *nodes;
};


struct heap *new_heap(int value)
{
    struct heap *heap = malloc(sizeof(*heap));
    if (!heap)
        goto error;

    heap->capacity = 1 << 4;
    heap->nodes = malloc(heap->capacity * sizeof(*heap->nodes));
    if (!heap->nodes)
        goto alloc_error;

    heap->nodes[0] = 0;  // Unused

    heap->size = 1;
    heap->nodes[heap->size] = value;

    return heap;

alloc_error:
    del_heap(heap);
error:
    return NULL;
}


bool move_up(struct heap *heap, int idx)
{
    if (!heap || idx <= 1)
        return false;

    int parent_idx = idx / 2;
    return heap->nodes[idx] > heap->nodes[parent_idx];
}


void insert_value(struct heap *heap, int value)
{
    if (!heap)
        return;

    assert(heap->size > 0);
    ++heap->size;

    assert(heap->capacity > 0);
    if (heap->size > heap->capacity) {
        int *new_nodes = realloc(heap->nodes, heap->capacity << 1);
        if (!new_nodes) {
            --heap->size;
            return;
        }

        if (new_nodes != heap->nodes)
            heap->nodes = new_nodes;

        heap->capacity <<= 1;
    }
    heap->nodes[heap->size] = value;

    int idx = heap->size;
#define swap(a, b)             \
    ({                         \
        typeof(a) tmp__ = (a); \
        (a) = (b);             \
        (b) = tmp__;           \
     })
    while (move_up(heap, idx)) {
        int parent_idx = idx / 2;
        swap(heap->nodes[idx], heap->nodes[parent_idx]);
        idx = parent_idx;
    }
#undef swap
}


void del_heap(struct heap *heap)
{
    if (!heap)
        return;

    free(heap->nodes);
    heap->capacity = 0;
    heap->size = 0;

    free(heap);
}


int main()
{
    struct heap *heap = new_heap(15);

    insert_value(heap, 10);
    insert_value(heap, 8);
    insert_value(heap, 5);
    insert_value(heap, 4);
    insert_value(heap, 20);

    assert(heap->size == 6);
    assert(heap->capacity == 1 << 4);

    for (int i = 1; i <= (int)heap->size; ++i) {
        printf("%d ", heap->nodes[i]);
    }
    puts("");

    del_heap(heap);

    return 0;
}
