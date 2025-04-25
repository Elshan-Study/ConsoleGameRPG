#include "Specialization.h"

std::unique_ptr<Specialization> SpecializationDeserialize(std::istream& in) {
	size_t len;
	in.read(reinterpret_cast<char*>(&len), sizeof(len));
	std::string type(len, '\0');
	in.read(&type[0], len);

	if (type == "Wizard") return std::make_unique<Wizard>();
	if (type == "Knight") return std::make_unique<Knight>();
	if (type == "Archer") return std::make_unique<Archer>();
	if (type == "Thief") return std::make_unique<Thief>();
	if (type == "Craftsman") return std::make_unique<Craftsman>();

	throw std::runtime_error("Unknown Specialization type during deserialization: " + type);
}