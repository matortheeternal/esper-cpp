#ifndef ESPER_STUBS_H_
#define ESPER_STUBS_H_

namespace esper {
	// == DEF CLASSES ==
	// BASE DEFS
	class Def {};
	class MaybeSubrecordDef : public Def {};
	class FormatDef : public Def {};
	class MembersDef : public Def {};
	class ValueDef : public MaybeSubrecordDef {};

	// STRUCTURED DEFS
	class ArrayDef : public MaybeSubrecordDef {};
	class StructDef : public MaybeSubrecordDef {};
	class UnionDef : public MaybeSubrecordDef {};

	// STRUCTURED MEMBER DEFS
	class MainRecordDef : public MembersDef {};
	class MemberArrayDef : public Def {};
	class MemberStructDef : public MembersDef {};
	class MemberUnionDef : public MembersDef {};

	// VALUE DEFS
	class EmptyDef : public ValueDef {};
	class BytesDef : public ValueDef {};
	class StringDef : public ValueDef {};
	class FloatDef : public ValueDef {};
	class IntegerDef : public ValueDef {};

	// INTEGER VALUE DEFS
	class Int0Def : public IntegerDef {};
	class Int8Def : public IntegerDef {};
	class Int16Def : public IntegerDef {};
	class Int32Def : public IntegerDef {};
	class UInt8Def : public IntegerDef {};
	class UInt16Def : public IntegerDef {};
	class UInt32Def : public IntegerDef {};
	class FormIdDef : public UInt32Def {};

	// FORMAT DEFS
	class DivideDef : public FormatDef {};
	class EnumDef : public FormatDef {};
	class FlagsDef : public FormatDef {};
	class FormatUnionDef : public FormatDef {};

	// == ELEMENT CLASSES ==
	// BASE
	class Element {};
	class Container : public Element {
	public:
		void elementAdded(Element* element);
	};
	class ValueElement : public Element {};

	// CONTAINERS
	class PluginFile : public Container {};
	class MainRecord : public Container {};
	class GroupRecord : public Container {};
	class ElementArray : public Container {};
	class MemberArray : public Container {};
	class MemberStruct : public Container {};
	class MemberUnion : public Container {};
	class Struct : public Container {};
	class Union : public Container {};

	// == SETUP CLASSES ==
	class Session {};
	class PluginManager {};
	class DefinitionManager;
	struct SessionOptions {};

	// == PARSING CLASSES ==
	struct MainRecordHeader {};
	struct GroupHeader {};
	class MemoryMap {};
	class PluginFileSource : public MemoryMap {};
	class Signature {};
	class Subrecord {};
}

#endif