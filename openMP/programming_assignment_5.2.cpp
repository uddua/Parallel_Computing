#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double num_aleatorio() {
   double numero = (double) random() / (double) RAND_MAX;
   if((double) random() / (double) RAND_MAX < 0.5) {
      numero *= -1;
   }
   return numero;
}

int main(int argc, char* argv[]) {

   long int number_tosses, number_in_circle;
   int thread_count, i;
   double x, y, distancia;

   thread_count = strtol(argv[1], NULL, 10);
   number_tosses = strtoll(argv[2], NULL, 10);

   number_in_circle =0;
   srandom(0);
#  pragma omp parallel for num_threads(thread_count) \
      reduction(+: number_in_circle) private(x, y, distancia)
   for (i = 0; i < number_tosses; i++) {
      x = num_aleatorio();
      y = num_aleatorio();
      distancia = x*x + y*y;

      if (distancia <= 1) {
         number_in_circle += 1;
      }
   }
   double pi = 4*number_in_circle/((double) number_tosses);
   printf("Pi = %.14f\n", pi);
   return 0;
}
