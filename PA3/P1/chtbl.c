#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "chtbl.h"

/**- chtbl_init -**/
int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key), int
   (*match)(const void *key1, const void *key2), void (*destroy)(void*data)) {

int i;
/* allocate underlying array of lists of size buckets */
if ((htbl->table = (List *)malloc(buckets * sizeof(List))) == NULL)
   return -1;
htbl->buckets = buckets;

for (i = 0; i < htbl->buckets; i++)
   list_init(&htbl->table[i], destroy);

htbl->h = h;
htbl->match = match;
htbl->destroy = destroy;

htbl->size = 0;

return 0;

}

/**- chtbl_destroy -**/
void chtbl_destroy(CHTbl *htbl) {

int                i;
 
/*****************************************************************************
*                                                                            *
*  Destroy each bucket.                                                      *
*                                                                            *
*****************************************************************************/

for (i = 0; i < htbl->buckets; i++)
   list_destroy(&htbl->table[i]);

free(htbl->table);
memset(htbl, 0, sizeof(CHTbl));

return;

}

/**- insert -**/
int chtbl_insert(CHTbl *htbl, const void *data) {

void               *temp;
int                bucket,
                   retval;
 
temp = (void *)data;

if (chtbl_lookup(htbl, &temp) == 0)
   return 1;

/* compute the has function */
bucket = htbl->h(data) % htbl->buckets;
if ((retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
   htbl->size++;

return retval;

}

/**- remove -**/
int chtbl_remove(CHTbl *htbl, void **data) {

ListElmt           *element,
                   *prev;

int                bucket;
 
bucket = htbl->h(*data) % htbl->buckets;
prev = NULL;

for (element = list_head(&htbl->table[bucket]); element != NULL; element =
   list_next(element)) {

   if (htbl->match(*data, list_data(element))) {

      if (list_rem_next(&htbl->table[bucket], prev, data) == 0) {
         htbl->size--;
         return 0;
         }
      else {
         return -1;

      }
   }

   prev = element;

}

return -1;

}

/*****************************************************************************
*                                                                            *
*  ----------------------------- chtbl_lookup -----------------------------  *
*                                                                            *
*****************************************************************************/

int chtbl_lookup(const CHTbl *htbl, void **data) {

ListElmt           *element;

int                bucket;
 
/*****************************************************************************
*                                                                            *
*  Hash the key.                                                             *
*                                                                            *
*****************************************************************************/

bucket = htbl->h(*data) % htbl->buckets;

/*****************************************************************************
*                                                                            *
*  Search for the data in the bucket.                                        *
*                                                                            *
*****************************************************************************/

for (element = list_head(&htbl->table[bucket]); element != NULL; element =
   list_next(element)) {

   if (htbl->match(*data, list_data(element))) {

      /***********************************************************************
      *                                                                      *
      *  Pass back the data from the table.                                  *
      *                                                                      *
      ***********************************************************************/

      *data = list_data(element);
      return 0;

   }

}

/*****************************************************************************
*                                                                            *
*  Return that the data was not found.                                       *
*                                                                            *
*****************************************************************************/

return -1;

}
