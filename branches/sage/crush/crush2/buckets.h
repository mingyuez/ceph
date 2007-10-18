#ifndef _CRUSH_BUCKETS_H
#define _CRUSH_BUCKETS_H

enum {
	CRUSH_BUCKET_UNIFORM = 1,
	CRUSH_BUCKET_LIST = 2,
	CRUSH_BUCKET_TREE = 3,
	CRUSH_BUCKET_STRAW = 4
};

struct crush_bucket {
	__s32 id;        /* this'll be negative */
	__u16 type;
	__u16 bucket_type;
	__u32 weight;    /* 16-bit fixed point */
	__u32 size;      /* num items */
	__s32 *items;
};

struct crush_bucket_uniform {
	struct crush_bucket h;
	__u32 *primes;
	__u32 item_weight;  /* 16-bit fixed point */
};

struct crush_bucket_list {
	struct crush_bucket h;
	__u32 *item_weights;  /* 16-bit fixed point */
	__u32 *sum_weights;   /* 16-bit fixed point.  element i is sum of weights 0..i, inclusive */
};

struct crush_bucket_tree {
	struct crush_bucket h;  /* note: h.size is tree size, not number of actual items */
	__u32 *node_weights;
};

struct crush_bucket_straw {
	struct crush_bucket h;
	__u32 *straws;  /* 16-bit fixed point */
};

extern int crush_bucket_uniform_choose(struct crush_bucket_uniform *bucket, int x, int r);
extern int crush_bucket_list_choose(struct crush_bucket_list *bucket, int x, int r);
extern int crush_bucket_tree_choose(struct crush_bucket_tree *bucket, int x, int r);
extern int crush_bucket_straw_choose(struct crush_bucket_straw *bucket, int x, int r);

extern void crush_destroy_bucket_uniform(struct crush_bucket_uniform *);
extern void crush_destroy_bucket_list(struct crush_bucket_list *);
extern void crush_destroy_bucket_tree(struct crush_bucket_tree *);
extern void crush_destroy_bucket_straw(struct crush_bucket_straw *);

#endif
