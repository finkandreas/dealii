// ---------------------------------------------------------------------
//
// Copyright (C) 2012 - 2018 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE at
// the top level of the deal.II distribution.
//
// ---------------------------------------------------------------------


// check that LinearAlgebra::Vector::add_and_dot works correctly for complex-valued
// vectors

#include "../tests.h"
#include <deal.II/lac/la_vector.h>




template <typename number>
void check ()
{
  for (unsigned int test=0; test<5; ++test)
    {
      const unsigned int size = 17 + test*1101;
      LinearAlgebra::Vector<std::complex<number>> v1 (size), v2(size), v3(size), check(size);
      for (unsigned int i=0; i<size; ++i)
        {
          v1(i) = std::complex<number>(0.1 + 0.005 * i, 1.234 + 12 * i);
          v2(i) = std::complex<number>(-5.2 + 0.18 * i, 42.4242 + 42 * i);
          v3(i) = std::complex<number>(3.14159 + 2.7183/(1.+i), 13.);
        }
      check = v1;
      const std::complex<number> factor = std::complex<number>(0.01432);

      // do things by hand once
      v1.add(factor, v2);
      const std::complex<number> prod = v1 * v3;

      // then do it a second time with the add_and_dot function
      const std::complex<number> prod_check = check.add_and_dot(factor, v2, v3);
      if (test == 0 && std::is_same<number,double>::value)
        {
          deallog << "Vector add reference:   ";
          v1.print(deallog.get_file_stream());
          deallog << std::endl;
          deallog << "Vector check reference: ";
          check.print(deallog.get_file_stream());
          deallog << std::endl;
        }

      deallog << "Add and dot should be " << prod/static_cast<number>(size)
              << ", is " << prod_check/static_cast<number>(size)
              << std::endl;
    }
}


int main()
{
  std::ofstream logfile("output");
  deallog << std::fixed;
  deallog << std::setprecision(2);
  deallog.attach(logfile);

  check<float>();
  check<double>();
  deallog << "OK" << std::endl;
}

