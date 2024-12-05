#include <CL/sycl.hpp>
using namespace sycl;

static const int N = 256;

int main() {
  queue q;
  std::cout << "Device : " << q.get_device().get_info<info::device::name>()
            << std::endl;

  // USM allocation and initialization
  int *data = malloc_shared<int>(N, q);

  // Init
  for (int i = 0; i < N; i++) data[i] = 10;

  // Solve dependencies using events
  event e1 = q.parallel_for(range<1>(N), [=](id<1> i) { data[i] += 2; });

  event e2 = q.parallel_for(range<1>(N), e1, [=](id<1> i) { data[i] += 3; });

  event e3 = q.parallel_for(range<1>(N), e2, [=](id<1> i) { data[i] += 5; });

  // Ensure the final task has completed
  e3.wait();

  // Print the results
  for (int i = 0; i < N; i++) std::cout << data[i] << " ";
  std::cout << std::endl;

  free(data, q);
  return 0;
}
