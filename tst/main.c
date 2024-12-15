#include <exception.h>

int sketchy(void *env)
{
  printf("Entered sketchy function\n");

  THROW(NEW (Exception) ("Test exception!"));

  printf("Exited sketchy function\n");

  return 0;
}

int sketchy2(void *env)
{
  printf("Entered sketchy function 2\n");

  void *a = *(void**)NULL;

  printf("Exited sketchy function\n");

  return (int)(long)a;
}

int main(void)
{
  CHECK_MEMORY

  TRY {
    sketchy2(NULL);
  } CATCH (SegmentationFaultException) {
    printf("Caught seg fault exception\n");
  } CATCH (Exception) {
    printf("Caught exception: %s\n", _exception->base);
  } FINALLY {
    printf("Always_executes when throw\n");
  } END_TRY;

  const Type *test = TYPEOF(long double);

  if (test) {
    printf("%s (%ld): %ld\n", test->name, test->size, test->category);
  }

  CHECK_MEMORY
  STOP_WATCHING
  
  printf("The program should reach this line!\n");
}