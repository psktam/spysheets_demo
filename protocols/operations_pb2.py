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




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1aprotocols/operations.proto\x12\noperations\"7\n\tCellArray\x12\x0c\n\x04rows\x18\x01 \x01(\x03\x12\x0c\n\x04\x63ols\x18\x02 \x01(\x03\x12\x0e\n\x06values\x18\x03 \x03(\t\"\xb2\x01\n\x13\x41\x63tionSpecification\x12<\n\ninput_data\x18\x01 \x03(\x0b\x32(.operations.ActionSpecification.Argument\x12\x17\n\x0fscript_contents\x18\x02 \x01(\t\x1a\x44\n\x08\x41rgument\x12\x0c\n\x04name\x18\x01 \x01(\t\x12*\n\x0bvalue_array\x18\x02 \x01(\x0b\x32\x15.operations.CellArray')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protocols.operations_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _CELLARRAY._serialized_start=42
  _CELLARRAY._serialized_end=97
  _ACTIONSPECIFICATION._serialized_start=100
  _ACTIONSPECIFICATION._serialized_end=278
  _ACTIONSPECIFICATION_ARGUMENT._serialized_start=210
  _ACTIONSPECIFICATION_ARGUMENT._serialized_end=278
# @@protoc_insertion_point(module_scope)
