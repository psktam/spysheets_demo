# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: protocols/operations.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1aprotocols/operations.proto\x12\noperations\"\xaa\x01\n\tCellValue\x12,\n\x04type\x18\x01 \x01(\x0e\x32\x1e.operations.CellValue.CellType\x12\x0f\n\x07int_val\x18\x02 \x01(\x03\x12\x10\n\x08real_val\x18\x03 \x01(\x01\x12\x12\n\nstring_val\x18\x04 \x01(\t\"8\n\x08\x43\x65llType\x12\x0b\n\x07Integer\x10\x01\x12\x08\n\x04Real\x10\x02\x12\n\n\x06String\x10\x03\x12\t\n\x05\x45mpty\x10\x04\"N\n\tCellArray\x12\x0c\n\x04rows\x18\x01 \x01(\x03\x12\x0c\n\x04\x63ols\x18\x02 \x01(\x03\x12%\n\x06values\x18\x03 \x03(\x0b\x32\x15.operations.CellValue\"\xb2\x01\n\x13\x41\x63tionSpecification\x12<\n\ninput_data\x18\x01 \x03(\x0b\x32(.operations.ActionSpecification.Argument\x12\x17\n\x0fscript_contents\x18\x02 \x01(\t\x1a\x44\n\x08\x41rgument\x12\x0c\n\x04name\x18\x01 \x01(\t\x12*\n\x0bvalue_array\x18\x02 \x01(\x0b\x32\x15.operations.CellArray')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protocols.operations_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _CELLVALUE._serialized_start=43
  _CELLVALUE._serialized_end=213
  _CELLVALUE_CELLTYPE._serialized_start=157
  _CELLVALUE_CELLTYPE._serialized_end=213
  _CELLARRAY._serialized_start=215
  _CELLARRAY._serialized_end=293
  _ACTIONSPECIFICATION._serialized_start=296
  _ACTIONSPECIFICATION._serialized_end=474
  _ACTIONSPECIFICATION_ARGUMENT._serialized_start=406
  _ACTIONSPECIFICATION_ARGUMENT._serialized_end=474
# @@protoc_insertion_point(module_scope)
