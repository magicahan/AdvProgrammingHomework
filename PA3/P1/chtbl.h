typedef struct CHTbl_{
  int buckets;
  int  (*h)(const void *key);
  int  (*match)(const void *key1, const void *key2);
  int  (*destroy)(void *data);
  int  size;
  List *table; /* dynamically allocated 1d array of Lists */
} CHTbl;

int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key),
	       int (*match)(const void *key1, const void *key2),
	       int (*destroy)(void *data));

void chtbl_destroy(CHTbl *htbl);
int chtbl_insert(CHTbl *htbl, const void *data);
int chtbl_remove(CHTbl *htbl, void **data);
int chtbl_lookup(const CHTbl *htbl, void **data);
#define chtbl_size(htbl) ((htbl)->size)
