# pvec
 Mostly a excersise in memory managment, pointers, and c. This lests me create a "pvec" (Patrick vector) of uint64_t's by chaining mutiple blocks of memory together.
 Current funtions:
 ```
 uint64_t *pvec = pvec_newPvec();
 pvec_append(pvec, index);
 pvec_pop(pvec);
 pvec_setValue(pvec, index, value);
 pvec_getValue(pvec, index);
 pvec_remove(pvec, index);
 pvec_insert(pvec, index, value);
 uint64_t len = pvec_getLength(pvec);
 pvec_print(pvec);
 ```
