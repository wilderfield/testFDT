
#include <vector>
#include <fstream>
#include <iostream>
#include <libfdt.h>
#include <string>

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
  
  const void* iuuid_ptr;
  int   iuuid_size;

  int offset;

  // Find interfaces node
  offset = fdt_subnode_offset(fdt,0,"interfaces");
  if (offset < 0)
    throw std::runtime_error("Could not find interfaces node");
  
  // Find @0 subnode
  offset = fdt_subnode_offset(fdt,offset,"@0");
  if (offset < 0)
    throw std::runtime_error("Could not find @0 subnode");

  // Get interface_uuid property from subnode
  iuuid_ptr = fdt_getprop(fdt,offset,"interface_uuid",&iuuid_size);
  if (iuuid_ptr == nullptr)
    throw std::runtime_error("Could not find interface_uuid property");
  
  if (iuuid_size != 33)
    throw std::runtime_error("interface_uuid size is invalid");

  std::string iuuid(reinterpret_cast<const char*>(iuuid_ptr),32);
  std::cout << iuuid << std::endl;
  
  return 0;
}
