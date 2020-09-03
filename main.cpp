
#include <vector>
#include <fstream>
#include <iostream>
#include <libfdt.h>


std::vector<char>
read_binary(const std::string& fnm)
{
  if (fnm.empty())
    throw std::runtime_error("No file specified");

  // load the file
  std::ifstream stream(fnm);
  if (!stream)
    throw std::runtime_error("Failed to open file '" + fnm + "' for reading");

  stream.seekg(0, stream.end);
  size_t size = stream.tellg();
  stream.seekg(0, stream.beg);

  std::vector<char> binary(size);
  stream.read(binary.data(), size);
  return binary;
}

int main ()
{
  auto binary = read_binary("partition_metadata.dtb");
  const void* fdt = binary.data();

  std::cout << fdt_magic(fdt) << std::endl;
  
  std::cout << fdt_totalsize(fdt) << std::endl;

  auto offset = fdt_path_offset(fdt,"/interfaces");

  std::cout << offset << std::endl;

  return 0;
}
