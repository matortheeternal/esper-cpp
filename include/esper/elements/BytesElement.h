#ifndef ESPER_BYTESELEMENT_H
#define ESPER_BYTESELEMENT_H

#include "../helpers/helpers.h"
#include "../defs/BytesDef.h"
#include "../parsing/Subrecord.h"
#include "ValueElement.h"

namespace esper {
	class BytesElement : public ValueElement {
	public:
		BytesElement(Element* container, Def* def)
			: ValueElement(container, def) {
			this->data = new list<uint8_t>(def->getSize()) { 0 };
		}

		~BytesElement() {
			delete this->data;
		}

		void build(Subrecord* subrecord) {
			if (subrecord->size != def->getSize())
				throw error("Subrecord size does not match def size.");
			for (auto i = 0; i < data->size(); i++)
				data[i] = subrecord->data[i];
		}

		list<uint8_t>* getData() {
			return data;
		}

		void setData(list<uint8_t>* data) {
			if (data->size() != this->data->size())
				throw error("Input data size did not match def size.");
			for (auto i = 0; i < data->size(); i++)
				this->data[i] = data[i];
		}

		string getValue() {
			return formatBytes(data, def->getSize());
		}

		void setValue(string value) {
			list<uint8_t>* bytes = parseBytes(value);
			setData(bytes);
			delete bytes;
		}

	private:
		list<uint8_t>* data;
	};
}

#endif