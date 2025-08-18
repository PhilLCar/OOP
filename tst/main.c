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

  TRY
    sketchy(NULL);

  CATCH (SegmentationFaultException)
    printf("Caught seg fault exception\n");

  CATCH (Exception)
    printf("Caught exception: %s\n", _exception->base);

  END_TRY;

  double *db = NEW (double)(3.2);

  const Type *test = gettype(db);

  if (test) {
    printf("%s (%ld): %ld\n", test->name, test->size, test->category);
    printf("%lf\n", *db);
  }

  DELETE(db);

  CHECK_MEMORY
  STOP_WATCHING
  
  printf("The program should reach this line!\n");
}