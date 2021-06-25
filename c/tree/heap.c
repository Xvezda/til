#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


struct heap {
    size_t size;
    size_t capacity;
    int   *nodes;
};


struct heap *heap_new(int value);
int heap_resiz(struct heap *heap, size_t size);
bool move_up(struct heap *heap, int idx);
bool move_down(struct heap *heap, int idx);
void heap_ins(struct heap *heap, int value);
int heap_pop(struct heap *heap);
void heap_show(struct heap *heap);
void heap_del(struct heap *heap);


#define max(a, b) ((a) > (b) ? (a) : (b))
// https://stackoverflow.com/a/3982397
#define swap(a, b)           \
    ({ typeof(a) swap = (a); \
       (a) = (b);            \
       (b) = swap; })


#define paren_idx_of(idx)          ((int)((idx) / 2))
#define left_idx_of(idx)           ((int)((idx) * 2))
#define right_idx_of(idx)          ((int)((idx) * 2) + 1)
#define last_idx_of(heap)          ((int)(heap)->size)
#define heap_get(heap, idx)        ((heap)->nodes[idx])
#define heap_set(heap, idx, value) ((heap)->nodes[idx] = (value))

#define HEAP_ALLOC_OK   0
#define HEAP_ALLOC_FAIL 1
enum { HEAP_UNUSED = 0, HEAP_ROOT = 1 };


struct heap *heap_new(int value)
{
    struct heap *heap = calloc(1, sizeof(*heap));
    if (!heap)
        goto error;

    if (heap_resiz(heap, 1) != HEAP_ALLOC_OK)
        goto alloc_error;

    heap_set(heap, HEAP_UNUSED, -1);

    heap->size = HEAP_ROOT;
    heap_set(heap, last_idx_of(heap), value);

    return heap;

alloc_error:
    heap_del(heap);
error:
    return NULL;
}


int heap_resiz(struct heap *heap, size_t size)
{
    if (!heap)
        goto error;

    if (!size) {
        free(heap->nodes);
        heap->nodes = NULL;

        heap->size = 0;
        heap->capacity = 0;
    } else {
        size_t capacity = heap->capacity ?
            heap->capacity << 1 :
            1 << 4;

        while (capacity < size) {
            if (capacity<<1 < capacity)
                goto error;
            capacity <<= 1;
        }

        int *new_node = realloc(heap->nodes,
                                capacity * sizeof(*heap->nodes));
        if (!new_node)
            goto error;

        if (new_node != heap->nodes)
            heap->nodes = new_node;

        heap->capacity = capacity;
    }
    return HEAP_ALLOC_OK;

error:
    return -HEAP_ALLOC_FAIL;
}


bool move_up(struct heap *heap, int idx)
{
    if (!heap || idx <= HEAP_ROOT)
        return false;

    int pidx = paren_idx_of(idx);
    return heap_get(heap, idx) > heap_get(heap, pidx);
}


bool move_down(struct heap *heap, int idx)
{
    if (!heap)
        return false;

    if (left_idx_of(idx) > last_idx_of(heap)) {
        return false;
    } else if (right_idx_of(idx) > last_idx_of(heap)) {
        return heap_get(heap, left_idx_of(idx)) > heap_get(heap, idx);
    } else {
        int left_child = heap_get(heap, left_idx_of(idx));
        int right_child = heap_get(heap, right_idx_of(idx));
        int max_child = max(left_child, right_child);
        return max_child > heap_get(heap, idx);
    }
}


void heap_ins(struct heap *heap, int value)
{
    if (!heap)
        return;

    assert(heap->size >= HEAP_ROOT);
    ++heap->size;

    assert(heap->capacity > HEAP_UNUSED);
    if (heap->size >= heap->capacity &&
            heap_resiz(heap, heap->size) != HEAP_ALLOC_OK) {
        --heap->size;
        return;
    }
    heap_set(heap, last_idx_of(heap), value);

    int idx = last_idx_of(heap);
    while (move_up(heap, idx)) {
        int pidx = paren_idx_of(idx);
        swap(heap_get(heap, idx), heap_get(heap, pidx));
        idx = pidx;
    }
}


int heap_pop(struct heap *heap)
{
    if (!heap || last_idx_of(heap) < HEAP_ROOT)
        return -1;

    int popidx = HEAP_ROOT;
    int ret = heap_get(heap, popidx);

    heap_set(heap, popidx, heap_get(heap, last_idx_of(heap)));
    --heap->size;

    while (move_down(heap, popidx)) {
        if (right_idx_of(popidx) > last_idx_of(heap)) {
            swap(heap_get(heap, left_idx_of(popidx)), heap_get(heap, popidx));
            popidx = left_idx_of(popidx);
        } else {
            int right_idx = right_idx_of(popidx);
            int left_idx = left_idx_of(popidx);
            if (heap_get(heap, left_idx) > heap_get(heap, right_idx)) {
                swap(heap_get(heap, left_idx), heap_get(heap, popidx));
                popidx = left_idx;
            } else {
                swap(heap_get(heap, right_idx), heap_get(heap, popidx));
                popidx = right_idx;
            }
        }
    }
    return ret;
}


void heap_show(struct heap *heap)
{
    if (!heap)
        return;

    for (int i = HEAP_ROOT; i <= last_idx_of(heap); ++i) {
        printf("%d ", heap_get(heap, i));
    }
    puts("");
}


void heap_del(struct heap *heap)
{
    if (!heap)
        return;

    heap_resiz(heap, 0);
    free(heap);
}


int main()
{
    struct heap *heap = heap_new(15);
    if (!heap)
        return 1;

    heap_ins(heap, 10);
    heap_ins(heap, 8);
    heap_ins(heap, 5);
    heap_ins(heap, 4);
    heap_ins(heap, 20);

    assert(last_idx_of(heap) == 6);
    assert(heap->capacity > heap->size);
    heap_show(heap);

    puts("=");
    printf("max: %d\n", heap_pop(heap));
    heap_show(heap);

    puts("=");
    printf("max: %d\n", heap_pop(heap));
    heap_show(heap);

    puts("=");
    printf("max: %d\n", heap_pop(heap));
    heap_show(heap);

    heap_del(heap);

    return 0;
}

