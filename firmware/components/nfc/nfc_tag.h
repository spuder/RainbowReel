#pragma once

#include <memory>
#include <vector>

#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "ndef_message.h"

namespace esphome {
namespace nfc {

class NfcTag {
 public:
  NfcTag() {
    this->uid_ = {};
    this->tag_type_ = "Unknown";
  };
  NfcTag(std::vector<uint8_t> &uid) {
    this->uid_ = uid;
    this->tag_type_ = "Unknown";
  };
  NfcTag(std::vector<uint8_t> &uid, const std::string &tag_type) {
    this->uid_ = uid;
    this->tag_type_ = tag_type;
  };
  NfcTag(std::vector<uint8_t> &uid, const std::string &tag_type, std::unique_ptr<nfc::NdefMessage> ndef_message) {
    this->uid_ = uid;
    this->tag_type_ = tag_type;
    this->ndef_message_ = std::move(ndef_message);
  };
  NfcTag(std::vector<uint8_t> &uid, const std::string &tag_type, std::vector<uint8_t> &ndef_data) {
    this->uid_ = uid;
    this->tag_type_ = tag_type;
    this->ndef_message_ = make_unique<NdefMessage>(ndef_data);
  };
  NfcTag(const NfcTag &rhs) {
    uid_ = rhs.uid_;
    tag_type_ = rhs.tag_type_;
    if (rhs.ndef_message_ != nullptr)
      ndef_message_ = make_unique<NdefMessage>(*rhs.ndef_message_);
  }

  NfcTag(std::vector<uint8_t> &uid, const std::string &tag_type, std::vector<uint8_t> &raw_data, bool is_raw_data) {
    //TODO: this probably could be merged with `std::vector<uint8_t> &uid, const std::string &tag_type, std::vector<uint8_t> &ndef_data`
    // but instead of making an ndef_message we just store the raw data
    this->uid_ = uid;
    this->tag_type_ = tag_type;
    this->raw_data_ = raw_data;
    this->is_raw_data_ = is_raw_data;
  }

  std::vector<uint8_t> &get_uid() { return this->uid_; };
  const std::string &get_tag_type() { return this->tag_type_; };
  bool has_ndef_message() { return this->ndef_message_ != nullptr; };
  const std::shared_ptr<NdefMessage> &get_ndef_message() { return this->ndef_message_; };
  void set_ndef_message(std::unique_ptr<NdefMessage> ndef_message) { this->ndef_message_ = std::move(ndef_message); };
  bool has_raw_data() { return this->is_raw_data_; };
  const std::vector<uint8_t> &get_raw_data() { return this->raw_data_; };

 protected:
  std::vector<uint8_t> uid_;
  std::string tag_type_;
  std::shared_ptr<NdefMessage> ndef_message_;
  std::vector<uint8_t> raw_data_;
  bool is_raw_data_ = false;
};

}  // namespace nfc
}  // namespace esphome
