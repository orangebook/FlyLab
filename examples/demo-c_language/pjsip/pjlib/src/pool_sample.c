#include <pjlib.h>
#define THIS_FILE "pool_sample.c"
static void my_perror(const char *title, pj_status_t status) {
  char errmsg[PJ_ERR_MSG_SIZE];
  pj_strerror(status, errmsg, sizeof(errmsg));
  PJ_LOG(1, (THIS_FILE, "%s: %s [status=%d]", title, errmsg, status));
}
static void pool_demo_1(pj_pool_factory *pfactory) {
  unsigned i;
  pj_pool_t *pool;
  // Must create pool before we can allocate anything
  pool = pj_pool_create(pfactory, // the factory
                        "pool1",  // pool's name
                        1114000,     // initial size
                        1114000,     // increment size
                        NULL);    // use default callback.
  if (pool == NULL) {
    my_perror("Error creating pool", PJ_ENOMEM);
    return;
  }
  // Demo: allocate some memory chunks
  for (i = 0; i < 1000; ++i) {
    void *p;
    p = pj_pool_alloc(pool, (pj_rand() + 1) % 512);
    // Do something with p

    // Look! No need to free p!!
  }
  // Done with silly demo, must free pool to release all memory.
  pj_pool_release(pool);
}
int main() {
  pj_caching_pool cp;
  pj_status_t status;
  // Must init PJLIB before anything else
  status = pj_init();
  if (status != PJ_SUCCESS) {
    my_perror("Error initializing PJLIB", status);
    return 1;
  }
  // Create the pool factory, in this case, a caching pool,
  // using default pool policy.
  pj_caching_pool_init(&cp, NULL, 1024 * 1024);
  // Do a demo
  pool_demo_1(&cp.factory);
  // Done with demos, destroy caching pool before exiting app.
  pj_caching_pool_destroy(&cp);
  PJ_LOG(1, (THIS_FILE, "Seems Fine"));
  return 0;
}