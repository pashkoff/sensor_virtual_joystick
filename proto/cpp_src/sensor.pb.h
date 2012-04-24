// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sensor.proto

#ifndef PROTOBUF_sensor_2eproto__INCLUDED
#define PROTOBUF_sensor_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace sensor {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_sensor_2eproto();
void protobuf_AssignDesc_sensor_2eproto();
void protobuf_ShutdownFile_sensor_2eproto();

class Accel;

// ===================================================================

class Accel : public ::google::protobuf::Message {
 public:
  Accel();
  virtual ~Accel();
  
  Accel(const Accel& from);
  
  inline Accel& operator=(const Accel& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Accel& default_instance();
  
  void Swap(Accel* other);
  
  // implements Message ----------------------------------------------
  
  Accel* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Accel& from);
  void MergeFrom(const Accel& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required float x = 1;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 1;
  inline float x() const;
  inline void set_x(float value);
  
  // required float y = 2;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 2;
  inline float y() const;
  inline void set_y(float value);
  
  // required float z = 3;
  inline bool has_z() const;
  inline void clear_z();
  static const int kZFieldNumber = 3;
  inline float z() const;
  inline void set_z(float value);
  
  // @@protoc_insertion_point(class_scope:sensor.Accel)
 private:
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();
  inline void set_has_z();
  inline void clear_has_z();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  float x_;
  float y_;
  float z_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_sensor_2eproto();
  friend void protobuf_AssignDesc_sensor_2eproto();
  friend void protobuf_ShutdownFile_sensor_2eproto();
  
  void InitAsDefaultInstance();
  static Accel* default_instance_;
};
// ===================================================================


// ===================================================================

// Accel

// required float x = 1;
inline bool Accel::has_x() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Accel::set_has_x() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Accel::clear_has_x() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Accel::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline float Accel::x() const {
  return x_;
}
inline void Accel::set_x(float value) {
  set_has_x();
  x_ = value;
}

// required float y = 2;
inline bool Accel::has_y() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Accel::set_has_y() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Accel::clear_has_y() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Accel::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline float Accel::y() const {
  return y_;
}
inline void Accel::set_y(float value) {
  set_has_y();
  y_ = value;
}

// required float z = 3;
inline bool Accel::has_z() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Accel::set_has_z() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Accel::clear_has_z() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Accel::clear_z() {
  z_ = 0;
  clear_has_z();
}
inline float Accel::z() const {
  return z_;
}
inline void Accel::set_z(float value) {
  set_has_z();
  z_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace sensor

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_sensor_2eproto__INCLUDED
